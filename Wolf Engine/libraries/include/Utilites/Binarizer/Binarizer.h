#pragma once
#include <iostream>
#include <fstream>


#define MODEL3D_HEADER "#Model3D"
#define MAX_TEXTURES_COUNT 4

namespace we {
	class Binarizer
	{
	public :
		Binarizer() = delete;
		//~Binarizer();
		template<typename T>
		inline static std::streampos TellPosition(T& file)
		{
			return file.tellp();
		}
		inline static void ReadAt(std::ifstream& file, std::streampos position)
		{
			file.seekg(position);
		}
		inline static void WriteAt(std::ofstream& file, std::streampos position)
		{
			file.seekp(position);
		}
		inline static std::string ReadString(std::ifstream& file, unsigned int size)
		{
			std::string s(size,'\0'); file.read((char*)s.c_str(), sizeof(char) * size); return s;
		}
		inline static std::streampos WriteString(std::ofstream& file, std::string string)
		{
			std::streampos p = file.tellp(); file.write((char*)string.c_str(), sizeof(char) * (string.size())); return p;
		}
		inline static char ReadChar(std::ifstream& file)
		{
			char c; file.read((char*)&c, sizeof(char)); return c;	
		}
		inline static std::streampos WriteChar(std::ofstream& file, char c)
		{
			std::streampos p = file.tellp(); file.write((char*)&c, sizeof(char)); return p;
		}
		inline static float ReadFloat(std::ifstream& file)
		{
			float f; file.read((char*)&f, sizeof(float)); return f;
		}
		inline static std::streampos WriteFloat(std::ofstream& file, float value)
		{
			std::streampos p = file.tellp(); file.write(reinterpret_cast<char*>(&value), sizeof(float)); return p;
		}
		inline static int ReadInt(std::ifstream& file)
		{
			int i; file.read((char*)&i, sizeof(int)); return i;
		}
		inline static std::streampos WriteInt(std::ofstream& file, int value)
		{
			std::streampos p = file.tellp(); file.write(reinterpret_cast<char*>(&value), sizeof(int)); return p;
		}
		inline static unsigned int ReadUint(std::ifstream& file)
		{
			unsigned int ui; file.read((char*)&ui, sizeof(unsigned int)); return ui;
		}
		inline static std::streampos WriteUint(std::ofstream& file, unsigned int value)
		{
			std::streampos p = file.tellp(); file.write(reinterpret_cast<char*>(&value), sizeof(unsigned int)); return p;
		}
		inline static unsigned char ReadByte(std::ifstream& file)
		{
			unsigned char b; file.read((char*)&b, sizeof(unsigned char)); return b;
		}
		inline static std::streampos WriteByte(std::ofstream& file, unsigned char b)
		{
			std::streampos p = file.tellp(); file.write(reinterpret_cast<char*>(&b), sizeof(unsigned char)); return p;
		}
		inline static std::streampos WriteByte(std::ofstream& file, unsigned char* b)
		{
			std::streampos p = file.tellp(); file.write(reinterpret_cast<char*>(b), sizeof(b)); return p;
		}
	};
}

