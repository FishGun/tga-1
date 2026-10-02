#include "Player.h"
#include "DisplayManager.h"
#include "InputController.h"

Player::Player(const Room* aRoom, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity) : myCurrentRoom(aRoom), myEntityClass(aEntity), myInvincibilityCheatOn(aInvincibilityOn), myInstakillCheatOn(aInstakillOn) {}

Player& Player::AddPlayer(Dungeon* aDungeon, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity, const int aRoomIndex)
{
	myPlayers.push_back(Player(aDungeon->GetRoom(aRoomIndex), aInvincibilityOn, aInstakillOn, aEntity));
	myPlayers.back().myCurrentDungeon = aDungeon;
	return myPlayers.back();
}
const int Player::GetPlayerCount()
{
	return static_cast<int>(myPlayers.size());
}


Player& Player::GetPlayer(int aIndex)
{
	return myPlayers.at(aIndex);
}

void Player::PlayRound(int aRound)
{
	for (int i = 0; i < GetPlayerCount(); i++)
	{
		myPlayers[i].TakeTurn(aRound);
	}
}

void Player::CheckForDeaths()
{
	for (int i = 0; i < GetPlayerCount(); i++)
	{
		Player& player = myPlayers.at(i);
		if (player.myEntityClass.IsDead())
		{
			if (player.myInvincibilityCheatOn)
			{
				DisplayManager::InvincibilityCallout(player);
			}
			else
			{
				DisplayManager::PlayerDeathCry(player);
				myPlayers.erase(std::next(myPlayers.begin(), i));
			}
		}
	}
}
bool Player::PlayerHasWon()
{
	for (int i = 0; i < GetPlayerCount(); i++)
	{
		Player& player = myPlayers.at(i);
		if (player.myKills >= DungeonData::KILLS_TO_WIN)
		{
			return true;
		}
	}
	return false;
}
void Player::ClearPlayers()
{
	myPlayers.clear();
}


void Player::TakeTurn(int aRound)
{
	if (!IsInCombat())
	{
		DisplayManager::RoomOptions(*this);

		const bool hasItem = myCurrentRoom->HasItem();
		const bool hasChest = myCurrentRoom->HasChest();
		const bool hasSpell = myCurrentRoom->HasSpell();

		const int contextualRoomOptionsAvailable =
			static_cast<int>(hasItem)
			+ static_cast<int>(hasChest)
			+ static_cast<int>(hasSpell);

		const int roomAction = InputController::IntegerRange(MenuData::GENERIC_ROOM_OPTIONS_SIZE + contextualRoomOptionsAvailable);
		if (roomAction == 1)
		{
			TryChangeRoom();
		}
		else if (roomAction == 2)
		{
			DisplayManager::ShowStats(*this);
		}
		else
		{
			int roomActionMathed = roomAction;
			bool alreadyChosen = false;
			if (!alreadyChosen && hasItem)
			{
				if (roomActionMathed == MenuData::GENERIC_ROOM_OPTIONS_SIZE + 1)
				{
					std::cout << "Item";
					//const ItemData::ItemInstanceData& itemData = *myCurrentRoom->myDroppedItems.at(0);
					//LootItemLogic(itemData);
					alreadyChosen = true;
				}
				else roomActionMathed--;
			}
			if (!alreadyChosen && hasChest)
			{
				if (roomActionMathed == MenuData::GENERIC_ROOM_OPTIONS_SIZE + 1)
				{
					std::cout << "Chest";
					//const ChestData::ChestInstance& chest = *myCurrentRoom->myChests.at(0);
					//LootChestLogic(chest);
					alreadyChosen = true;
				}
				else roomActionMathed--;
			}
			if (!alreadyChosen && hasSpell)
			{
				if (hasSpell && roomActionMathed == MenuData::GENERIC_ROOM_OPTIONS_SIZE + 1)
				{
					std::cout << "Spell";
					ActivateSpell(myCurrentRoom->mySpells.at(0), aRound);
					//const SpellData::SpellInstanceData& spellData = *myCurrentRoom->mySpells.at(0);
					//ActivateSpellLogic(spellData);
					alreadyChosen = true;
				}
				else roomActionMathed--;
			}
		}
	}
	if (IsInCombat())
	{
		Event* const event = myCurrentRoom->GetEvent();
		int enemiesCount = event->GetCurrentEnemies();

		DisplayManager::CombatOptions(*this, *event);

		const int attackTarget = InputController::IntegerRange(enemiesCount) - 1;


		if (myInstakillCheatOn)
		{
			DisplayManager::InstakillCallout(*this);
			event->InjureEnemy(9001, attackTarget);
		}
		else
		{
			DisplayManager::EntityAttackShout(myEntityClass, event->GetEnemy(attackTarget).myEntityClass);
			event->InjureEnemy(myEntityClass.GetAttack(), attackTarget);
		}
		myKills += enemiesCount - event->GetCurrentEnemies();
		enemiesCount = event->GetCurrentEnemies();
	}
	CleanSpells();
}

