#pragma once
#include <Core/Engine/Render/Vertex/Vertex.h>
#include <vector>
#include <string>
#include <iostream>
//#include <Core/Engine/Render/Drawable.h>

namespace we {

	class Mesh
	{
	public:
		Mesh();
		Mesh(const we::Mesh& other);
		Mesh(const std::vector<we::Vertex>& vertices, const std::vector<unsigned int>& indices);
		~Mesh();
		//Mesh operator=(we::Mesh&) {r}
		void Draw() const;
	private:
		void Init();
		GLuint VAO, VBO, EBO;
		std::vector<we::Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::string m_Name;
	};
}

