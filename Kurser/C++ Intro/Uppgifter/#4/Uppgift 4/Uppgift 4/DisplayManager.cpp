#include "DisplayManager.h"
#include <iostream>
//#include <format>

namespace DisplayManager
{
	void MainMenu()
	{
		//std::format("{:^{}}", "Diablo\n\n", 7);
		std::cout << "Diablo\n";
		BasicStringArrayDisplay(MenuData::globalMainOptions);
	}
	void CheatMenu()
	{
		std::cout << "Which cheat would you like to toggle?\n";
		BasicStringArrayDisplay(MenuData::globalCheatOptions);
	}
	void CheatStatus(bool aInvincibilityOn, bool aInstakillOn)
	{
		std::cout <<
			MenuData::globalCheatOptions.at(0) << ": " << (aInvincibilityOn ? "On" : "Off") << "\n"
			<< MenuData::globalCheatOptions.at(0) << ": " << (aInstakillOn ? "On" : "Off") << "\n";
	}
	void RoomOptions(const Player& aPlayer)
	{
		PlayerContext(aPlayer);
		std::cout << "What would you like to do in the room?\n";
		BasicStringArrayDisplay(MenuData::globalRoomOptions);
	}
	void CombatOptions(const Player& aPlayer, const Event& aEvent)
	{
		std::vector <std::string> generatedStringVector;
		const int enemyAmount = aEvent.GetCurrentEnemies();
		generatedStringVector.reserve(enemyAmount);
		for (int i = 0; i < enemyAmount; i++)
		{
			const Entity& entity = aEvent.GetEnemy(i).myEntityClass;
			std::string generatedString = entity.GetName();
			generatedString.append(" #");
			generatedString += std::to_string(i + 1);
			generatedString.append(", ");
			generatedString += std::to_string(entity.GetHP());
			generatedString.append("/");
			generatedString += std::to_string(entity.GetMaxHP());
			generatedStringVector.push_back(generatedString);
		}

		PlayerContext(aPlayer);
		std::cout << "You are in combat! Which enemy would you like to attack?\n";
		BasicStringArrayDisplay(generatedStringVector);
	}
	void LockedDoorOptions(const Door& aDoor)
	{
		std::cout << "The door is locked. How would you like to try opening it?\n";
		std::vector<std::string> generatedStringVector;
		//generatedStringVector.reserve();
		generatedStringVector.push_back(MenuData::globalLockedDoorOptions.at(0) + " (DC" + std::to_string(aDoor.myGenerationData.pickDC) + ")");
		generatedStringVector.push_back(MenuData::globalLockedDoorOptions.at(1) + " (DC" + std::to_string(aDoor.myGenerationData.breakDC) + ")");
		BasicStringArrayDisplay(generatedStringVector);
	}
	void DoorOpenCallout()
	{
		std::cout << "With some effort, you manage to get the door open!\n";
	}
	void DoorStillLockedCallout()
	{
		std::cout << "Despite your best effort, the door is still locked!\n";
	}
	void BasicStringArrayDisplay(const std::vector<std::string> aStringVector)
	{
		const int length = static_cast<int>(aStringVector.size());
		for (int i = 0; i < length; i++)
		{
			std::cout << i + 1 << ": " << aStringVector.at(i) << "\n";
		}
	}

	void Round(int aRoundIndex)
	{
		std::cout << "Round #" << aRoundIndex << "!\n";
	}

	void PlayerContext(const Player& aPlayer)
	{
		std::cout << "You find yourself in " << aPlayer.GetRoom()->GetName() << "\n";
		EntityHP(aPlayer.myEntityClass);
	}
	void EntityStats(const Entity& aEntity)
	{
		EntityData::BaseData baseStats = aEntity.GetBaseStats();
		EntityHP(aEntity);
		std::cout <<
			"Strength: " << baseStats.strength << "\n"
			"Dexterity: " << baseStats.dexterity << "\n"
			"Physique: " << baseStats.physique << "\n"
			"\n"
			"Attack: " << aEntity.GetAttack() << "\n"
			"Defense: " << aEntity.GetDefense() << "\n"
			"Carrying capacity: " << aEntity.GetCarryingCapacity() << "\n"
			"\n";
	}
	void EntityHP(const Entity& aEntity, bool aEnityIsFirstPerson)
	{
		if (aEnityIsFirstPerson)
		{
			std::cout << "You have " << aEntity.GetHP() << " / " << aEntity.GetMaxHP() << "HP\n";
		}
		else
		{
			std::cout << aEntity.GetName() << " has " << aEntity.GetHP() << "/" << aEntity.GetMaxHP() << "HP\n";
		}
		std::cout << "\n";
	}
	void EntityAttackShout(const Entity& aAttacker, const Entity& aTarget)
	{
		std::cout << aAttacker.GetName() << " attacks " << aTarget.GetName() << " for " << Entity::DamageCalculator(aAttacker.GetAttack(), aTarget.GetDefense()) << " damage! (" << aAttacker.GetAttack() << "-" << (aTarget.GetDefense() / EntityData::globalDefenseDivider) << ")\n";
	}
	void EntityDeathCry(const Entity& aEntity)
	{
		std::cout << aEntity.GetName() << " falls to the floor in agony and dies!\n";
	}
	void PlayerDeathCry(const Player& aPlayer)
	{
		std::cout <<
			"\n"
			<< aPlayer.myEntityClass.GetName() << " tries to go on, but is unable.\n"
			"Slowly, they loose their poise, and fall to the ground defeated.\n"
			<< aPlayer.GetDungeon()->GetName() << " is their tomb, and " << aPlayer.GetRoom()->GetName() << " is their shrine.\n";
	}
	void InvincibilityCallout(const Player& aPlayer)
	{
		std::cout << aPlayer.myEntityClass.GetName() << " would have died, if they didn't have their suit on.\n";
	}
	void InstakillCallout(const Player& aPlayer)
	{
		std::cout << aPlayer.myEntityClass.GetName() << " destroyed their foe with a stare!\n";
	}

	void AskForDoorChoice(const Player& aPlayer)
	{
		std::cout << "Which door would you like to go through?\n";
		const Room& room = *aPlayer.GetRoom();
		const int doorTotal = room.GetDoorTotal();
		std::vector<std::string> generatedStringVector;
		//generatedStringVector.reserve();
		const bool hasReturnDoor = room.GetReturnDoor() != NULL;
		for (int i = 0; i < doorTotal; i++)
		{
			std::string generatedString;
			if (i == 0 && hasReturnDoor)
			{
				generatedString = "Door to ";
				generatedString.append(room.GetReturnDoor()->GetPreviousRoom()->GetName());
				generatedString += " (return door)";
			}
			else
			{
				generatedString = "Door to ";
				generatedString.append(room.GetForwardDoor(i - (hasReturnDoor ? 1 : 0))->GetNextRoom()->GetName());
			}
			generatedStringVector.push_back(generatedString);
		}
		BasicStringArrayDisplay(generatedStringVector);
	}
	void MoveThroughDoor(const Door& door, const bool aIsMovingToPreviousRoom)
	{
		const char* previousName = door.GetPreviousRoom()->GetName();
		const char* nextName = door.GetNextRoom()->GetName();
		std::cout << "You leave " << (aIsMovingToPreviousRoom ? nextName : previousName) << ", and go through the door to " << (aIsMovingToPreviousRoom ? previousName : nextName) << "\n";
	}
}