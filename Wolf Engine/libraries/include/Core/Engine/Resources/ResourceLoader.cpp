#include "ResourceLoader.h"
#include <Utilites/Image/Image.h>
#include <Core/Engine/Resources/ResourceManager.h>

we::ResourceLoader::ResourceLoader()
{
}

we::ResourceLoader::~ResourceLoader()
{
}

we::Texture* we::ResourceLoader::LoadTexture(const std::string& filePath)
{
	int width, height, numComponets;

	unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &numComponets, 4);
	
	if (imageData == NULL) {
		std::cerr << "Image loading failed for texure" << filePath << std::endl;
	}

	we::Texture* t = new we::Texture(we::ImageData({ width, height, numComponets, imageData }));

	stbi_image_free(imageData);

	return t;
}

we::Model3D* we::ResourceLoader::LoadModel(const std::string& filePath)
{
	std::ifstream infile;
	infile.open(filePath, std::ios::binary);
	// Create string buffer
	std::string buffer;
	std::string header("#Model");
	// Set buffer size as header expected
	buffer.resize(header.size());
	// Read header
	infile.read((char*)buffer.c_str(), sizeof(char) * header.size());

	if (buffer != header)
	{
		std::cerr << "Error, cannot read file - wrong header: " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}
    //Read meshes count  
	unsigned int meshesCount = 0;
	infile.read((char*)&meshesCount, sizeof(unsigned int));
	if (meshesCount == 0)
	{
		std::cerr << "Error, cannot load model - mesh count 0: " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<we::Mesh*> meshes;

	//meshes.resize(meshesCount);
	//Read each mesh
	for (unsigned int m = 0; m < meshesCount; m++)
	{
		meshes.push_back(new we::Mesh());
		//Read mesh name
		unsigned int nameSize = 0;
		infile.read((char*)&nameSize, sizeof(unsigned int));
		if (nameSize == 0)
		{
			std::cerr << "Error, cannot load model - mesh size name 0: " << filePath << std::endl;
			exit(EXIT_FAILURE);
		}

		std::string meshName;
		meshName.resize(nameSize);
		infile.read((char*)meshName.c_str(), sizeof(char) * nameSize);

		//Read vertex possition size
		unsigned int possSize = 0;
		infile.read((char*)&possSize, sizeof(unsigned int));
		if (possSize == 0)
		{
			std::cerr << "Error, cannot load model - vertices size 0: " << filePath << std::endl;
			exit(EXIT_FAILURE);
		}
		//Read vertex 
		std::vector<we::Vertex> vertices;
		vertices.resize(possSize);
		for (unsigned int p = 0; p < possSize; p++)
		{
			infile.read((char*)&vertices[p].m_Possition.x, sizeof(float));
			infile.read((char*)&vertices[p].m_Possition.y, sizeof(float));
			infile.read((char*)&vertices[p].m_Possition.z, sizeof(float));
		}
		for (unsigned int p = 0; p < possSize; p++)
		{
			infile.read((char*)&vertices[p].m_TextureCoords.x, sizeof(float));
			infile.read((char*)&vertices[p].m_TextureCoords.y, sizeof(float));
		}
		for (unsigned int p = 0; p < possSize; p++)
		{
			infile.read((char*)&vertices[p].m_Normals.x, sizeof(float));
			infile.read((char*)&vertices[p].m_Normals.y, sizeof(float));
			infile.read((char*)&vertices[p].m_Normals.z, sizeof(float));
		}
		//Read indices size
		unsigned int indicesSize = 0;
		infile.read((char*)&indicesSize, sizeof(unsigned int));
		if (indicesSize == 0)
		{
			std::cerr << "Error, cannot load model - indices size 0: " << filePath << std::endl;
			exit(EXIT_FAILURE);
		}

		std::vector<unsigned int> indices;
		indices.resize(indicesSize);
		//Read indices
		for (unsigned int i = 0; i < indicesSize; i++)
		{
			infile.read((char*)&indices[i], sizeof(unsigned int));
		}

		std::map<std::string, we::Texture*> texures;
		//Read texures
		unsigned int diffusSize = 0;
		infile.read((char*)&diffusSize, sizeof(unsigned int));
		if (diffusSize != 0)
		{
			//Read difuse
			std::string diffuse;
			diffuse.resize(diffusSize);
			infile.read((char*)diffuse.c_str(), sizeof(char) * diffusSize);
			texures.insert(
				std::pair<std::string, we::Texture*>(
					"DIFFUSE_TEXURE",
					reinterpret_cast<we::Texture*>(
						we::ResourceManager::GetInstance().Hold(
							diffuse, we::TEXTURE, meshes.back()))));
			//std::cout << diffuse << "\n";
		}

		
		unsigned int specularSize = 0;
		infile.read((char*)&specularSize, sizeof(unsigned int));
		if (specularSize != 0)
		{
			//Read specular
			std::string specular;
			specular.resize(specularSize);
			infile.read((char*)specular.c_str(), sizeof(char) * specularSize);
			texures.insert(
				std::pair<std::string, we::Texture*>(
					"SPECULAR_TEXURE",
					reinterpret_cast<we::Texture*>(
						we::ResourceManager::GetInstance().Hold(
							specular, we::TEXTURE, meshes.back()))));
		}

		unsigned int heightMapSize = 0;
		infile.read((char*)&heightMapSize, sizeof(unsigned int));
		if (heightMapSize != 0)
		{
			//Read height map
			std::string heightMap;
			heightMap.resize(heightMapSize);
			infile.read((char*)heightMap.c_str(), sizeof(char) * heightMapSize);
			texures.insert(
				std::pair<std::string, we::Texture*>(
					"NORMAL_MAP",
					reinterpret_cast<we::Texture*>(
						we::ResourceManager::GetInstance().Hold(
							heightMap, we::TEXTURE, meshes.back()))));
		}

		unsigned int shinnesSize = 0;
		infile.read((char*)&shinnesSize, sizeof(unsigned int));
		if (shinnesSize != 0)
		{
			//Read shinnes
			std::string shinnes;
			shinnes.resize(shinnesSize);
			infile.read((char*)shinnes.c_str(), sizeof(char) * shinnesSize);
			texures.insert(
				std::pair<std::string, we::Texture*>(
					"SHINES_TEXTURE",
					reinterpret_cast<we::Texture*>(
						we::ResourceManager::GetInstance().Hold(
							shinnes, we::TEXTURE, meshes.back()))));
		}

		meshes.back()->SetVertices(vertices);
		meshes.back()->SetIndices(indices);
		meshes.back()->SetTextures(texures);
		meshes.back()->Init();
	}

	return new we::Model3D(meshes);
}
