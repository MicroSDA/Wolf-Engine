#include "Material.h"

we::Material::Material() :
	m_AmbientColor(0.0, 0.0, 0.0),
	m_DiffuseColor(0.64f, 0.64f, 0.64f),
	m_SpecularColor(0.5f, 0.5f, 0.5f),
	m_SpecularPower(96.078431),
    m_Transparency(1.0)

{
}

we::Material::~Material()
{
}

void we::Material::Process() const
{
	
	glUniform3fv(12, 1, &m_AmbientColor[0]);
	glUniform3fv(13, 1, &m_DiffuseColor[0]);
	glUniform3fv(14, 1, &m_SpecularColor[0]);
	glUniform1f(15,     m_SpecularPower);
	//glUniform1f(16,     m_Transparency);

}
