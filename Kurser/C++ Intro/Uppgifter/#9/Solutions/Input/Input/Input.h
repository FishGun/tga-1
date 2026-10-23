#pragma once

#include <Windows.h>
#include <array>

namespace CommonUtilities
{
	class InputHandler
	{
	public:
		InputHandler();

		bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);

		bool IsKeyDown(const int aKeyCode) const;

		bool IsKeyPressed(const int aKeyCode) const;

		bool IsKeyReleased(const int aKeyCode) const;

		bool UpdateMouseInput(UINT aMessage);

		void UpdateInput();

	private:
		std::array<bool, 256> myCurrentState;
		std::array<bool, 256> myPreviousState;
		std::array<bool, 256> myInputState;
	};
}