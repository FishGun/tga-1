#pragma once
#include "Entity.h"
#include "Room.h"
#include "Dungeon.h"

#include <vector>

class Player
{
public:
	Player() = delete;

	static Player& AddPlayer(Dungeon* aDungeon, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity = EntityData::BASE_PLAYER_STATS, const int aRoomIndex = 0);
	static const int GetPlayerCount();
	static Player& GetPlayer(int aIndex);
	static void PlayRound(int aRound);
	static void CheckForDeaths();
	static bool PlayerHasWon();
	static void ClearPlayers();


	void TakeTurn(int aRound);
	const int RoomMenu() const;
	const Room* GetRoom() const;
	Room* SetRoom(Room* aRoom);
	const Dungeon* GetDungeon() const;
	const Dungeon* SetDungeon(Dungeon* aDungeon);
	const bool IsInCombat() const;
	bool TryToUnlockDoor(Door& door);
	void TryChangeRoom();

	Entity myEntityClass;
private:
	Player(Room* aRoom, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity);
	static std::vector<Player> myPlayers;
	Room* myCurrentRoom;
	const Dungeon* myCurrentDungeon;
	int myKills = { 0 };

	bool myInvincibilityCheatOn;
	bool myInstakillCheatOn;
};