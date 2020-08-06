#include "Input.h"

we::Input::Input()
{

}

bool we::Input::IsMouseBPressed(we::WE_MOUSE_BUTTON keyCode)
{
	return m_Mouse.GetMouseDown(keyCode);
}

bool we::Input::IsMouseBRereleased(we::WE_MOUSE_BUTTON keyCode)
{
	return m_Mouse.GetMouseUp(keyCode);
}

bool we::Input::IsKeyboardBPressed(we::WE_KEYBOARD_BUTTON keyCode)
{
	return m_Keyboard.GetKeyDown(keyCode);
}

bool we::Input::IsKeyboardBRereleased(we::WE_KEYBOARD_BUTTON keyCode)
{
	return m_Keyboard.GetKeyUp(keyCode);
}

void we::Input::Update()
{
	m_Mouse.Update();
	m_Keyboard.Update();
}

