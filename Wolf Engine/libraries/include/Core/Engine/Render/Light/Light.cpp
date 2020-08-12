#include "Light.h"

we::Light::Light():
	m_AmbientColor(0.1, 0.1, 0.1),
	m_DiffuseColor(1.5f, 1.5f, 1.5f),
	m_SpecularColor(1.0f, 1.0f, 1.0f),
	m_SpecularIntens(3.0f)
{
}

we::Light::~Light()
{
}
