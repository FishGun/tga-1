#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <array>

namespace CommonUtilities
{
	struct Vector2float
	{
		float x = { 0 };
		float y = { 0 };
	};

	enum Key
	{
		KEY_LMB = VK_LBUTTON,
		KEY_RMB = VK_RBUTTON,
		KEY_MMB = VK_MBUTTON,
	};

	class InputHandler
	{
	public:
		struct MouseValues
		{
			Vector2float currentPosition;
			Vector2float previousPosition;
			Vector2float deltaPosition;

			float currentWheel;
			float previousWheel;
			float deltaWheel;
			float GetWheelStandardizedDelta() const
			{
				return deltaWheel / 120.0f;
			}
		};

		InputHandler();

		bool UpdateEvents(UINT message, WPARAM wParam, LPARAM lParam);

		bool IsKeyDown(const int aKeyCode) const;

		bool IsKeyPressed(const int aKeyCode) const;

		bool IsKeyReleased(const int aKeyCode) const;

		Vector2float GetMousePosition() const;

		Vector2float GetMousePositionDelta() const;

		float GetMouseWheelDelta() const;

		//bool UpdateMouseInput(UINT aMessage);

		void UpdateInput();

	private:
		std::array<bool, 256> myCurrentState;
		std::array<bool, 256> myPreviousState;
		std::array<bool, 256> myInputState;
		MouseValues myMouseValues;
	};
}