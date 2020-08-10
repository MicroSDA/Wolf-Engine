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
	for (const auto& t : m_pTextures)
	{
		delete t.second.begin()->first;
	}
	m_pTextures.clear();
}

we::Resource* we::ResourceManager::Hold(const std::string& fileName, const we::WE_RESOURCE& type, const we::RHolder* holder)
{
	switch (type)
	{
	case we::MODEL3D:
		if (m_pModels3d.find(fileName) != m_pModels3d.end())
		{
			if (std::find(
				m_pModels3d.find(fileName)->second.begin()->second.begin(),
				m_pModels3d.find(fileName)->second.begin()->second.end(),
				holder) == m_pModels3d.find(fileName)->second.begin()->second.end())
			{
				m_pModels3d.find(fileName)->second.begin()->second.push_back(holder);
			}

			return m_pModels3d.find(fileName)->second.begin()->first;

		}
		else {

			we::Resource* pM = m_Loader.LoadModel("./Resources/Models/" + fileName + ".bin");
			std::map<we::Resource*, std::vector<const we::RHolder*>> el;
			el.insert(std::pair<we::Resource*, std::vector<const we::RHolder*>>(
				pM, std::vector<const we::RHolder*>{ holder }));
			m_pModels3d.insert(std::pair<std::string,
				std::map<we::Resource*,
				std::vector<const we::RHolder*>>>(fileName, el));

			return pM;
		}

		break;
	case we::SHADER:
		if (m_pShaders.find(fileName) != m_pShaders.end())
		{
			if (std::find(
				m_pShaders.find(fileName)->second.begin()->second.begin(),
				m_pShaders.find(fileName)->second.begin()->second.end(),
				holder) == m_pShaders.find(fileName)->second.begin()->second.end())
			{
				m_pShaders.find(fileName)->second.begin()->second.push_back(holder);
			}

			return m_pShaders.find(fileName)->second.begin()->first;

		}
		else {

			we::Resource* pS = new we::Shader(fileName);
			std::map<we::Resource*, std::vector<const we::RHolder*>> el;
			el.insert(std::pair<we::Resource*, std::vector<const we::RHolder*>>(
				pS, std::vector<const we::RHolder*>{ holder }));
			m_pShaders.insert(std::pair<std::string,
				std::map<we::Resource*,
				std::vector<const we::RHolder*>>>(fileName, el));

			return pS;
		}
		break;
	case we::TEXTURE:
		if (m_pTextures.find(fileName) != m_pTextures.end())
		{
			if (std::find(
				m_pTextures.find(fileName)->second.begin()->second.begin(),
				m_pTextures.find(fileName)->second.begin()->second.end(),
				holder) == m_pTextures.find(fileName)->second.begin()->second.end())
			{
				m_pTextures.find(fileName)->second.begin()->second.push_back(holder);
			}

			return m_pTextures.find(fileName)->second.begin()->first;

		}
		else {

			we::Resource* pS = m_Loader.LoadTexture("./Resources/Models/" + fileName);
			std::map<we::Resource*, std::vector<const we::RHolder*>> el;
			el.insert(std::pair<we::Resource*, std::vector<const we::RHolder*>>(
				pS, std::vector<const we::RHolder*>{ holder }));
			m_pTextures.insert(std::pair<std::string,
				std::map<we::Resource*,
				std::vector<const we::RHolder*>>>(fileName, el));

			return pS;
		}
		break;
	default:
		return nullptr;
		break;
	}
	
}

void we::ResourceManager::UnHold(const we::Resource* resource, const we::WE_RESOURCE& type, const we::RHolder* holder)
{
	switch (type)
	{
	case we::SHADER:
		for (auto it = m_pShaders.begin(); it != m_pShaders.end(); it++)
		{
			if (resource == it->second.begin()->first)
			{
				if (it->second.begin()->second.size() > 1)
				{ // This will be delited any way cose Model3d present just one
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{
						if (holder == it->second.begin()->second[m])
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
	case we::MODEL3D:
		for (auto it = m_pModels3d.begin(); it != m_pModels3d.end(); it++)
		{
			if (resource == it->second.begin()->first)
			{
				if (it->second.begin()->second.size() > 1)
				{
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{
					
						if (holder == it->second.begin()->second[m])
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
	case we::TEXTURE:
		for (auto it = m_pTextures.begin(); it != m_pTextures.end(); it++)
		{
			if (resource == it->second.begin()->first)
			{
				if (it->second.begin()->second.size() > 1)
				{
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{

						if (holder == it->second.begin()->second[m])
						{
							it->second.begin()->second.erase(it->second.begin()->second.begin() + m);
						}

					}
				}
				else {
					delete it->second.begin()->first;
					m_pTextures.erase(it);
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
void we::ResourceManager::UnHold(const std::string& fileName, const we::WE_RESOURCE& type, const we::RHolder* holder)
{
	switch (type)
	{
	case we::WE_RESOURCE::SHADER:
		for (auto it = m_pShaders.begin(); it != m_pShaders.end(); it++)
		{
			if (fileName == it->first)
			{
				if (it->second.begin()->second.size() > 1)
				{ // This will be delited any way cose Model3d present just one
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{
						if (holder == it->second.begin()->second[m])
						{
							it->second.begin()->second.erase(it->second.begin()->second.begin() + m);
						}

					}
				}
				else {
					delete it->second.begin()->first;
					m_pShaders.erase(it);
					std::cout << "Resource free(" << fileName << ")\n";
					return;
				}
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

						if (holder == it->second.begin()->second[m])
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
	case we::TEXTURE:
		for (auto it = m_pTextures.begin(); it != m_pTextures.end(); it++)
		{
			if (fileName == it->first)
			{
				if (it->second.begin()->second.size() > 1)
				{
					for (unsigned int m = 0; m < it->second.begin()->second.size(); m++)
					{

						if (holder == it->second.begin()->second[m])
						{
							it->second.begin()->second.erase(it->second.begin()->second.begin() + m);
						}

					}
				}
				else {
					delete it->second.begin()->first;
					m_pTextures.erase(it);
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

we::Resource* we::ResourceManager::Get(const std::string& fileName, const we::WE_RESOURCE& type)
{
	switch (type)
	{
	case we::MODEL3D:
		if (m_pModels3d.find(fileName) != m_pModels3d.end())
		{
			return m_pModels3d.find(fileName)->second.begin()->first;
		}
		
		break;
	case we::SHADER:
		if (m_pShaders.find(fileName) != m_pShaders.end())
		{
			return m_pShaders.find(fileName)->second.begin()->first;
		}
		
		break;
	case we::TEXTURE:
		if (m_pTextures.find(fileName) != m_pTextures.end())
		{
			return m_pTextures.find(fileName)->second.begin()->first;
		}
		break;
	default:
		return nullptr;
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
	for (const auto& t : m_pTextures)
	{
		delete t.second.begin()->first;
	}
	m_pTextures.clear();
}
