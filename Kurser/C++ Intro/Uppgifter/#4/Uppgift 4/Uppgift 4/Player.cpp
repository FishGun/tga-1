#include "Player.h"
#include "DisplayManager.h"
#include "InputController.h"

Player::Player(Room* aRoom, bool aInvincibilityOn, bool aInstakillOn, EnemyType aEntityType) : myCurrentRoom(aRoom), myTypeData(aEntityType), myCurrentHP(GetMaxHP()), myInvincibilityCheatOn(aInvincibilityOn), myInstakillCheatOn(aInstakillOn)
{
	myActiveSpells.clear();
}

void Player::AddPlayer(Dungeon* aDungeon, bool aInvincibilityOn, bool aInstakillOn, EnemyType aEntityType, const int aRoomIndex)
{
	myPlayers.push_back(Player(aDungeon->GetRoom(aRoomIndex), aInvincibilityOn, aInstakillOn, aEntityType));
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
		if (player.IsDead())
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
					Item& item = myCurrentRoom->myDroppedItems.back();
					if (TryAddItem(item))
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
						Item& item = chest->items.back();
						if (TryAddItem(item, false))
						{
							DisplayManager::ChestGrabCallout();
							DisplayManager::ItemPickupCallout(*this, item);
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

					ActivateSpell(myCurrentRoom->mySpells.back(), aRound);
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
			DisplayManager::EntityAttackShout(myTypeData, event->GetEnemy(attackTarget).GetTypeData());
			event->InjureEnemy(myCurrentRoom->myDroppedItems, GetAttack(), attackTarget);
		}
		myKills += enemiesCount - event->GetCurrentEnemies();
		enemiesCount = event->GetCurrentEnemies();
	}
	CleanSpells(aRound);
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
		door.TryPick(GetDexterity());
	}
	else if (unlockInput == 1)
	{
		door.TryBreak(GetStrength());
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


void Player::TakeDamage(int aValue)
{
	myCurrentHP -= aValue;
}
const int Player::GetCurrentHP() const
{
	return myCurrentHP;
}
const bool Player::IsDead() const
{
	return myCurrentHP <= 0;
}
const EnemyType& Player::GetTypeData() const
{
	return myTypeData;
}
const int Player::GetKills() const
{
	return myKills;
}

const int Player::GetStrength() const
{
	return myTypeData.GetBaseStats().strength + GetStrMod();
}
const int Player::GetDexterity() const
{
	return myTypeData.GetBaseStats().dexterity + GetDexMod();
}
const int Player::GetPhysique() const
{
	return myTypeData.GetBaseStats().physique + GetPhyMod();
}
const int Player::GetAttack() const
{
	return GetStrength() * GetDexterity() + GetAttMod();
}
const int Player::GetMaxHP() const
{
	return GetPhysique() * 4 + GetStrength() * 6 + GetDexterity() * 3 + GetMaxHPMod();
}
const int Player::GetCarryingCapacity() const
{
	return GetStrength() + GetDexterity() / 3 + GetCarMod();
}
const int Player::GetDefense() const
{
	return GetPhysique() * GetDexterity() + GetDefMod();
}

const int Player::GetStrMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItems.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItems.at(i).GetItemType().GetBaseData().strength;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->baseModifiers.strength;
	}
	return total;
}
const int Player::GetDexMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItems.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItems.at(i).GetItemType().GetBaseData().dexterity;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->baseModifiers.dexterity;
	}
	return total;
}
const int Player::GetPhyMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItems.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItems.at(i).GetItemType().GetBaseData().physique;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->baseModifiers.physique;
	}
	return total;
}
const int Player::GetAttMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItems.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItems.at(i).GetItemType().GetDerivedData().attack;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.attack;
	}
	return total;
}
const int Player::GetMaxHPMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItems.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItems.at(i).GetItemType().GetDerivedData().hitPointMax;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.hitPointMax;
	}
	return total;
}
const int Player::GetCarMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItems.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItems.at(i).GetItemType().GetDerivedData().carryingCapacity;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.carryingCapacity;
	}
	return total;
}
const int Player::GetDefMod() const
{
	int total = 0;
	const int itemTotal = static_cast<int>(myItems.size());
	for (int i = 0; i < itemTotal; i++)
	{
		total += myItems.at(i).GetItemType().GetDerivedData().defense;
	}
	const int spellTotal = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellTotal; i++)
	{
		total += myActiveSpells.at(i).data->derivedModifiers.defense;
	}
	return total;
}

const std::vector<Item>& Player::GetTemporaryItemVector() const
{
	return myItems;
}
const std::vector<SpellData::ActivatedSpell>& Player::GetTemporarySpellVector() const
{
	return myActiveSpells;
}

bool Player::TryAddItem(Item& aItem, const bool aShouldCallout)
{
	if (GetCarryingCapacity() > static_cast<int>(myItems.size()))
	{
		myItems.push_back(aItem);
		myCurrentHP += aItem.GetItemType().GetDerivedData().hitPointMax;
		if (aShouldCallout)
		{
			DisplayManager::ItemPickupCallout(*this, aItem);
		}
		return true;
	}
	else
	{
		if (aShouldCallout)
		{
			DisplayManager::ItemPickupFailedCallout(*this);
		}
		return false;
	}
}
void Player::ActivateSpell(const SpellData::SpellInstanceData* aSpellDataPointer, int aRound)
{
	myActiveSpells.push_back(SpellData::ActivatedSpell(aSpellDataPointer, aRound));
}
void Player::CleanSpells(int aRound)
{
	int spellCount = static_cast<int>(myActiveSpells.size());
	for (int i = 0; i < spellCount; i++)
	{
		const SpellData::ActivatedSpell& spell = myActiveSpells.at(i);
		const int endRound = spell.roundAquisition + spell.data->roundDuration;
		if (endRound <= aRound)
		{
			myActiveSpells.erase(myActiveSpells.begin() + i);
			DisplayManager::SpellEndCallout(*spell.data);
			i--;
			spellCount--;
		}
	}
}

std::vector<Player> Player::myPlayers = {};