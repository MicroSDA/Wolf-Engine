#pragma once
//#include <Core/Engine/Resources/ResourceManager.h>
#include <Core/Engine/Resources/Resource.h>
#include <Utilites/GLEW/glew.h>

namespace we
{ 
	struct ImageData
	{
		int m_Width, m_Height, m_NumComponets;
		unsigned char* m_pImageData;
	};

	class Texture :public we::Resource
	{
	public:
		Texture();
		Texture(const we::ImageData& imageData);
		~Texture();
		void Bind(unsigned int i);
		void UnBind();
	private:
		GLuint m_Texture;
	};
}

