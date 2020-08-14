#include "ResourceLoader.h"
#include <Utilites/Image/Image.h>
#include <Core/Engine/Resources/ResourceManager.h>
#include <thread>
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

	std::ifstream _File;
	_File.open(filePath, std::ios::binary);

	if (MODEL3D_HEADER != we::Binarizer::ReadString(_File, sizeof(MODEL3D_HEADER - 1))) {
		std::cerr << "Error, cannot read file - wrong header: " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}

	unsigned int _MeshCount = we::Binarizer::ReadUint(_File);
	if (_MeshCount == 0) {
		std::cerr << "Error, cannot load model - mesh count 0: " << filePath << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<we::Mesh*> _Meshes;
	for (unsigned int m = 0; m < _MeshCount; m++) {

		_Meshes.push_back(new we::Mesh());
		std::string name = we::Binarizer::ReadString(_File,
			we::Binarizer::ReadUint(_File));

		unsigned int _VertexCount = we::Binarizer::ReadUint(_File);
		if (_VertexCount == 0) {
			std::cerr << "Error, cannot load model - vertices count 0: " << filePath << std::endl;
			exit(EXIT_FAILURE);
		}

		std::vector<we::Vertex> _Vertices;
		_Vertices.resize(_VertexCount);
		for (unsigned int v = 0; v < _VertexCount; v++) {
			//Possition with one s :)))
			_Vertices[v].m_Possition.x = we::Binarizer::ReadFloat(_File);
			_Vertices[v].m_Possition.y = we::Binarizer::ReadFloat(_File);
			_Vertices[v].m_Possition.z = we::Binarizer::ReadFloat(_File);

			_Vertices[v].m_TextureCoords.x = we::Binarizer::ReadFloat(_File);
			_Vertices[v].m_TextureCoords.y = we::Binarizer::ReadFloat(_File);

			_Vertices[v].m_Normals.x = we::Binarizer::ReadFloat(_File);
			_Vertices[v].m_Normals.y = we::Binarizer::ReadFloat(_File);
			_Vertices[v].m_Normals.z = we::Binarizer::ReadFloat(_File);

		}
		unsigned int _IndicesCount = we::Binarizer::ReadUint(_File);
		if (_IndicesCount == 0) {
			std::cerr << "Error, cannot load model - indices size 0: " << filePath << std::endl;
			exit(EXIT_FAILURE);
		}

		std::vector<unsigned int> _Indices;
		_Indices.resize(_IndicesCount);
		for (unsigned int i = 0; i < _IndicesCount; i++) {
			_Indices[i] = we::Binarizer::ReadUint(_File);
		}

		//!issue ���� ������ ���������� ������ ��� ���� ��� �� �� ������� ������� ��� �������� ��������� ����������
		//��� ��� �� � ����� ���������� ��� ��� �� � ��������, ��������� �� ���� �� ������ ���� �������� ��� � ���� ������� �������� ������ �� �����. � ��� ������ ��� ������ �������, ���� ��������� �� �������� ����� ������� 
		//���� ��� ����� �� �� ��� ����� �������� 
		std::vector<we::Texture*> _Textures;
		//Max textures is 4 for now
		for (unsigned int t = 1; t < MAX_TEXTURES_COUNT; t++)
		{
			unsigned int _NameSize = we::Binarizer::ReadUint(_File);
			std::string _Name = we::Binarizer::ReadString(_File, _NameSize);
			we::Texture* _Texture;
			if (_NameSize > 0) {
				_Texture = reinterpret_cast<we::Texture*>(we::ResourceManager::GetInstance().Hold(_Name, we::TEXTURE, _Meshes.back()));
				_Texture->SetType(we::TEXTURES(t));
				_Textures.push_back(_Texture);
			}
			else {
				_Texture = reinterpret_cast<we::Texture*>(we::ResourceManager::GetInstance().Hold("undefined.png", we::TEXTURE, _Meshes.back()));
				_Texture->SetType(we::TEXTURES(t));
				_Textures.push_back(_Texture);
			}
		}

		we::Material _Material;
		glm::vec3 _ColorProperty(we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File));
		_Material.SetAmbientColor(_ColorProperty);// Ambient
		_ColorProperty = glm::vec3(we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File));
		_Material.SetDiffuseColor(_ColorProperty);// Diffues
		_ColorProperty = glm::vec3(we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File));
		_Material.SetSpecularColor(_ColorProperty);// Specular
		_ColorProperty = glm::vec3(we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File), we::Binarizer::ReadFloat(_File));
		_Material.SetTransparentMask(_ColorProperty);// Transparent mask
		_Material.SetShinines(we::Binarizer::ReadFloat(_File));// Shinines

		_Meshes.back()->SetVertices(_Vertices);
		_Meshes.back()->SetIndices(_Indices);
		_Meshes.back()->SetTextures(_Textures);
		_Meshes.back()->SetMaterial(_Material);
		_Meshes.back()->Init();

		
	}
	
	_File.close();
	return new we::Model3D(_Meshes);
}


