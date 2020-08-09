#include "Engine.h"

void we::Engine::Start()
{
    // Read configs and set scenes
    m_Scenes.insert(std::pair<std::string, we::Scene*>("MainScene", new MainScene()));

    // Prepare values
    Prepare();
    Run();
}

void we::Engine::Stop()
{
    if (m_State == WE_FORCE_EXIT)
        return;

    m_State = WE_FORCE_EXIT;
    CleanUp();
}

void we::Engine::Run()
{
  
    while (!m_Display->IsCloseRequested() && m_State == WE_RUNNING)
    {
        m_Display->UpdateTime();

        while (SDL_PollEvent(&m_Display->GetEventHandler()))
        {
            m_Display->WindowControlUpdate();
        }

        m_Input->Update();
        //////////////////////////////////////////
        SceneProcess(m_Scenes[m_CurrentScene]->Process());
        /////////////////////////////////////////
        Render();

      
    }
       
    Stop();
   
}

void we::Engine::Render()
{
    if (m_State == WE_FORCE_EXIT)
        return;

    m_Display->Clear();

    m_Scenes[m_CurrentScene]->Render();

    m_Display->Update();
}

void we::Engine::Prepare()
{
    m_CurrentScene = m_Scenes.begin()->first;
}

void we::Engine::SceneProcess(const int& stateKey)
{
    switch (stateKey)
    {
    case WE_FORCE_EXIT:
        Stop();
        break;
    default:
        //TODO: nothig yeat
        break;
    }
}

void we::Engine::CleanUp()
{
     std::cout << "Engine::CleanUp()\n";
     m_Display->Destroy();
     for (const auto& e : m_Scenes)
     {
          delete e.second;
     }

     m_Scenes.clear();

}

void we::Engine::SetCurrentScene(const int& scene)
{

    std::map<std::string, Scene*>::iterator current = m_Scenes.find(m_CurrentScene);

    switch (scene)
    {
    case 0:
        // PREVIOS_SCENE
        current--;
        if (current != m_Scenes.end())
        {
            m_CurrentScene = *(current)->first.data();
        }
        else { std::cout << "Scene Not found\n"; }
        break;
    case 1:
        // NEXT_SCENE
        current++;
        if (current != m_Scenes.end())
        {
            m_CurrentScene = *(current)->first.data();
        }
        else { std::cout << "Scene Not found\n"; }
        break;
    default:
        break;
    }
}

we::Engine::Engine()
{
    m_Display = &we::Display::GetInstance();
    m_Input = &we::Input::GetInstance();
    m_CurrentScene = "Undefined";
    m_State = WE_RUNNING;
}
