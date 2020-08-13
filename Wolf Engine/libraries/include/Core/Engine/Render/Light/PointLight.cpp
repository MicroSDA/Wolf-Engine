#include "PointLight.h"
#include <string>
we::PointLight::PointLight(int id):we::Light(),
    m_Position(0.0f, 0.0f, 0.0f),
	m_Constant(0.1f),
	m_Linear(0.01),
	m_Qaudratic(0.001),
	m_Id(id)
{
}

we::PointLight::~PointLight()
{
}

void we::PointLight::Process(const we::Shader& shader)
{

	
    glUniform1i(glGetUniformLocation(shader.GetProgram(), "POINT_LIGHTS_COUNT"),  m_Id + 1);
	char index[64];
	memset(index, 0, sizeof(index));

	_snprintf_s(index, sizeof(index), "pointL[%i].position", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1,       &m_Position[0]);
	_snprintf_s(index, sizeof(index), "pointL[%i].colorAmbient", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1,       &m_AmbientColor[0]);
	_snprintf_s(index, sizeof(index), "pointL[%i].colorDiffuse", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1,       &m_DiffuseColor[0]);
	_snprintf_s(index, sizeof(index), "pointL[%i].colorSpecular", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1,       &m_SpecularColor[0]);
	_snprintf_s(index, sizeof(index), "pointL[%i].specularIntensivity", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index),            m_SpecularIntens);
	_snprintf_s(index, sizeof(index), "pointL[%i].constant", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index),            m_Constant);
	_snprintf_s(index, sizeof(index), "pointL[%i].linear", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index),            m_Linear);
	_snprintf_s(index, sizeof(index), "pointL[%i].qaudratic", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index),            m_Qaudratic);


	/*glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].position"), 1, &m_Position[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorAmbient"), 1, &m_AmbientColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorDiffuse"), 1, &m_DiffuseColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorSpecular"), 1, &m_SpecularColor[0]);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].specularIntensivity"), m_SpecularIntens);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].constant"), m_Constant);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].linear"), m_Linear);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].qaudratic"), m_Qaudratic);*/
}
