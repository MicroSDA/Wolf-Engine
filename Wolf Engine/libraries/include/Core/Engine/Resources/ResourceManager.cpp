#include "ResourceManager.h"


we::ResourceManager::ResourceManager()
{

}

we::ResourceManager::~ResourceManager()
{
	for (const auto& s : m_pShaders)
	{
		delete s.second.begin()->first;
	}
	m_pShaders.clear();

	for (const auto& m : m_pModels3d)
	{
		delete m.second.begin()->first;
	}
	m_pModels3d.clear();
}

we::Resource* we::ResourceManager::GetResource(const std::string& fileName, we::Object3D* callObj)
{
	if (m_pModels3d.find(fileName) != m_pModels3d.end())
	{
		if (std::find(
			m_pModels3d.find(fileName)->second.begin()->second.begin(),
			m_pModels3d.find(fileName)->second.begin()->second.end(),
			callObj) == m_pModels3d.find(fileName)->second.begin()->second.end())
		{
			m_pModels3d.find(fileName)->second.begin()->second.push_back(callObj);
		}

		return m_pModels3d.find(fileName)->second.begin()->first;

	}
	else {

		Model3D* pM = m_Loader.LoadModel("./Resources/Models/" + fileName + ".bin");
		std::map<we::Resource*, std::vector<we::Object3D*>> el;
		el.insert(std::pair<we::Resource*, std::vector<we::Object3D*>>(
			pM, std::vector<we::Object3D*>{ callObj }));
		m_pModels3d.insert(std::pair<std::string,
			std::map<we::Resource*,
			std::vector<we::Object3D*>>>(fileName, el));

		return pM;
	}

}

we::Resource* we::ResourceManager::GetResource(const std::string& fileName, we::Model3D* callObj)
{

	if (m_pShaders.find(fileName) != m_pShaders.end())
	{
		if (std::find(
			m_pShaders.find(fileName)->second.begin()->second.begin(),
			m_pShaders.find(fileName)->second.begin()->second.end(),
			callObj) == m_pShaders.find(fileName)->second.begin()->second.end())
		{
			m_pShaders.find(fileName)->second.begin()->second.push_back(callObj);
		}

		return m_pShaders.find(fileName)->second.begin()->first;

	}
	else {

		we::Shader* pS = new we::Shader(fileName);
		std::map<we::Shader*, std::vector<we::Model3D*>> el;
		el.insert(std::pair<we::Shader*, std::vector<we::Model3D*>>(
			pS, std::vector<we::Model3D*>{ callObj }));
		m_pShaders.insert(std::pair<std::string,
			std::map<we::Shader*,
			std::vector<we::Model3D*>>>(fileName, el));

		return pS;
	}

}

void we::ResourceManager::ResourceFree(const we::Resource* resource, const we::WE_RESOURCE& resType, we::Object3D* callObject)
{
	switch (resType)
	{
	case we::WE_RESOURCE::SHADER:

		for (auto it = m_pShaders.begin(); it != m_pShaders.end(); it++)
		{
			if (resource == it->second.begin()->first)
			{
				delete it->second.begin()->first;
				m_pShaders.erase(it);
				std::cout << "Resource free(" << resource << ")\n";
				return;
			}

		}
		break;
	case we::WE_RESOURCE::MODEL3D:
		for (auto it = m_pModels3d.begin(); it != m_pModels3d.end(); it++)
		{
			if (resource == it->second.begin()->first)
			{
				if (it->second.begin()->second.size() > 1)
				{
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{
					
						if (callObject == it->second.begin()->second[m])
						{
							it->second.begin()->second.erase(it->second.begin()->second.begin() + m);
						}

					}
				}
				else {
					delete it->second.begin()->first;
					m_pModels3d.erase(it);
					std::cout << "Resource free(" << resource << ")\n";
					return;
				}
			}
		}
		break;
	default:
		break;
	}
}
void we::ResourceManager::ResourceFree(const we::Resource* resource, const we::WE_RESOURCE& resType, we::Model3D* callObject)
{
	
	switch (resType)
	{
	case we::WE_RESOURCE::SHADER:
		for (auto it = m_pShaders.begin(); it != m_pShaders.end(); it++)
		{
			if (resource == it->second.begin()->first)
			{
				if (it->second.begin()->second.size() > 1)
				{ // This will be delited any way cose Model3d present just one
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{
						if (callObject == it->second.begin()->second[m])
						{
							it->second.begin()->second.erase(it->second.begin()->second.begin() + m);
						}

					}
				}
				else {
					delete it->second.begin()->first;
					m_pShaders.erase(it);
					std::cout << "Resource free(" << resource << ")\n";
					return;
				}
			}
		}
		break;
	case we::WE_RESOURCE::MODEL3D:
		
	default:
		break;
	}
}

void we::ResourceManager::ResourceFree(const std::string& fileName, const we::WE_RESOURCE& resType, we::Object3D* callObject)
{
	switch (resType)
	{
	case we::WE_RESOURCE::SHADER:

		for (auto it = m_pShaders.begin(); it != m_pShaders.end(); it++)
		{
			if (fileName == it->first)
			{
				delete it->second.begin()->first;
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
				if (it->second.begin()->second.size() > 1)
				{
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{
						if (callObject == it->second.begin()->second[m])
						{
							it->second.begin()->second.erase(it->second.begin()->second.begin() + m);
						}
						
					}
				}
				else {
					delete it->second.begin()->first;
					m_pModels3d.erase(it);
					std::cout << "Resource free(" << fileName << ")\n";
					return;
				}
			}
		}
		break;
	default:
		break;
	}
}

void we::ResourceManager::Truncate()
{
	for (const auto& s : m_pShaders)
	{
		delete s.second.begin()->first;
	}
	m_pShaders.clear();

	for (const auto& m : m_pModels3d)
	{
		delete m.second.begin()->first;
	}
	m_pModels3d.clear();
}
