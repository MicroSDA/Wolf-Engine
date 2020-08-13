#include "GeneralLight.h"

we::GeneralLight::GeneralLight() : we::Light(),
	m_Direction(0.0f, 0.0f, 1.0f)
{
}

we::GeneralLight::~GeneralLight()
{
}

void we::GeneralLight::Process(const we::Shader& shader)
{
	
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "generalL.direction"),1,        &m_Direction[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "generalL.colorAmbient"),1,     &m_AmbientColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "generalL.colorDiffuse"),1,     &m_DiffuseColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "generalL.colorSpecular"),1,    &m_SpecularColor[0]);
	glUniform1f(glGetUniformLocation(shader.GetProgram(),  "generalL.specularIntensivity"), m_SpecularIntens);

}
