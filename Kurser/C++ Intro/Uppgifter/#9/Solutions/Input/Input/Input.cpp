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
		if (message == WM_KEYDOWN)
		{
			std::cout << "key down message recived, ";
			if (wParam >= 65 && wParam <= 90)
			{
				std::cout << "keycode '" << static_cast<char>(wParam) << "' (lParam: " << lParam << ").\n";
				myPreviousState[wParam] = myCurrentState[wParam];
				myCurrentState[wParam] = true;
				myInputState[wParam] = myPreviousState[wParam] != myCurrentState[wParam];
			}
			else
			{
				std::cout << "ERROR: keycode not recognized!\n";
			}
			return true;
		}
		else if (message == WM_KEYUP)
		{
			std::cout << "key release message recived, ";
			if (wParam >= 65 && wParam <= 90)
			{
				std::cout << "keycode '" << static_cast<char>(wParam) << "' (lParam: " << lParam << ").\n";
				myPreviousState[wParam] = myCurrentState[wParam];
				myCurrentState[wParam] = false;
				myInputState[wParam] = myPreviousState[wParam] != myCurrentState[wParam];
			}
			else
			{
				std::cout << "ERROR: keycode not recognized!\n";
			}
			return true;
		}
		else if (message == WM_LBUTTONDOWN)
		{
			std::cout << "LMB message recived!\n";
			return true;
		}
		else if (message == WM_MOUSEWHEEL)
		{
			auto wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			std::cout << "Scrolled " << wheelDelta << " (" << wParam << ")\n";
			

			std::cout << "Is Holding Down A? " << IsKeyDown(65) << "\n";
			std::cout << "Is A Pressed? " << IsKeyPressed(65) << "\n";
			std::cout << "Is A Released? " << IsKeyReleased(65) << "\n";
			return true;
		}

		return false;
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
		return true;
	}

	void InputHandler::UpdateInput()
	{

	}
}