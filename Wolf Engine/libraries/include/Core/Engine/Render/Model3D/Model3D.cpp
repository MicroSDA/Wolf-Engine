#include "Model3D.h"
#include <Core/Engine/Resources/ResourceManager.h>

we::Model3D::Model3D():we::Resource(), we::RHolder()
{
	m_pShader = nullptr;

	std::cout << "Model3D(" << this << ")\n";
}

we::Model3D::Model3D(std::vector<Mesh*> meshes): we::Resource(), we::RHolder()
{
	m_pShader = reinterpret_cast<we::Shader*>(
		we::ResourceManager::GetInstance().Hold("BasicModel", we::SHADER, this)
		);

	m_Meshes = meshes;

	std::cout << "Model3D(" << this << ")\n";
}

we::Model3D::~Model3D()
{
	
	//There incorect, poiner will be nulptr and unbind will not work
	if (m_pShader != nullptr)
	{	
		we::ResourceManager::GetInstance().UnHold(m_pShader, we::SHADER, this);
		std::cout << "~Model3D(" << this << ")\n";
	}
	for (auto& m : m_Meshes)
	{
		delete m;
	}

	m_Meshes.clear();// if soter a pointer, only pointer will be delited, not referenced objects shoudl deleate all object by pointer at first
}

void we::Model3D::Draw(we::Transform& transform, we::Camera& camera, we::Light& generalLight) const
{
	m_pShader->Bind();
	m_pShader->Update(transform, camera);
	generalLight.Process(*m_pShader);

	for (unsigned int i = 0; i < m_Meshes.size(); i++) {
		/*for (unsigned int t = 0; t < m_Meshes[i].GetTexure()[t];t++)
		{
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "gBones"), (GLsizei)Transforms.size(), GL_FALSE, glm::value_ptr(Transforms[0]));
		}*/
		  m_Meshes[i]->Draw();
	}
}

void we::Model3D::AddMesh(we::Mesh mesh)
{
}

we::Mesh& we::Model3D::GetMesh()
{
	// TODO: insert return statement here
	Mesh m;
	return m;
}
