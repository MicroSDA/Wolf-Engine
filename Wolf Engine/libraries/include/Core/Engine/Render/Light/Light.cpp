#include "Light.h"

we::Light::Light():
	m_AmbientColor(0.1, 0.1, 0.1),
	m_DiffuseColor(1.0f, 1.0f, 1.0f),
	m_SpecularColor(1.0f, 1.0f, 1.0f),
	m_ShininesStrength(1.0)
{
}

we::Light::~Light()
{
}
