#include "Model3D.h"

we::Model3D::Model3D()
{
}

we::Model3D::Model3D(std::vector<Mesh> meshes)
{
	m_Meshes = meshes;
}

we::Model3D::~Model3D()
{
	std::cout << "~Model3D(" << this << ")\n";
}

void we::Model3D::Draw()
{
	for (unsigned int i = 0; i < m_Meshes.size(); i++) {
		  m_Meshes[i].Draw();
	}
}

void we::Model3D::AddMesh(we::Mesh mesh)
{
}

we::Mesh& we::Model3D::GetMesh()
{
	// TODO: insert return statement here
	Mesh m;
	return m;
}
