#pragma once
#include <Core/Engine/Input/Mouse/Mouse.h>
#include <Core/Engine/Input/Keyboard/Keyboard.h>

namespace we {

	/*
	* \brief Input
	*/
	class Input
	{
	public:
		static Input& GetInstance() {
			static Input  instance;
			return instance;
		}

		bool IsMouseBPressed(we::WE_MOUSE_BUTTON keyCode);
		bool IsMouseBRereleased(we::WE_MOUSE_BUTTON keyCode);
		bool IsKeyboardBPressed(we::WE_KEYBOARD_BUTTON keyCode);
		bool IsKeyboardBRereleased(we::WE_KEYBOARD_BUTTON keyCode);
		void Update();
	private:
		Input();
		Input(const Input&);
		Input& operator=(Input&);

		we::Mouse m_Mouse;
		we::Keyboard m_Keyboard;
		//TODO: add mouse and keyboard to managment input
	};

}