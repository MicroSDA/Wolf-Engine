#pragma once
#include <Core/Engine/Render/Drawable.h>
#include <Core/Engine/Render/Mesh/Mesh.h>
namespace we {

	class Object3D : public Drawable
	{
	public:
		Object3D();
        virtual ~Object3D();

	
	private:
		
		std::vector<we::Mesh*> m_Meshes;
	};
}


