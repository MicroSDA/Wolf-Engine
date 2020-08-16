#pragma once
//#include <Core/Engine/Resources/ResourceManager.h>
#include <Core/Engine/Resources/Resource.h>
#include <Utilites/GLEW/glew.h>
#include <Utilites/Image/Image.h>

namespace we
{ 
	enum TEXTURES {
		SIMPLE_T,
		DIFFUSE_T,
		SPECULAR_T,
		NORMAL_T,
		SHINES_T
	};
	/*struct ImageData
	{
		int m_Width, m_Height, m_NumComponets;
		unsigned char* m_pImageData;
	};*/

	class Texture :public we::Resource
	{
	public:
		Texture(we::ImageData& imageData);
		~Texture();
		void Init();
		void Bind(unsigned int i);
		void UnBind();

		inline void SetType(const we::TEXTURES& type) { m_Type = type; }
		inline we::TEXTURES GetType() { return m_Type; }
	private:
		GLuint m_Texture;
		we::TEXTURES m_Type;
		we::ImageData* m_ImageData;
	};
}

