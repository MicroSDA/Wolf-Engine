#include "Texture.h"
//#include <Core/Engine/Resources/ResourceManager.h>


we::Texture::Texture():we::Resource()
{
	std::cout << "Texture(" << this << ")\n";
}

we::Texture::Texture(const we::ImageData& imageData):we::Resource()
{
	std::cout << "Texture(" << this << ")\n";

	glGenTextures(1, &m_Texture);

	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, imageData.m_Width, imageData.m_Width, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.m_pImageData);

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
	
}

we::Texture::~Texture()
{
	std::cout << "~Texture(" << this << ")\n";
	glDeleteTextures(1, &m_Texture);
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
