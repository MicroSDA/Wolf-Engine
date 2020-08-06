#pragma once
#include <Utilites/SDL2/SDL.h>
#include <Utilites/GLEW/glew.h>

#include <iostream>

#define WE_DISPLAY_BASE_WIDTH  800 
#define WE_DISPLAY_BASE_HEIGHT 600 
#define WE_DISPLAY_TITLE "Wolf Engine" 

namespace we {
	/*
	* \brief Display
	*/
	class Display
	{
    public:
        static Display& GetInstance() {
            static Display  instance;
            return instance;
        }
        // Set Window title
        inline void SetTitle(const char* title) { SDL_SetWindowTitle(m_Window, title);}
        // Set clear color
        inline void SetClearColor(const float& r, const float& g, const float& b, const float& a)
        {
            m_CR = r;
            m_CG = g;
            m_CB = b;
            m_CA = a;
        }
        // Clear Window
        inline void Clear()
        {
            glClearColor(m_CR, m_CG, m_CB, m_CA);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        } 
        // Window Event input update
        void WindowControlUpdate();
        // Update Window
        void Update();
        // Destroy Window
        inline void Destroy()
        {
            
            SDL_GL_DeleteContext(m_GlContext);
            SDL_DestroyWindow(m_Window);
            SDL_Quit();
            std::cout << "~Display(\n";
            std::cout << "m_GlContext(" << &m_GlContext << ")\n";
            std::cout << "m_Window(" << &m_Window << ")\n";
            std::cout << ")" << this <<"\n";
        }
        // Set width and height size
        inline void SetSize(const int& width, const int& height)
        {
            m_Width = width;
            m_Height = height;
            Resize();
        }
        // Set width size
        inline void SetWidth(const int& width)
        {
            m_Width = width;
            Resize();
        }
        // Set height size
        inline void SetHeight(const int& height)
        {
            m_Height = height;
            Resize();
        }
        // Get width size
        inline int GetWidth() { return m_Width; }
        // Get height size
        inline int GetHeight() { return m_Height; }
        // Check if closing window has been requesetd
        inline bool IsCloseRequested() { return m_IsClosed; }
        // Get window event hendler
        inline SDL_Event& GetEventHandler() { return m_Event; }
        inline SDL_Window& GetWindowHandler() const { return *m_Window; } 
        inline void SetRenderProps(GLenum prop, bool enable) { enable ? glEnable(prop): glDisable(prop); }
    private:
        Display();
        Display(const Display&);
        Display& operator=(Display&);
        inline void Resize() 
        {
            //Set a new size for window
            SDL_SetWindowSize(m_Window, m_Width, m_Height);
            //Prepare a new centered position for window on screen
            SDL_SetWindowPosition(m_Window,
                m_DisplayMode.w / 2 - m_Width / 2,
                m_DisplayMode.h / 2 - m_Height / 2);
        };

        void InitOpengl();

        int m_Width;
        int m_Height;
        bool m_IsClosed;
        float m_CR, m_CG, m_CB, m_CA;

        SDL_Window* m_Window;
        SDL_GLContext m_GlContext;
        SDL_Event m_Event;
        SDL_DisplayMode m_DisplayMode;
    };
	
}


