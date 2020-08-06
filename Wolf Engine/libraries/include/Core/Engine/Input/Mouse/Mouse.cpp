#include "Mouse.h"

we::Mouse::Mouse()
{
	memset(m_KeyDown, 0, NUM_MOUSE_BUTTONS * sizeof(bool));
	memset(m_KeyUp, 0, NUM_MOUSE_BUTTONS * sizeof(bool));
	m_Event = &we::Display::GetInstance().GetEventHandler();
}

we::Mouse::~Mouse()
{

}

void we::Mouse::Update()
{
	//Not sure about 1542 and 1030, idk what is it
	if (SDL_GetWindowFlags(&we::Display::GetInstance().GetWindowHandler()) == 1542
		|| SDL_GetWindowFlags(&we::Display::GetInstance().GetWindowHandler()) == 1030)
	{
		for (int i = 0; i < NUM_MOUSE_BUTTONS; i++)
		{	
				if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(i))
				{
					m_KeyDown[i] = true;
					m_KeyUp[i] = false;
				}
				else if (m_KeyDown[i])
				{
					m_KeyDown[i] = false;
					m_KeyUp[i] = true;
				}
				else 
				{
					m_KeyUp[i] = false;
				}
		}
		
	}
	else 
	{
		for (int i = 0; i < NUM_MOUSE_BUTTONS; i++)
		{
			if (m_KeyDown[i])
			{
				m_KeyDown[i] = false;
				m_KeyUp[i] = true;
			}
			else {

				m_KeyUp[i] = false;
			}
		}
	}

}