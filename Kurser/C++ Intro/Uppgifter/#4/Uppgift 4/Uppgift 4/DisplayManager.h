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
	void CombatOptions(const Player& aPlayer, Event& aEvent);
	void LockedDoorOptions(const Door& aDoor);
	void DoorOpenCallout();
	void DoorStillLockedCallout();

	void BasicStringArrayDisplay(const std::vector<std::string>& aStringVector);

	void Round(int aRoundIndex);

	void PlayerContext(const Player& aPlayer);
	void PlayerStats(const Player& aPlayer);
	void EnemyHP(const Enemy& aEnemy);
	void PlayerHP(const Player& aPlayer);
	void EntityAttackShout(const EnemyType& aAttacker, const EnemyType& aTarget, const int aDamageValue, const int aAttackValue, const int aDamageReductionValue);
	void EntityDeathCry(const EnemyType& aEntity);
	void PlayerDeathCry(const Player& aPlayer);
	void ShowStats(const Player& aPlayer, const int aRound);

	void ItemDropCallout();
	void ItemPickupCallout(const Player& aPlayer, const Item& aItem);
	void ItemPickupFailedCallout(const Player& aPlayer);

	void ChestSpillCallout();
	void ChestGrabCallout();

	void SpellActivateCallout(const SpellData::SpellInstanceData& aSpell);
	void SpellEndCallout(const SpellData::SpellInstanceData& aSpell);

	void InvincibilityCallout(const Player& aPlayer);
	void InstakillCallout(const Player& aPlayer);

	void AskForDoorChoice(const Player& aPlayer);
	void MoveThroughDoor(Door& aDoor, const bool aIsMovingToPreviousRoom);

	void GameStart(Dungeon& aDungeon, int aKillsToWin);
	void GameOver();
	void Win();
}