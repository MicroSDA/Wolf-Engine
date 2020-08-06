#pragma once
#include <Utilites/Math/glm/glm.hpp>
#include <Utilites/GLEW/glew.h>

namespace we {

	class Vertex
	{
	public:
		Vertex();
		Vertex(const glm::vec3& possition,
			   const glm::vec2& textureCoords,
			   const glm::vec3& normals,
			   const GLuint& id);
		Vertex(const GLfloat& possitionX,
			   const GLfloat& possitionY,
			   const GLfloat& possitionZ,
			   const GLfloat& textureCoordX,
			   const GLfloat& textureCoordY,
			   const GLfloat& normalX,
			   const GLfloat& normalY,
			   const GLfloat& normalZ,
			   const GLuint& id);
		~Vertex();

		glm::vec3 m_Possition;
		glm::vec2 m_TextureCoords;
		glm::vec3 m_Normals;
		GLuint m_Id;
	};
}


