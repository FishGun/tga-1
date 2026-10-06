#include "Player.h"
#include "DisplayManager.h"
#include "InputController.h"

Player::Player(Room* aRoom, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity) : myCurrentRoom(aRoom), myEntityClass(aEntity), myInvincibilityCheatOn(aInvincibilityOn), myInstakillCheatOn(aInstakillOn) {}

void Player::AddPlayer(Dungeon* aDungeon, bool aInvincibilityOn, bool aInstakillOn, Entity aEntity, const int aRoomIndex)
{
	myPlayers.push_back(Player(aDungeon->GetRoom(aRoomIndex), aInvincibilityOn, aInstakillOn, aEntity));
	myPlayers.back().myCurrentDungeon = aDungeon;
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
			DisplayManager::ShowStats(*this, aRound);
		}
		else
		{
			int roomActionMathed = roomAction;
			bool alreadyChosen = false;
			if (!alreadyChosen && hasItem)
			{
				if (roomActionMathed == MenuData::GENERIC_ROOM_OPTIONS_SIZE + 1)
				{
					const Item* item = myCurrentRoom->myDroppedItems.back();
					if (myEntityClass.TryAddItem(item))
					{
						myCurrentRoom->myDroppedItems.pop_back();
					}
					alreadyChosen = true;
				}
				else roomActionMathed--;
			}
			if (!alreadyChosen && hasChest)
			{
				if (roomActionMathed == MenuData::GENERIC_ROOM_OPTIONS_SIZE + 1)
				{
					ChestData::ChestInstance* chest = myCurrentRoom->myChests.back();
					while (static_cast<int>(chest->items.size()) > 0)
					{
						const Item* item = chest->items.back();
						if (myEntityClass.TryAddItem(item, false))
						{
							DisplayManager::ChestGrabCallout();
							DisplayManager::ItemPickupCallout(myEntityClass, *item);
						}
						else
						{
							DisplayManager::ChestSpillCallout();
							myCurrentRoom->myDroppedItems.push_back(item);
						}
						chest->items.pop_back();
					}
					myCurrentRoom->myChests.pop_back();
					alreadyChosen = true;
				}
				else roomActionMathed--;
			}
			if (!alreadyChosen && hasSpell)
			{
				if (hasSpell && roomActionMathed == MenuData::GENERIC_ROOM_OPTIONS_SIZE + 1)
				{
					DisplayManager::SpellActivateCallout(*myCurrentRoom->mySpells.back());

					myEntityClass.ActivateSpell(myCurrentRoom->mySpells.back(), aRound);
					myCurrentRoom->mySpells.pop_back();
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
			event->InjureEnemy(myCurrentRoom->myDroppedItems, 9001, attackTarget);
		}
		else
		{
			DisplayManager::EntityAttackShout(myEntityClass, event->GetEnemy(attackTarget).GetEntity());
			event->InjureEnemy(myCurrentRoom->myDroppedItems, myEntityClass.GetAttack(), attackTarget);
		}
		myKills += enemiesCount - event->GetCurrentEnemies();
		enemiesCount = event->GetCurrentEnemies();
	}
	myEntityClass.CleanSpells(aRound);
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
Room* Player::SetRoom(Room* aRoom)
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
		door.TryPick(myEntityClass.GetDexterity());
	}
	else if (unlockInput == 1)
	{
		door.TryBreak(myEntityClass.GetStrength());
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

std::vector<Player> Player::myPlayers = {};