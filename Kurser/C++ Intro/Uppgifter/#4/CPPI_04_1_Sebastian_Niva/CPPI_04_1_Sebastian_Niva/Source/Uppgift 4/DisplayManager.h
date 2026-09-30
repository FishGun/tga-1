#pragma once
#include "MenuData.h"
#include "Event.h"
#include "Player.h"
#include "Dungeon.h"

namespace DisplayManager
{
	void MainMenu();
	void CheatMenu();
	void CheatStatus(bool aInvincibilityOn, bool aInstakillOn);
	void RoomOptions(const Player& aPlayer);
	void CombatOptions(const Player& aPlayer, const Event& aEvent);
	void LockedDoorOptions(const Door& aDoor);
	void DoorOpenCallout();
	void DoorStillLockedCallout();
	void BasicStringArrayDisplay(const std::vector<std::string> aStringVector);

	void Round(int aRoundIndex);

	void PlayerContext(const Player& aPlayer);
	void EntityStats(const Entity& aEntity);
	void EntityHP(const Entity& aEntity, bool aEnityIsFirstPerson = false);
	void EntityAttackShout(const Entity& aAttacker, const Entity& aTarget);
	void EntityDeathCry(const Entity& aEntity);
	void PlayerDeathCry(const Player& aPlayer);
	void ShowStats(const Player& aPlayer);

	void InvincibilityCallout(const Player& aPlayer);
	void InstakillCallout(const Player& aPlayer);

	void AskForDoorChoice(const Player& aPlayer);
	void MoveThroughDoor(const Door& door, const bool aIsMovingToPreviousRoom);

	void GameStart(Dungeon& aDungeon, int aKillsToWin);
	void GameOver();
	void Win();
}