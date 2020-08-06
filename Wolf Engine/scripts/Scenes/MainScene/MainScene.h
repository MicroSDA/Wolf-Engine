#pragma once
#include <Core/Engine/Scene/Scene.h>
#include <Core/Engine/Render/Mesh/Mesh.h>
#include <Core/Engine/Render/Shader/Shader.h>

//class Engine;

class MainScene : public we::Scene
{
public:
	MainScene();
	~MainScene();

	int  Process();
	void Render();
	void Prepare();

	we::Mesh   mesh;
	we::Shader shader;
	we::Camera camera;
};