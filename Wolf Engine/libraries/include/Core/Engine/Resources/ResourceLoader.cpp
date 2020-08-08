#include "ResourceLoader.h"

we::ResourceLoader::ResourceLoader()
{
}

we::ResourceLoader::~ResourceLoader()
{
}

we::Model3D* we::ResourceLoader::LoadModel(const std::string filePath)
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

	std::vector<we::Mesh> meshes;

	meshes.resize(meshesCount);
	//Read each mesh
	for (unsigned int m = 0; m < meshesCount; m++)
	{
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

		//Read texures
		unsigned int diffusSize = 0;
		infile.read((char*)&diffusSize, sizeof(unsigned int));
		if (diffusSize != 0)
		{
			//Read difuse
			std::string diffuse;
			diffuse.resize(diffusSize);
			infile.read((char*)diffuse.c_str(), sizeof(char) * diffusSize);
			std::cout << diffuse << "\n";
		}

		unsigned int specularSize = 0;
		infile.read((char*)&specularSize, sizeof(unsigned int));
		if (specularSize != 0)
		{
			//Read specular
			std::string specular;
			specular.resize(specularSize);
			infile.read((char*)specular.c_str(), sizeof(char) * specularSize);
			std::cout << specular << "\n";
		}

		unsigned int heightMapSize = 0;
		infile.read((char*)&heightMapSize, sizeof(unsigned int));
		if (heightMapSize != 0)
		{
			//Read height map
			std::string heightMap;
			heightMap.resize(heightMapSize);
			infile.read((char*)heightMap.c_str(), sizeof(char) * heightMapSize);
			std::cout << heightMap << "\n";
		}

		unsigned int shinnesSize = 0;
		infile.read((char*)&shinnesSize, sizeof(unsigned int));
		if (shinnesSize != 0)
		{
			//Read shinnes
			std::string shinnes;
			shinnes.resize(shinnesSize);
			infile.read((char*)shinnes.c_str(), sizeof(char) * shinnesSize);
			std::cout << shinnes << "\n";
		}

		meshes[m] = we::Mesh(vertices, indices);
	}



	return new we::Model3D(meshes);
}
