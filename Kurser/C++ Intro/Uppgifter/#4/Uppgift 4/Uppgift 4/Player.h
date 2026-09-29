#pragma once
#include "Entity.h"
#include "Room.h"
#include "Dungeon.h"

#include <vector>

class Player
{
public:
	Player() = delete;

	static Player& AddPlayer(Dungeon* aDungeon, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity = EntityData::playerBaseStats, const int aRoomIndex = 0);
	static const int GetPlayerCount();
	static Player& GetPlayer(int aIndex);
	static void PlayRound();
	static void CheckForDeaths();


	void TakeTurn();
	const int RoomMenu() const;
	const Room* GetRoom() const;
	const Room* SetRoom(const Room* aRoom);
	const Dungeon* GetDungeon() const;
	const Dungeon* SetDungeon(Dungeon* aDungeon);
	const bool IsInCombat() const;
	bool TryToUnlockDoor(Door& door);
	void TryChangeRoom();

	Entity myEntityClass;
private:
	Player(const Room* aRoom, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity);
	static std::vector<Player> myPlayers;
	const Room* myCurrentRoom;
	const Dungeon* myCurrentDungeon;

	bool myInvincibilityCheatOn;
	bool myInstakillCheatOn;
};