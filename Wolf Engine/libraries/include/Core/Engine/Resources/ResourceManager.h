#pragma once
#include <map>
#include <Core/Engine/Resources/ResourceLoader.h>
#include <Core/Engine/Resources/RHolder.h>

//TODO: Попробовать отказаться от Model3D и отдавать ссылку на массив мешей 
namespace we {

	enum WE_RESOURCE
	{
		SHADER,
		MODEL3D,
		TEXTURE
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
		we::Resource* Hold(const std::string &fileName, const we::WE_RESOURCE& type, const we::RHolder* holder);
		void UnHold(const we::Resource* resource, const we::WE_RESOURCE& type, const we::RHolder* holder);
		void UnHold(const std::string& fileName, const we::WE_RESOURCE& type, const we::RHolder* holder);
		we::Resource* Get(const std::string& fileName, const we::WE_RESOURCE& type);
		void Truncate();
	private:
		ResourceManager();
		ResourceManager(const ResourceManager&);
		ResourceManager& operator=(ResourceManager&);

		std::map<std::string, std::map<we::Resource*, std::vector<const we::RHolder*>>> m_pShaders;
		std::map<std::string, std::map<we::Resource*, std::vector<const we::RHolder*>>> m_pModels3d;
		std::map<std::string, std::map<we::Resource*, std::vector<const we::RHolder*>>> m_pTextures;
		we::ResourceLoader m_Loader;
	};

}
