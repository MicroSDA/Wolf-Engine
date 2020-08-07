#include "Vertex.h"

we::Vertex::Vertex()
{
	m_Possition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_TextureCoords = glm::vec2(0.0f, 0.0f);
	m_Normals = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Id = 0;
}

we::Vertex::Vertex(const glm::vec3& possition,
	const glm::vec2& textureCoords, 
	const glm::vec3& normals,
	const GLuint& id)
{
	m_Possition = possition;
	m_TextureCoords = textureCoords;
	m_Normals = normals;
	m_Id = id;
}

we::Vertex::Vertex(const GLfloat& possitionX,
	const GLfloat& possitionY,
	const GLfloat& possitionZ,
	const GLfloat& textureCoordX,
	const GLfloat& textureCoordY,
	const GLfloat& normalX,
	const GLfloat& normalY,
	const GLfloat& normalZ,
	const GLuint& id)
{
	m_Possition.x = possitionX;
	m_Possition.y = possitionY;
	m_Possition.z = possitionZ;

	m_TextureCoords.x = textureCoordX;
	m_TextureCoords.y = textureCoordY;

	m_Normals.x = normalX;
	m_Normals.y = normalY;
	m_Normals.z = normalZ;

	m_Id = id;
}

we::Vertex::~Vertex()
{
	//std::cout << "~Vertex(" << this << ")\n";
}
