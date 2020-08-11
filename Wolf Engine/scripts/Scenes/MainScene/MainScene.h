#pragma once
#include <Core/Engine/Scene/Scene.h>
#include <Core/Engine/Render/Object3D/Object3D.h>
#include <map>
#include <thread>

class MainScene : public we::Scene
{
public:
	MainScene();
	~MainScene();

	int  Process();
	void Render();
	void Prepare();

	we::Camera m_Camera;
	std::vector<we::Object3D*> m_pObject3d;
	we::Light m_GeneralLight;
};