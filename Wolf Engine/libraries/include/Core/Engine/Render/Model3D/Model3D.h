#pragma once
#include <Core/Engine/Render/Mesh/Mesh.h>
#include <Core/Engine/Render/Shader/Shader.h>
#include <Core/Engine/Resources/RHolder.h>
#include <Core/Engine/Render/Light/GeneralLight.h>
#include <iostream>
class ResourceManager;

namespace we {

	class Model3D : public we::Resource, public we::RHolder
	{
	public:
		Model3D();
		Model3D(std::vector<we::Mesh*> meshes);
		~Model3D();
		void Draw(we::Transform& transform, we::Camera& camera, std::vector<we::Light*>& lightSources) const;

		void AddMesh(we::Mesh mesh);
		we::Mesh& GetMesh();
	private:
		std::vector<we::Mesh*> m_Meshes;
		we::Shader* m_pShader;
	};
}


