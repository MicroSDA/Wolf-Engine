#include "Object3D.h"

we::Object3D::Object3D():
	m_pModel3D(nullptr)
{

}

we::Object3D::Object3D(const we::Model3D* model)
{
	m_pModel3D = model;
}

we::Object3D::~Object3D()
{
}

void we::Object3D::Draw(we::Camera& camera)
{
	//TODO: Chech if model was deleted;
	m_pModel3D->Draw(m_Transform, camera);
}

 void we::Object3D::SetPossition(const float& x, const float& y, const float& z)
{
	m_Transform.SetPostition(glm::vec3(x, y, z));
}
 void we::Object3D::SetPossition(const glm::vec3& possition)
{
	m_Transform.SetPostition(possition);
}
 void we::Object3D::SetRotation(const float& x, const float& y, const float& z)
{
	m_Transform.SetRotation(glm::vec3(x, y, z));
}
 void we::Object3D::SetRotation(const glm::vec3& rotation)
{
	m_Transform.SetRotation(glm::vec3(rotation));
}
 void we::Object3D::SetScale(const float& x, const float& y, const float& z)
{
	m_Transform.SetScale(glm::vec3(x, y, z));
}
 void we::Object3D::SetScale(const glm::vec3& scale)
{
	m_Transform.SetScale(scale);
}
 glm::vec3 we::Object3D::GetPossition()
{
	return m_Transform.GetPosition();
}
 glm::vec3 we::Object3D::GetRotation()
{
	return m_Transform.GetRotation();
}
 glm::vec3 we::Object3D::GetScale()
{
	return m_Transform.GetScale();
}

void we::Object3D::SetModel3D(const we::Model3D* model)
{
	m_pModel3D = model;
}

