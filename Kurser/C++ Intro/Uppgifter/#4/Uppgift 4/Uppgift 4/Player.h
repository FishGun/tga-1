#pragma once
#include "EnemyType.h"
#include "Room.h"
#include "Dungeon.h"
#include "ItemFactory.h"
#include "SpellData.h"

#include <vector>

class Player
{
public:
	Player() = delete;

	static void AddPlayer(Dungeon* aDungeon, bool aInvincibilityOn, bool aInstakillOn, EnemyType aEntityType = EntityData::BASE_PLAYER_STATS, const int aRoomIndex = 0);
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

	void TakeDamage(int aValue);
	const int GetCurrentHP() const;
	const bool IsDead() const;
	const EnemyType& GetTypeData() const;
	const int GetKills() const;

	const int GetStrength() const;
	const int GetDexterity() const;
	const int GetPhysique() const;

	const int GetAttack() const;
	const int GetMaxHP() const;
	const int GetCarryingCapacity() const;
	const int GetDefense() const;

	const int GetStrMod() const;
	const int GetDexMod() const;
	const int GetPhyMod() const;

	const int GetAttMod() const;
	const int GetMaxHPMod() const;
	const int GetCarMod() const;
	const int GetDefMod() const;

	const std::vector<Item>& GetTemporaryItemVector() const;
	const std::vector<SpellData::ActivatedSpell>& GetTemporarySpellVector() const;

	bool TryAddItem(Item& aItem, const bool aShouldCallout = true);
	void ActivateSpell(const SpellData::SpellInstanceData* aSpellDataPointer, int aRound);
	void CleanSpells(int aRound);

private:
	Player(Room* aRoom, bool aInvincibilityOn, bool aInstakillOn, EnemyType aEntityType);
	static std::vector<Player> myPlayers;
	Room* myCurrentRoom;
	const Dungeon* myCurrentDungeon;

	EnemyType myTypeData;
	int myCurrentHP;
	int myKills = { 0 };

	std::vector<Item> myItems;
	std::vector<SpellData::ActivatedSpell> myActiveSpells;

	bool myInvincibilityCheatOn;
	bool myInstakillCheatOn;
};