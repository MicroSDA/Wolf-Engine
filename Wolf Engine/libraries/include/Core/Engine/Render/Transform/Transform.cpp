#include "Transform.h"

we::Transform::Transform()
{
	m_Possition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Rotation  = glm::vec3(0.0f, 0.0f, 0.0f);
	m_Scale     = glm::vec3(1.0f, 1.0f, 1.0f);
}

we::Transform::~Transform()
{
}
