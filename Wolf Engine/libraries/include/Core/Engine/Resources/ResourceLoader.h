#pragma once

#include <Core/Engine/Render/Mesh/Mesh.h>
#include <Core/Engine/Render/Model3D/Model3D.h>
#include <Core/Engine/Render/Texture/Texture.h>
#include <Utilites/Binarizer/Binarizer.h>
#include <Utilites/Image/Image.h>
#include <iostream>




class ResourceManager;

namespace we {

	class ResourceLoader
	{
	public:
		ResourceLoader();
		~ResourceLoader();
		we::Model3D* LoadModel(const std::string& filePath);
		we::Texture* LoadTexture(const std::string& filePath);
	private:
	};
}


