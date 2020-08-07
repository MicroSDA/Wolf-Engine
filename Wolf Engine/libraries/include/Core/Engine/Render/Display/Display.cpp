#include "Display.h"

we::Display::Display()
{
	m_Width = WE_DISPLAY_BASE_WIDTH;
	m_Height = WE_DISPLAY_BASE_HEIGHT;
	m_IsClosed = false;
	//Default window clear color
	m_CR = 0.0f;
	m_CG = 0.0f;
	m_CB = 0.0f;
	m_CA = 1.0f;

	m_TimeNow = SDL_GetPerformanceCounter();
	m_TimeLast = 0;
	m_DeltaTime = 0.0f;


	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GetCurrentDisplayMode(0, &m_DisplayMode);
	m_Window = SDL_CreateWindow(
		WE_DISPLAY_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Width,
		m_Height, SDL_WINDOW_OPENGL);
	m_GlContext = SDL_GL_CreateContext(m_Window);

	SDL_ShowCursor(true);

	//glewExperimental = GL_TRUE;

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		std::cerr << "Glew fialed to initialize" << std::endl;
	}

	InitOpengl();

	SDL_PollEvent(&m_Event);
	
}

void we::Display::InitOpengl()
{
	SetRenderProps(GL_DEPTH_TEST, true);
	SetRenderProps(GL_CULL_FACE, true);
	glCullFace(GL_BACK);
	//glFrontFace(GL_FRONT);
}

void we::Display::WindowControlUpdate()
{
	if (m_Event.type == SDL_QUIT)
	{
		m_IsClosed = true;
	}
}

void we::Display::Update()
{
	SDL_GL_SwapWindow(m_Window);

	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
	{ 
		std::cout << err << "\n";
	}
		
}
