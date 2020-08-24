#include "Image.h"

we::Image::Image()
{
	
}

we::Image::~Image()
{
}

we::ImageData* we::Image::LoadFromFile(const std::string& filePath)
{
	m_File.open(filePath, std::ios_base::binary);
	if (!m_File.is_open())
	{
		std::cerr << "Cannot open file: " + filePath + "\n";
		return nullptr;
	}

	if (filePath.substr(filePath.find_last_of(".") + 1) == "tga")
	{
		unsigned char UncHeader[12] = { 0x0,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0 };
		unsigned char ComHeader[12] = { 0x0,0x0,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0 };
		unsigned char Header[12];

		//Always uncompresed - see http://www.opennet.ru/docs/formats/targa.pdf
		for (unsigned int i = 0; i < 12; i++)
		{
			Header[i] = we::Binarizer::ReadByte(m_File);
		}
		if (memcmp(&Header, &UncHeader, 12) == 0)
		{
			return LoadUncompressedTGA();
		}
		else {

			return LoadUncompressedTGA();
		}


	}
	else if (filePath.substr(filePath.find_last_of(".") + 1) == "png")
	{
		unsigned char PngHeader[8] = { 0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A };
		unsigned char Header[8];

		for (unsigned int i = 0; i < 8; i++)
		{
			Header[i] = we::Binarizer::ReadByte(m_File);
		}
		if (memcmp(&Header, &PngHeader, 8) == 0)
		{
			//return LoadPNG();
			std::cerr << "Undefined file format: " + filePath + "\n";
			return nullptr;
		}
		else {

			std::cerr << "Undefined file format: " + filePath + "\n";
			return nullptr;
		}
	}
	else {
		std::cerr << "Undefined file format: " + filePath + "\n";
		return nullptr;
	}

	return nullptr;
}

we::ImageData* we::Image::LoadUncompressedTGA()
{
	unsigned int _Meta[6];
	for (unsigned int i = 0; i < 6; i++)
	{
		_Meta[i] = (unsigned int)we::Binarizer::ReadByte(m_File) ;
	}

	we::ImageData* _ImageData = new we::ImageData;
	_ImageData->m_Width = _Meta[1] * 256 + _Meta[0];
	_ImageData->m_Height = _Meta[3] * 256 + _Meta[2];
	_ImageData->m_BytePerPixel = _Meta[4] / 8;

	if (_Meta[4] == 32)
		_ImageData->m_HasAlpha = true;
	else
		_ImageData->m_HasAlpha = false;

	unsigned int _ImageDataSize = _ImageData->m_BytePerPixel *
		                          _ImageData->m_Width *
		                          _ImageData->m_Height;
	_ImageData->m_pImageData = new unsigned char[_ImageDataSize];

	m_File.read((char*)_ImageData->m_pImageData, sizeof(unsigned char) * _ImageDataSize);
	m_File.close();

	for (unsigned int i = 0; i < _ImageDataSize; i += _ImageData->m_BytePerPixel)
	{
		    _ImageData->m_pImageData[i] ^= _ImageData->m_pImageData[i + 2] ^=
			_ImageData->m_pImageData[i] ^= _ImageData->m_pImageData[i + 2];
	}
	
	//TODO: DO NOT FORGET ABOUT DELETE; !!!
	return _ImageData;
	//delete _ImageData.m_ImageData;
}

