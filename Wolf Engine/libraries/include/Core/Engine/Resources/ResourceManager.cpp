#include "ResourceManager.h"


we::ResourceManager::ResourceManager()
{

}

we::ResourceManager::~ResourceManager()
{
	/*for (const auto& s : m_pShaders)
	{
		delete s.second;
	}
	m_pShaders.clear();

	for (const auto& m : m_pModels3d)
	{
		delete m.second;
	}*/
	m_pModels3d.clear();
}

we::Resource* we::ResourceManager::GetResource(const std::string& fileName, const we::WE_RESOURCE& resType, const we::Drawable& callObj)
{
	switch (resType)
	{
	case we::WE_RESOURCE::SHADER:

		if (m_pShaders.find(fileName) != m_pShaders.end())
		{

			return m_pShaders.find(fileName)->second;

		}else{

			Shader* pS = new we::Shader(fileName);
			m_pShaders.insert(std::pair<std::string, we::Shader*>(fileName, pS));
			return pS;
		}
	
		break;
	case we::WE_RESOURCE::MODEL3D:
		//TODO: check if this works correct;

		if (m_pModels3d.find(fileName) != m_pModels3d.end())
		{
            if (std::find(
				m_pModels3d.find(fileName)->second.begin()->second.begin(),
				m_pModels3d.find(fileName)->second.begin()->second.end(),
				&callObj) == m_pModels3d.find(fileName)->second.begin()->second.end())
			{
				m_pModels3d.find(fileName)->second.begin()->second.push_back(&callObj);
			}

			return m_pModels3d.find(fileName)->second.begin()->first;

		}
		else {

			Model3D* pM = m_Loader.LoadModel("./Resources/Models/" + fileName + ".bin");
			std::map<we::Model3D*, std::vector<const we::Drawable*>> el;
			el.insert(std::pair<we::Model3D*, std::vector<const we::Drawable*>>(
				pM, std::vector<const we::Drawable*>{ &callObj }));
			m_pModels3d.insert(std::pair<std::string,
				std::map<we::Model3D*,
				std::vector<const we::Drawable*>>>(fileName, el));

			return pM;
		}
		break;
	default:
		return nullptr;
		break;
	}
}

void we::ResourceManager::ResourceFree(const we::Resource* resource, const we::WE_RESOURCE& resType)
{
	/*switch (resType)
	{
	case we::WE_RESOURCE::SHADER:

		for (auto it = m_pShaders.begin(); it != m_pShaders.end(); it++)
		{
			if (resource == it->second)
			{
				delete it->second;
				m_pShaders.erase(it);
				std::cout << "Resource free(" << resource << ")\n";
				return;
			}

		}
		break;
	case we::WE_RESOURCE::MODEL3D:
		for (auto it = m_pModels3d.begin(); it != m_pModels3d.end(); it++)
		{
			if (resource == it->second)
			{
				delete it->second;
				m_pModels3d.erase(it);
				std::cout << "Resource free(" << resource << ")\n";
				return;
			}
		}
		break;
	default:
		break;
	}*/
}

void we::ResourceManager::ResourceFree(const std::string& fileName, const we::WE_RESOURCE& resType)
{
	/*switch (resType)
	{
	case we::WE_RESOURCE::SHADER:

		for (auto it = m_pShaders.begin(); it != m_pShaders.end(); it++)
		{
			if (fileName == it->first)
			{
				delete it->second;
				m_pShaders.erase(it);
				std::cout << "Resource free(" << fileName << ")\n";
				return;
			}

		}
		break;
	case we::WE_RESOURCE::MODEL3D:
		for (auto it = m_pModels3d.begin(); it != m_pModels3d.end(); it++)
		{
			if (fileName == it->first)
			{
				delete it->second;
				m_pModels3d.erase(it);
				std::cout << "Resource free(" << fileName << ")\n";
				return;
			}
		}
		break;
	default:
		break;
	}*/
}

void we::ResourceManager::Truncate()
{
	/*for (const auto& s : m_pShaders)
	{
		delete s.second;
	}
	m_pShaders.clear();

	for (const auto& m : m_pModels3d)
	{
		delete m.second;
	}
	m_pModels3d.clear();*/
}
