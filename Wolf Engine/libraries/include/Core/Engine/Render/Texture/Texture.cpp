#include "Texture.h"
//#include <Core/Engine/Resources/ResourceManager.h>

we::Texture::Texture(we::ImageData& imageData):we::Resource(),
    m_Type(we::SIMPLE_T),
	m_Texture(NULL),
	m_IsInitalized(false)
{
	m_ImageData = &imageData;
	std::cout << "Texture(" << this << ")\n";
}

we::Texture::~Texture()
{
	std::cout << "~Texture(" << this << ")\n";
	glDeleteTextures(1, &m_Texture);
}

void we::Texture::Init()
{
	if (m_IsInitalized)
		return;
	

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (m_Type == we::DIFFUSE_T || m_Type == we::NORMAL_T ) // Normal only for nanosuit in srgb
	{
		if (m_ImageData->m_HasAlpha)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, m_ImageData->m_Width, m_ImageData->m_Width, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageData->m_pImageData);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, m_ImageData->m_Width, m_ImageData->m_Width, 0, GL_RGB, GL_UNSIGNED_BYTE, m_ImageData->m_pImageData);
		}
		  
	}
	else {

		if (m_ImageData->m_HasAlpha)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ImageData->m_Width, m_ImageData->m_Width, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_ImageData->m_pImageData);
		}
		else {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ImageData->m_Width, m_ImageData->m_Width, 0, GL_RGB, GL_UNSIGNED_BYTE, m_ImageData->m_pImageData);
		}
		
		
	}


	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);


	if (glewIsExtensionSupported("GL_EXT_texture_filter_anisotropic")) {

		GLfloat amount;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &amount);

		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, amount);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
	}
	else {

		std::cerr << "Anisotropic filtering isn't supported" << std::endl;
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	we::Image::FreeImageData(m_ImageData);
	
	m_IsInitalized = true;
}

void we::Texture::Bind(unsigned int i)
{
	glActiveTexture(GL_TEXTURE0 + i);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}

void we::Texture::UnBind()
{
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
