#include "Material.h"

we::Material::Material() :
	m_AmbientColor(0.0, 0.0, 0.0),
	m_DiffuseColor(1.0f, 1.0f, 1.0f),
	m_SpecularColor(1.0f, 1.0f, 1.0f),
	m_SpecularPower(96.078431),
    m_Transparency(1.0)

{
}

we::Material::~Material()
{
}

void we::Material::Process(we::Shader& shader) const
{

	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "material.colorAmbient"), 1, &m_AmbientColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "material.colorDiffuse"), 1, &m_DiffuseColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "material.colorSpecular"), 1, &m_SpecularColor[0]);
	glUniform1f(glGetUniformLocation(shader.GetProgram(),  "material.specularPower"), m_SpecularPower);
	//glUniform1f(glGetUniformLocation(shader.GetProgram(),  "material.transparency"), m_Transparency);
}
