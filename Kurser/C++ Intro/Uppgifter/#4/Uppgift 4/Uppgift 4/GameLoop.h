#pragma once
#include "Dungeon.h"
#include "Door.h"
#include "Room.h"
#include "Player.h"
#include "EntityData.h"

#include <iostream>

#include "DisplayManager.h"
#include "InputController.h"

class GameLoop
{
public:
	GameLoop();
	const int GetCurrentRound() const;
private:
	const int MainMenu() const;
	void Play(bool aInvincibilityOn, bool aInstakillOn);
	int myRoundTracker;
};

