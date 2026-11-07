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
			myMouseValues.wheelDelta = wheelDelta;
			return true;
		}
		case WM_MOUSEMOVE:
		{
			std::cout << "Mouse Moved!\n";
			myMouseValues.currentPosition.x = GET_X_LPARAM(lParam);
			myMouseValues.currentPosition.y = GET_Y_LPARAM(lParam);
			return true;
		}
		case WM_LBUTTONDOWN:
		{
			std::cout << "LMB down message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::LMB)] = true;
			return true;
		}
		case WM_LBUTTONUP:
		{
			std::cout << "LMB up message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::LMB)] = false;
			return true;
		}
		case WM_RBUTTONDOWN:
		{
			std::cout << "RMB down message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::RMB)] = true;
			return true;
		}
		case WM_RBUTTONUP:
		{
			std::cout << "RMB up message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::RMB)] = false;
			return true;
		}
		case WM_MBUTTONDOWN:
		{
			std::cout << "MMB down message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = true;
			return true;
		}
		case WM_MBUTTONUP:
		{
			std::cout << "MMB up message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = false;
			return true;
		}
		case WM_XBUTTONDOWN:
		{
			if (lParam == XBUTTON1)
			{
				std::cout << "X1B down message recived!\n";
				myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::X1B)] = true;
				return true;
			}
			else if (lParam == XBUTTON2)
			{
				std::cout << "X2B down message recived!\n";
				myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::X2B)] = true;
				return true;
			}
			else
			{
				std::cout << "Unknown X button pressed!\n";
				return false;
			}
		}
		case WM_XBUTTONUP:
		{
			if (lParam == XBUTTON1)
			{
				std::cout << "X1B down message recived!\n";
				myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::X1B)] = false;
				return true;
			}
			else if (lParam == XBUTTON2)
			{
				std::cout << "X2B down message recived!\n";
				myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::X2B)] = false;
				return true;
			}
			else
			{
				std::cout << "Unknown X button pressed!\n";
				return false;
			}
		}
		case WM_MBUTTONDOWN:
		{
			std::cout << "MMB down message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = true;
			return true;
		}
		case WM_MBUTTONUP:
		{
			std::cout << "MMB up message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = false;
			return true;
		}
		case WM_MBUTTONDOWN:
		{
			std::cout << "MMB down message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = true;
			return true;
		}
		case WM_MBUTTONUP:
		{
			std::cout << "MMB up message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = false;
			return true;
		}
		case WM_MBUTTONDOWN:
		{
			std::cout << "MMB down message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = true;
			return true;
		}
		case WM_MBUTTONUP:
		{
			std::cout << "MMB up message recived!\n";
			myMouseValues.inputState[static_cast<int>(MouseValues::MouseCode::MMB)] = false;
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

	bool InputHandler::UpdateMouseInput(UINT aMessage)
	{
		MouseValues& mv = myMouseValues;
		for (size_t i = 0; i < mv.previousState.size(); i++)
		{
			mv.previousState[i] = mv.currentState[i];
			mv.currentState[i] = mv.inputState[i];
		}
		mv.previousPosition = mv.currentPosition;
		return true;
	}

	void InputHandler::UpdateInput()
	{
		for (size_t i = 0; i < myPreviousState.size(); i++)
		{
			myPreviousState[i] = myCurrentState[i];
			myCurrentState[i] = myInputState[i];
		}
	}
}