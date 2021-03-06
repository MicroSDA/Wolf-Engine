#include "SpotLight.h"

we::SpotLight::SpotLight(int id): we::PointLight(id),
    m_Direction(0.0, 0.0f, 1.0f),
	m_MinAngle(glm::cos(glm::radians(5.0f))),
    m_MaxAngle(glm::cos(glm::radians(7.0f)))
{
}

we::SpotLight::~SpotLight()
{
}
void we::SpotLight::Process(const we::Shader& shader)
{
	glUniform1i(glGetUniformLocation(shader.GetProgram(), "SPOT_LIGHTS_COUNT"), m_Id + 1);
	char index[64];
	memset(index, 0, sizeof(index));

	_snprintf_s(index, sizeof(index), "spotL[%i].direction", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1, &m_Direction[0]);
	_snprintf_s(index, sizeof(index), "spotL[%i].position", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1, &m_Position[0]);
	_snprintf_s(index, sizeof(index), "spotL[%i].colorAmbient", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1, &m_AmbientColor[0]);
	_snprintf_s(index, sizeof(index), "spotL[%i].colorDiffuse", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1, &m_DiffuseColor[0]);
	_snprintf_s(index, sizeof(index), "spotL[%i].colorSpecular", m_Id);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), index), 1, &m_SpecularColor[0]);
	_snprintf_s(index, sizeof(index), "spotL[%i].shininesStrength", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index), m_ShininesStrength);
	_snprintf_s(index, sizeof(index), "spotL[%i].constant", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index), m_Constant);
	_snprintf_s(index, sizeof(index), "spotL[%i].linear", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index), m_Linear);
	_snprintf_s(index, sizeof(index), "spotL[%i].qaudratic", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index), m_Qaudratic);
	_snprintf_s(index, sizeof(index), "spotL[%i].minAngle", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index), m_MinAngle);
	_snprintf_s(index, sizeof(index), "spotL[%i].maxAngle", m_Id);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), index), m_MaxAngle);

	/*glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].position"), 1, &m_Position[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorAmbient"), 1, &m_AmbientColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorDiffuse"), 1, &m_DiffuseColor[0]);
	glUniform3fv(glGetUniformLocation(shader.GetProgram(), "pointL[0].colorSpecular"), 1, &m_SpecularColor[0]);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].specularIntensivity"), m_SpecularIntens);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].constant"), m_Constant);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].linear"), m_Linear);
	glUniform1f(glGetUniformLocation(shader.GetProgram(), "pointL[0].qaudratic"), m_Qaudratic);*/
}
