#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <array>

namespace CommonUtilities
{
	struct Vector2f
	{
		float x = { 0 };
		float y = { 0 };
	};

	struct MouseValues
	{
		Vector2f currentPosition;
		Vector2f previousPosition;
		Vector2f GetPositionDelta()
		{
			Vector2f posDelta = currentPosition;
			posDelta.x -= previousPosition.x;
			posDelta.y -= previousPosition.y;
			return posDelta;
		}

		float wheelDelta;
		float GetWheelPercentDelta()
		{
			return wheelDelta / 2880.0f;
		}

		enum class MouseCode
		{
			LMB,
			RMB,
			MMB,
			X1B,
			X2B,
			CTRL,
			SHIFT
		};
		std::array<bool, 7> currentState;
		std::array<bool, 7> previousState;
		std::array<bool, 7> inputState;
	};

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
		MouseValues myMouseValues;
	};
}