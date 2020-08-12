#include "Mesh.h"
#include <Core/Engine/Resources/ResourceManager.h>

we::Mesh::Mesh() :we::RHolder()
{
    VAO = NULL;
    VBO = NULL;
    EBO = NULL;

	m_Name = "undefined";

}

we::Mesh::Mesh(const we::Mesh& other): we::RHolder()
{
    m_Vertices = other.m_Vertices;
	m_Indices = other.m_Indices;
	m_pTextures = other.m_pTextures;

    VAO = NULL;
    VBO = NULL;
    EBO = NULL;

	m_Name = "undefined";

	//Init();
}

we::Mesh::Mesh(const std::vector<we::Vertex>& vertices,
	           const std::vector<unsigned int>& indices
	           ): we::RHolder()
{
    m_Vertices = vertices;
	m_Indices = indices;

    VAO = NULL;
    VBO = NULL;
    EBO = NULL;

	m_Name = "undefined";

	//Init();
}

we::Mesh::~Mesh()
{
	std::cout << "~Mesh(" << this <<")\n";
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	m_Vertices.clear();
	m_Indices.clear();

	for (auto& t : m_pTextures)
	{
		we::ResourceManager::GetInstance().UnHold(t.second, we::TEXTURE, this);
		
	}
	m_pTextures.clear();
}

void we::Mesh::Draw() const
{
	
	unsigned int id = 0;
	for (auto& t : m_pTextures)
	{
		//Different ids for dif, spec, normal etc. cos they could not be inserted
		t.second->Bind(id);
		id++;
	}

	m_Material.Process();

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//Bind current arry to 0 for safe behavior
	glBindVertexArray(0);
}

void we::Mesh::Init()
{
	if (m_Vertices.size() == 0)
		return;

	glGenVertexArrays(1, &VAO);// Generate 1280 error GL_INVALID_ENUM, ignor, glew is broken
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// Load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(we::Vertex), &m_Vertices[0], GL_STATIC_DRAW);
	// Set the vertex attribute pointers in the VBO buffer
	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(we::Vertex), (GLvoid*)0);
	// Vertex Texture Coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(we::Vertex), (GLvoid*)offsetof(we::Vertex, m_TextureCoords));
	// Vertex Normals
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(we::Vertex), (GLvoid*)offsetof(we::Vertex, m_Normals));
	// Set the indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(GLuint), &m_Indices[0], GL_STATIC_DRAW);

	//Bind current arry to 0 for safe behavior
	glBindVertexArray(0);

}
