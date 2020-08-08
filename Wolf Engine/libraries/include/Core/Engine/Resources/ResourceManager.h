#pragma once
#include <map>
#include <Core/Engine/Resources/ResourceLoader.h>
#include <Core/Engine/Render/Shader/Shader.h>
#include <Core/Engine/Render/Model3D/Model3D.h>
#include <Core/Engine/Render/Drawable.h>

//class Model3D;

namespace we {

	enum WE_RESOURCE
	{
		SHADER,
		MODEL3D
	};

	class ResourceManager
	{
	public:
		static ResourceManager& GetInstance() {
			static ResourceManager  instance;
			return instance;
		}
		~ResourceManager();
		//TODO: load thrue ResourceLoader
		we::Resource* GetResource(const std::string &fileName, const we::WE_RESOURCE& resType,const we::Drawable& callObj);
		void ResourceFree(const we::Resource* resource, const we::WE_RESOURCE& resType);
		void ResourceFree(const std::string& fileName, const we::WE_RESOURCE& resType);
		void Truncate();
	private:
		ResourceManager();
		ResourceManager(const ResourceManager&);
		ResourceManager& operator=(ResourceManager&);


		std::map<std::string, we::Shader*> m_pShaders;
		//std::map<std::string, we::Model3D*> m_pModels3d;
		std::map<std::string, std::map<we::Model3D*, std::vector<const we::Drawable*>>> m_pModels3d;
		we::ResourceLoader m_Loader;
	};

}
