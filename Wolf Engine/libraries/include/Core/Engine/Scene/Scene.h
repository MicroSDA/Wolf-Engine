#pragma once
#include <Core/Engine/Input/Input.h>
#include <Core/Engine/Util.h>
#include <Core/Engine/Resources/ResourceManager.h>
#include <Core/Engine/Render/Light/GeneralLight.h>
#include <Core/Engine/Render/Light/PointLight.h>
#include <string>

class Engine;

namespace we {

	enum SCENES
	{
		PREVIOS_SCENE,
		NEXT_SCENE
	};

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		virtual int Process() = 0;
		virtual void Render() = 0;
		//Loading shaders, some basic textures, objects and other things that necessary for the first run and rendering
		virtual void Prepare() = 0;
	protected:
		we::Display* m_Display;
		we::Input* m_Input;
		//we::ResourceManager m_ResManager;
		void SetScene(const we::SCENES& scene);
		void SetScene(const std::string& scene);
	private:

	};
}


