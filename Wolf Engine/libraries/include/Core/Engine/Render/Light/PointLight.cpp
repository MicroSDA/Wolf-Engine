#include "PointLight.h"

we::PointLight::PointLight():we::Light(),
    m_Position(0.0f, 0.0f, -10.0f),
	m_Constant(1.0f),
	m_Linear(0.000001),
	m_Qaudratic(0.00000001)
{
}

we::PointLight::~PointLight()
{
}

void we::PointLight::Process(const we::Shader& shader)
{
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].position"), 1,        &m_Position[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorAmbient"), 1,    &m_AmbientColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorDiffuse"), 1,    &m_DiffuseColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorSpecular"), 1,   &m_SpecularColor[0]);
	glUniform1f(glGetUniformLocation(shader.GetProgram(),  "pointL[0].specularIntensivity"), m_SpecularIntens);
	glUniform1f(glGetUniformLocation(shader.GetProgram(),  "pointL[0].constant"),            m_Constant);
	glUniform1f(glGetUniformLocation(shader.GetProgram(),  "pointL[0].linear"),              m_Linear);
	glUniform1f(glGetUniformLocation(shader.GetProgram(),  "pointL[0].qaudratic"),           m_Qaudratic);
}
