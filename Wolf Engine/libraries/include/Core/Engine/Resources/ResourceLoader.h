#pragma once
#include <Core/Engine/Render/Mesh/Mesh.h>

namespace we {

	class ResourceLoader
	{
	public:
		ResourceLoader();
		~ResourceLoader();

		Model* LoadModel();
	private:
	};
}