we::ImageData* we::Image::LoadCompressedTGA()
{   
	unsigned int _Meta[6];
	for (unsigned int i = 0; i < 6; i++)
	{
		_Meta[i] = (unsigned int)we::Binarizer::ReadByte(m_File);
	}

	we::ImageData* _ImageData = new we::ImageData;
	_ImageData->m_Width = _Meta[1] * 256 + _Meta[0];
	_ImageData->m_Height = _Meta[3] * 256 + _Meta[2];
	_ImageData->m_BytePerPixel = _Meta[4] / 8;

	if (_Meta[4] == 32)
		_ImageData->m_HasAlpha = true;
	else
		_ImageData->m_HasAlpha = false;

	unsigned int _ImageDataSize = _ImageData->m_BytePerPixel *
		                          _ImageData->m_Width *
		                          _ImageData->m_Height;
	_ImageData->m_pImageData = new unsigned char[_ImageDataSize];

	unsigned int _PixelCount    = _ImageData->m_Width * _ImageData->m_Height;
	unsigned int _CurrentPixel  = 0;
	unsigned int _CurrentByte   = 0;
	unsigned char* _ColorBuffer = new unsigned char[_ImageData->m_BytePerPixel];// TODO: DONOT FORGET !!!

	do {
	 
		unsigned char _ChunkHeader = we::Binarizer::ReadByte(m_File);
		if (_ChunkHeader < 128) // RAW
		{
			_ChunkHeader++;
			for (short c = 0; c < _ChunkHeader; c++)
			{
				m_File.read((char*)_ColorBuffer, sizeof(unsigned char) * _ImageData->m_BytePerPixel);
				_ImageData->m_pImageData[_CurrentByte]      = _ColorBuffer[2];    //R
				_ImageData->m_pImageData[_CurrentByte + 1]  = _ColorBuffer[1];    //G
				_ImageData->m_pImageData[_CurrentByte + 2]  = _ColorBuffer[0];    //B
				if(_ImageData->m_HasAlpha)
					_ImageData->m_pImageData[_CurrentByte + 3] = _ColorBuffer[3]; //A

				_CurrentByte += _ImageData->m_BytePerPixel;
				_CurrentPixel++;
			}
		}
		else {
			_ChunkHeader -= 127; //RLE
			m_File.read((char*)_ColorBuffer, sizeof(unsigned char) * _ImageData->m_BytePerPixel);//Check this
			for (short c = 0; c < _ChunkHeader; c++)
			{
				_ImageData->m_pImageData[_CurrentByte]     = _ColorBuffer[2];     //R
				_ImageData->m_pImageData[_CurrentByte + 1] = _ColorBuffer[1];     //G
				_ImageData->m_pImageData[_CurrentByte + 2] = _ColorBuffer[0];     //B
				if (_ImageData->m_HasAlpha)
					_ImageData->m_pImageData[_CurrentByte + 3] = _ColorBuffer[3]; //A

				_CurrentByte += _ImageData->m_BytePerPixel;
				_CurrentPixel++;
			}
		}
	
	} while (_CurrentPixel < _PixelCount);

	delete[] _ColorBuffer;
	m_File.close();
	return _ImageData;
}

we::ImageData* we::Image::LoadPNG()
{

	/*//Длина 13, но записанна не в том битовом порядке, вроде во всех пикчах тут 13 так что можно просто скипнуть 
	unsigned char _C_buffer[4];
	m_File.read((char*)_C_buffer, sizeof(_C_buffer));
	unsigned int _ChunkSize = *reinterpret_cast<unsigned int*>(we::Binarizer::ToLittleEndian(_C_buffer));
	std::cout << we::Binarizer::ReadString(m_File, 4) << "\n"; // Header chunk

	we::ImageData* _ImageData = new we::ImageData;
	m_File.read((char*)_C_buffer, sizeof(_C_buffer));//Width
	_ImageData->m_Width = *reinterpret_cast<unsigned int*>(we::Binarizer::ToLittleEndian(_C_buffer));
	m_File.read((char*)_C_buffer, sizeof(_C_buffer));//Height
	_ImageData->m_Height = *reinterpret_cast<unsigned int*>(we::Binarizer::ToLittleEndian(_C_buffer));
	//m_File.read((char*)_C_buffer, sizeof(_C_buffer));//BPP
	//char c = we::Binarizer::ReadChar(m_File);
	_ImageData->m_BytePerPixel = we::Binarizer::ReadByte(m_File);
	unsigned char _Color = we::Binarizer::ReadByte(m_File);
	if (_Color == 0x1)
	{
		//Monochrome
		_ImageData->m_HasAlpha = true;
	}
	else if(_Color == 0x2){
		//RGB
	}
	else if (_Color == 0x3)
	{
		//Paleted
	}
	else if (_Color == 0x4)
	{
		//Gray scale + alpha
	}
	else if (_Color == 0x6)
	{
		//RGB+Alpha
	}
	
	//skeep 2 bytes
	we::Binarizer::ReadAt(m_File, we::Binarizer::TellPosition(m_File) + std::streampos(2));

	if (we::Binarizer::ReadByte(m_File) == 0x0)
	{

	}
	else {
		//Adam7
	}

	we::Binarizer::ReadAt(m_File, we::Binarizer::TellPosition(m_File) + std::streampos(62));
	std::cout << _ChunkSize << "\n";
	//Имя 4 байта

	//we::Binarizer::ReadAt(m_File, we::Binarizer::TellPosition(m_File) + std::streampos(9));

	/*for (unsigned int i = 0; i < _Lenght; i++)
	{
		std::cout << (char)we::Binarizer::ReadByte(m_File);
	}
	
	m_File.close();*/
	return nullptr;
}
