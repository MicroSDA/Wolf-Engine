#include "Keyboard.h"

we::Keyboard::Keyboard()
{
	memset(m_KeyDown, 0, NUM_KEYBOARD_KEYS * sizeof(bool));
	memset(m_KeyUp, 0, NUM_KEYBOARD_KEYS * sizeof(bool));
	m_Event = &we::Display::GetInstance().GetEventHandler();
}

we::Keyboard::~Keyboard()
{
}

void we::Keyboard::Update()
{
	//Not sure about 1542 and 1030, idk what is it
	if (SDL_GetWindowFlags(&we::Display::GetInstance().GetWindowHandler()) == 1542
		|| SDL_GetWindowFlags(&we::Display::GetInstance().GetWindowHandler()) == 1030)
	{
		const Uint8* keys = SDL_GetKeyboardState(NULL);

		for (int i = 0; i < NUM_KEYBOARD_KEYS ; i++)
		{
			if (static_cast<bool>(keys[i]))
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
		for (int i = 0; i < NUM_KEYBOARD_KEYS; i++)
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
