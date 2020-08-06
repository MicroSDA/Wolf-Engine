#pragma once
#include <Core/Engine/Render/Display/Display.h>
#include <Core/Engine/Input/Input.h>
#include <Scenes/SceneRegister.h>
#include <Core/Engine/Util.h>
#include <map>



namespace we {
    
    /*
     * \brief Main engine object
     */
	class Engine
	{

	public:
        static Engine& getInstance() {
            static Engine  instance;
            return instance;
        }

        /* \brief 
         * \param 
         */
       
        // Start Engine
        void Start();
        // Stop Engine
        void Stop();
        // Run Engine
        void Run();
        // Clean up Engine
        void CleanUp();
        // Sec Current Scene
        void SetCurrentScene(const int& scene);
        // Sec Current Scene
        inline void SetCurrentScene(const std::string sceneName)
        { m_Scenes.find(sceneName) != m_Scenes.end() ? m_CurrentScene = sceneName : m_CurrentScene; }

    private:
        Engine();
        Engine(const Engine&);
        Engine& operator=(Engine&);

        // Render Engine
        void Render();
        void Prepare();
        void SceneProcess(const int& stateKey);
        std::map<std::string, Scene*> m_Scenes;
        std::string m_CurrentScene;
        we::Display* m_Display;
        we::Input* m_Input;
        int m_State;
	};
}
