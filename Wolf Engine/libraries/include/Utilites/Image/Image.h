#pragma once
#include <Utilites/Binarizer/Binarizer.h>

namespace we {

	struct ImageData
	{
		unsigned char* m_pImageData;
		unsigned int   m_BytePerPixel;
		unsigned int   m_Width;
		unsigned int   m_Height;
		bool           m_HasAlpha;
	};

	class Image
	{
	public:
		Image();
		~Image();
		we::ImageData* LoadFromFile(const std::string& filePath);
		static inline void FreeImageData(we::ImageData* imageData) { delete imageData->m_pImageData; delete imageData; }
	private:
		std::ifstream m_File;
		we::ImageData* LoadUncompressedTGA();
		we::ImageData* LoadCompressedTGA();
		we::ImageData* LoadPNG();
	};
}

