// Input.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Input.h"
#include <iostream>

namespace CommonUtilities
{
	InputHandler::InputHandler()
	{

	}

	bool InputHandler::UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		default:
		{
			return false;
		}
		case WM_KEYDOWN:
		{
			std::cout << "key down message recived, ";
			if (wParam >= 0 && wParam < 256)
			{
				std::cout << "keycode '" << static_cast<char>(wParam) << "' (lParam: " << lParam << ").\n";
				myInputState[wParam] = true;
			}
			else
			{
				std::cout << "ERROR: keycode not recognized!\n";
			}
			return true;
		}
		case WM_KEYUP:
		{
			std::cout << "key release message recived, ";
			if (wParam >= 0 && wParam < 256)
			{
				std::cout << "keycode '" << static_cast<char>(wParam) << "' (lParam: " << lParam << ").\n";
				myInputState[wParam] = false;
			}
			else
			{
				std::cout << "ERROR: keycode not recognized!\n";
			}
			return true;
		}
		case WM_MOUSEWHEEL:
		{
			auto wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			std::cout << "Scrolled " << wheelDelta << " (" << wParam << ")\n";
			myMouseValues.currentWheel += wheelDelta;
			return true;
		}
		case WM_MOUSEMOVE:
		{
			myMouseValues.currentPosition.x = GET_X_LPARAM(lParam);
			myMouseValues.currentPosition.y = GET_Y_LPARAM(lParam);
			return true;
		}
		case WM_LBUTTONDOWN:
		{
			std::cout << "LMB down message recived!\n";
			myInputState[KEY_LMB] = true;
			return true;
		}
		case WM_LBUTTONUP:
		{
			std::cout << "LMB up message recived!\n";
			myInputState[KEY_LMB] = false;
			return true;
		}
		case WM_RBUTTONDOWN:
		{
			std::cout << "RMB down message recived!\n";
			myInputState[KEY_RMB] = true;
			return true;
		}
		case WM_RBUTTONUP:
		{
			std::cout << "RMB up message recived!\n";
			myInputState[KEY_RMB] = false;
			return true;
		}
		case WM_MBUTTONDOWN:
		{
			std::cout << "MMB down message recived!\n";
			myInputState[KEY_MMB] = true;
			return true;
		}
		case WM_MBUTTONUP:
		{
			std::cout << "MMB up message recived!\n";
			myInputState[KEY_MMB] = false;
			return true;
		}
		}
	}

	bool InputHandler::IsKeyDown(const int aKeyCode) const
	{
		return myCurrentState[aKeyCode];
	}

	bool InputHandler::IsKeyPressed(const int aKeyCode) const
	{
		return myCurrentState[aKeyCode] && !myPreviousState[aKeyCode];
	}

	bool InputHandler::IsKeyReleased(const int aKeyCode) const
	{
		return !myCurrentState[aKeyCode] && myPreviousState[aKeyCode];
	}

	Vector2float InputHandler::GetMousePosition() const
	{
		return myMouseValues.currentPosition;
	}

	Vector2float InputHandler::GetMousePositionDelta() const
	{
		return myMouseValues.deltaPosition;
	}

	float InputHandler::GetMouseWheelDelta() const
	{
		return myMouseValues.GetWheelStandardizedDelta();
	}

	/*
	bool InputHandler::UpdateMouseInput(UINT aMessage)
	{
		return true;
	}
	*/

	void InputHandler::UpdateInput()
	{
		for (size_t i = 0; i < myPreviousState.size(); i++)
		{
			myPreviousState[i] = myCurrentState[i];
			myCurrentState[i] = myInputState[i];
		}
		MouseValues& mv = myMouseValues;
		mv.deltaPosition = mv.currentPosition;
		mv.deltaPosition.x -= mv.previousPosition.x;
		mv.deltaPosition.y -= mv.previousPosition.y;
		mv.previousPosition = mv.currentPosition;

		mv.deltaWheel = mv.currentWheel - mv.previousWheel;
		mv.previousWheel = mv.currentWheel;
	}
}