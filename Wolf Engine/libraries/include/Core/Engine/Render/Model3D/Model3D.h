#pragma once
#include <Core/Engine/Render/Mesh/Mesh.h>
#include <iostream>

namespace we {

	class Model3D
	{
	public:
		Model3D();
		Model3D(std::vector<Mesh> meshes);
		~Model3D();
		void Draw();

		void AddMesh(we::Mesh mesh);
		we::Mesh& GetMesh();
	private:
		std::vector<Mesh> m_Meshes;
	};
}


