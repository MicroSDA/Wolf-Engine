#include "Light.h"

we::Light::Light():
	m_Direction(0.0f, 0.0f, -1.0f),
	m_AmbientColor(0.0f, 0.0f, 0.0f),
	m_DiffuseColor(1.0f, 1.0f, 1.0f),
	m_SpecularColor(1.0f, 1.0f, 1.0f)

{
}

we::Light::~Light()
{
}

void we::Light::Process(const we::Shader& shader)
{
	glUniform3fv(7,  1, &m_Direction[0]);
	glUniform3fv(8,  1, &m_AmbientColor[0]);
	glUniform3fv(9,  1, &m_DiffuseColor[0]);
	glUniform3fv(10, 1, &m_SpecularColor[0]);
}
