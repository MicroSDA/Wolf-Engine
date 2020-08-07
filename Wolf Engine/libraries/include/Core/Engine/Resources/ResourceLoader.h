#pragma once
#include <Core/Engine/Render/Mesh/Mesh.h>
#include <Core/Engine/Render/Model3D/Model3D.h>
#include <iostream>
#include <fstream>

namespace we {

	class ResourceLoader
	{
	public:
		ResourceLoader();
		~ResourceLoader();

		Model3D* LoadModel(const std::string filePath);
	private:
	};
}


