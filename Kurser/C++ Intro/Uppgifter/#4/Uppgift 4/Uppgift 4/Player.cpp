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

void Player::PlayRound()
{
	for (int i = 0; i < GetPlayerCount(); i++)
	{
		myPlayers[i].TakeTurn();
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

void Player::TakeTurn()
{
	if (IsInCombat())
	{
		Event* const event = myCurrentRoom->GetEvent();
		int enemiesCount = event->GetCurrentEnemies();

		DisplayManager::CombatOptions(*this, *event);

		const int attackTarget = InputController::IntegerRange(enemiesCount)-1;


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
		enemiesCount = event->GetCurrentEnemies();
	}
	else
	{
		DisplayManager::RoomOptions(*this);
		const int roomAction = InputController::IntegerRange(MenuData::globalRoomOptionsSize) - 1;
		if (roomAction == 0)
		{
			TryChangeRoom();
		}
		else
		{

		}
	}
}

const int Player::RoomMenu() const
{
	DisplayManager::PlayerContext(*this);
	return InputController::IntegerRange(MenuData::globalMainOptionsSize);
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
	const int unlockInput = InputController::IntegerRange(2)-1;
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
	const int localDoorIndex = InputController::IntegerRange(myCurrentRoom->GetDoorTotal())-1;
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