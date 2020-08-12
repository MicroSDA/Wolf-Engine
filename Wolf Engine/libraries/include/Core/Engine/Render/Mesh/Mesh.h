#pragma once
#include <Core/Engine/Render/Vertex/Vertex.h>
#include <Core/Engine/Render/Texture/Texture.h>
#include <Core/Engine/Resources/RHolder.h>
#include <Core/Engine/Render/Material/Material.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
//#include <Core/Engine/Render/Drawable.h>

namespace we {

	class Mesh :public we::RHolder
	{
	public:
		Mesh();
		Mesh(const we::Mesh& other);
		Mesh(const std::vector<we::Vertex>& vertices,
			 const std::vector<unsigned int>& indices);
		~Mesh();
		inline void SetVertices(std::vector<we::Vertex> vertices) { m_Vertices = vertices; }
		inline void SetIndices(std::vector<unsigned int> indices) { m_Indices = indices; }
		inline void SetTextures(std::map<std::string, we::Texture*> textures) { m_pTextures = textures; }
		inline std::map<std::string, we::Texture*>* GetTextures() { return &m_pTextures; }
		void Init();
		//Mesh operator=(we::Mesh&) {r}
		void Draw(we::Shader& shader) const;
	private:
		
		GLuint VAO, VBO, EBO;
		std::vector<we::Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::string m_Name;
		std::map<std::string, we::Texture*> m_pTextures;
		we::Material m_Material;
	};
}