const int Player::RoomMenu() const
{
	DisplayManager::PlayerContext(*this);
	return InputController::IntegerRange(MenuData::MAIN_OPTIONS_SIZE);
}

const Room* Player::GetRoom() const
{
	return myCurrentRoom;
}
const Room* Player::SetRoom(const Room* aRoom)
{
	myCurrentRoom = aRoom;
	return myCurrentRoom;
}
const Dungeon* Player::GetDungeon() const
{
	return myCurrentDungeon;
}
const Dungeon* Player::SetDungeon(Dungeon* aDungeon)
{
	myCurrentDungeon = aDungeon;
	return myCurrentDungeon;
}
const bool Player::IsInCombat() const
{
	return myCurrentRoom->HasActiveEvent();
}
bool Player::TryToUnlockDoor(Door& door)
{
	DisplayManager::LockedDoorOptions(door);
	const int unlockInput = InputController::IntegerRange(2) - 1;
	if (unlockInput == 0)
	{
		door.TryPick(myEntityClass.GetBaseStats().dexterity);
	}
	else if (unlockInput == 1)
	{
		door.TryBreak(myEntityClass.GetBaseStats().strength);
	}
	return door.IsOpen();
}
void Player::TryChangeRoom()
{
	DisplayManager::AskForDoorChoice(*this);
	const int localDoorIndex = InputController::IntegerRange(myCurrentRoom->GetDoorTotal()) - 1;
	Door* door;
	bool isMovingToPreviousRoom;
	if (localDoorIndex == 0 && myCurrentRoom->GetReturnDoor() != NULL)
	{
		door = myCurrentRoom->GetReturnDoor();
		isMovingToPreviousRoom = true;
	}
	else
	{
		door = myCurrentRoom->GetForwardDoor(localDoorIndex);
		isMovingToPreviousRoom = false;
	}

	if (!door->IsOpen())
	{
		TryToUnlockDoor(*door);
		if (door->IsOpen())
		{
			DisplayManager::DoorOpenCallout();
		}
		else
		{
			DisplayManager::DoorStillLockedCallout();
		}
	}
	if (door->IsOpen())
	{
		DisplayManager::MoveThroughDoor(*door, isMovingToPreviousRoom);
		if (isMovingToPreviousRoom)
		{
			SetRoom(door->GetPreviousRoom());
		}
		else
		{
			SetRoom(door->GetNextRoom());

		}
	}
}

void Player::AddItem(const ItemData::ItemInstanceData* aItemDataPointer)
{
	if (myEntityClass.GetCarryingCapacity() < myItemData.size())
	{
		myItemData.push_back(aItemDataPointer);
	}
}
void Player::ActivateSpell(const SpellData::SpellInstanceData* aSpellDataPointer, int aRound)
{
	myActiveSpells.push_back(SpellData::ActivatedSpell(*aSpellDataPointer, aRound));
}
void Player::CleanSpells(int aRound)
{
	int spellCount = myActiveSpells.size();
	for (int i = 0; i < spellCount; i++)
	{
		SpellData::ActivatedSpell& spell = myActiveSpells.at(i);
		const int endRound = spell.roundAquisition + spell.data.roundDuration;
		if (endRound <= aRound)
		{
			myActiveSpells.erase(myActiveSpells.begin() + i);
			i--;
			spellCount--;
		}
	}
}

std::vector<Player> Player::myPlayers = {};