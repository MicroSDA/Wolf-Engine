#pragma warning(push)
#pragma warning(disable : 26812)
#pragma once
#include <Core/Engine/Render/Display/Display.h>

namespace we {

	enum WE_MOUSE_BUTTON
	{
		MOUSE_LEFT_BUTTON = 1,
		MOUSE_MIDDLE_BUTTON = 2,
		MOUSE_RIGHT_BUTTON = 3,
		MOUSE_WHEEL_UP = 4,
		MOUSE_WHEEL_DOWN = 5
	};

	class Mouse
	{
	public:
		Mouse();
		~Mouse();
		inline bool GetMouseDown(we::WE_MOUSE_BUTTON keyCode)      const { return m_KeyDown[keyCode]; }
		inline bool GetMouseUp(we::WE_MOUSE_BUTTON keyCode)        const { return m_KeyUp[keyCode]; }

		void Update();
	private:
		static const int NUM_MOUSE_BUTTONS = 5;
		bool m_KeyDown[NUM_MOUSE_BUTTONS];
		bool m_KeyUp[NUM_MOUSE_BUTTONS];

		const SDL_Event* m_Event;
	};
}


