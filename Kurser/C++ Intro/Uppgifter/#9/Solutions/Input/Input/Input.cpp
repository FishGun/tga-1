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
		if (message == 256)
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
		}
		if (message == 257)
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
		}

		if (wParam == WM_LBUTTONDOWN)
		{
			std::cout << "LMB message recived!\n";
		}

		std::cout << "Is Holding Down A? " << IsKeyDown(65) << "\n";
		return true;
	}

	bool InputHandler::IsKeyDown(const int aKeyCode) const
	{
		return myCurrentState[aKeyCode] && !myInputState[aKeyCode];
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