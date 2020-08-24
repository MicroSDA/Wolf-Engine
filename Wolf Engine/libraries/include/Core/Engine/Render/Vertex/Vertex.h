#pragma once
#include <Utilites/Math/glm/glm.hpp>
#include <Utilites/GLEW/glew.h>
#include <iostream>

namespace we {

	class Vertex
	{
	public:
		Vertex();
		Vertex(const glm::vec3& position,
			const glm::vec2& textureCoords,
			const glm::vec3& normals,
			const glm::vec3& tangents,
			const unsigned int& id);
		Vertex(const float& positionX,
			const float& positionY,
			const float& positionZ,
			const float& textureCoordX,
			const float& textureCoordY,
			const float& normalX,
			const float& normalY,
			const float& normalZ,
			const float& tangentX,
			const float& tangentY,
			const float& tangentZ,
			const unsigned int& id);
		~Vertex();

		glm::vec3 m_Position;
		glm::vec2 m_TextureCoords;
		glm::vec3 m_Normals;
		glm::vec3 m_Tangents;
		unsigned int m_Id;
	};
}


