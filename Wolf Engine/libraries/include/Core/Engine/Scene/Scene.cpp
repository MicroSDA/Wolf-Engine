#include "Scene.h"
#include <Core/Engine/Engine.h>

we::Scene::Scene()
{
    m_Display = &we::Display::GetInstance();
    m_Input = &we::Input::GetInstance();
}

we::Scene::~Scene()
{
    std::cout << "~Scene("<<this<<")\n";
}

void we::Scene::SetScene(const we::SCENES& scene)
{
    we::Engine::getInstance().SetCurrentScene(scene);
}

void we::Scene::SetScene(const std::string& scene)
{
    we::Engine::getInstance().SetCurrentScene(scene);
}
