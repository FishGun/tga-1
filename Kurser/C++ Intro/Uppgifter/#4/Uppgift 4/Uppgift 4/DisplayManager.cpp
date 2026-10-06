#include "DisplayManager.h"
#include <iostream>
//#include <format>

namespace DisplayManager
{
	void MainMenu()
	{
		//std::format("{:^{}}", "Diablo\n\n", 7);
		std::cout << "Diablo\n";
		BasicStringArrayDisplay(MenuData::MAIN_OPTIONS);
	}
	void CheatMenu()
	{
		std::cout << "Which cheat would you like to toggle?\n";
		BasicStringArrayDisplay(MenuData::CHEAT_OPTIONS);
	}
	void CheatStatus(bool aInvincibilityOn, bool aInstakillOn)
	{
		std::cout <<
			MenuData::CHEAT_OPTIONS.at(0) << ": " << (aInvincibilityOn ? "On" : "Off") << "\n"
			<< MenuData::CHEAT_OPTIONS.at(1) << ": " << (aInstakillOn ? "On" : "Off") << "\n";
	}
	void RoomOptions(const Player& aPlayer)
	{
		const Room& room = *aPlayer.GetRoom();
		PlayerContext(aPlayer);

		bool showedAny = false;
		if (room.myDroppedItems.size() > 0)
		{
			std::cout << "You can see a metal object sparkling in the corner. (x" << room.myDroppedItems.size() << ")\n";
			showedAny = true;
		}
		if (room.myChests.size() > 0)
		{
			std::cout << "A grand treasure chest sits in the room. (x" << room.myChests.size() << ")\n";
			showedAny = true;
		}
		if (room.mySpells.size() > 0)
		{
			std::cout << "A magic spell glyph ominously hovers over a pentagram. (x" << room.mySpells.size() << ")\n";
			showedAny = true;
		}
		if (showedAny)
		{
			std::cout << "\n";
		}

		std::cout << "What would you like to do in the room?\n";
		std::vector<std::string> generatedStringVector = MenuData::GENERIC_ROOM_OPTIONS;
		generatedStringVector.reserve(MenuData::GENERIC_ROOM_OPTIONS_SIZE + MenuData::CONTEXTUAL_ROOM_OPTIONS_SIZE);
		if (room.myDroppedItems.size() > 0)
		{
			generatedStringVector.push_back(MenuData::CONTEXTUAL_ROOM_OPTIONS.at(0));
		}
		if (room.myChests.size() > 0)
		{
			generatedStringVector.push_back(MenuData::CONTEXTUAL_ROOM_OPTIONS.at(1));
		}
		if (room.mySpells.size() > 0)
		{
			generatedStringVector.push_back(MenuData::CONTEXTUAL_ROOM_OPTIONS.at(2));
		}
		BasicStringArrayDisplay(generatedStringVector);
	}
	void CombatOptions(const Player& aPlayer, Event& aEvent)
	{
		std::vector <std::string> generatedStringVector;
		const int enemyAmount = aEvent.GetCurrentEnemies();
		generatedStringVector.reserve(enemyAmount);
		for (int i = 0; i < enemyAmount; i++)
		{
			const Entity& entity = aEvent.GetEnemy(i).GetEntity();
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
		generatedStringVector.reserve(2);
		generatedStringVector.push_back(MenuData::LOCKED_DOOR_OPTIONS.at(0) + " (DC " + std::to_string(aDoor.myGenerationData.pickDC) + ")");
		generatedStringVector.push_back(MenuData::LOCKED_DOOR_OPTIONS.at(1) + " (DC " + std::to_string(aDoor.myGenerationData.breakDC) + ")");
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

	void BasicStringArrayDisplay(const std::vector<std::string>& aStringVector)
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
		std::cout <<
			aPlayer.myKills << "/" << DungeonData::KILLS_TO_WIN << " kills (to win)\n"
			"You find yourself in " << aPlayer.GetRoom()->GetName() << "\n";
		EntityHP(aPlayer.myEntityClass);
	}
	void EntityStats(const Entity& aEntity)
	{
		EntityHP(aEntity);
		std::cout <<
			"Strength: " << aEntity.GetStrength() << "\n"
			"Dexterity: " << aEntity.GetDexterity() << "\n"
			"Physique: " << aEntity.GetPhysique() << "\n"
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
		std::cout << aAttacker.GetName() << " attacks " << aTarget.GetName() << " for " << Entity::DamageCalculator(aAttacker.GetAttack(), aTarget.GetDefense()) << " damage! (" << aAttacker.GetAttack() << "-" << (aTarget.GetDefense() / EntityData::DEFENSE_DIVIDER) << ")\n";
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
	void ShowStats(const Player& aPlayer, const int aRound)
	{
		Entity entity = aPlayer.myEntityClass;
		std::cout <<
			entity.GetName() << "\n"
			"HP:" << entity.GetHP() << "/" << entity.GetMaxHP() << "\n"
			"Strength:" << entity.GetStrength() << "\n"
			"Dexterity:" << entity.GetDexterity() << "\n"
			"Physique:" << entity.GetPhysique() << "\n"
			"Attack:" << entity.GetAttack() << "\n"
			"Defense:" << entity.GetDefense() << " (damage reduction:" << entity.GetDefense() / EntityData::DEFENSE_DIVIDER << ")\n"
			"Carrying Capacity:" << entity.GetCarryingCapacity() << "\n";
		const int itemCount = static_cast<int>(entity.GetItemVector().size());
		for (int i = 0; i < itemCount; i++)
		{
			std::cout << "Item #" << i + 1 << ": " << entity.GetItemVector().at(i)->GetBaseData().name << "\n";
		}
		const int spellCount = static_cast<int>(entity.GetSpellVector().size());
		for (int i = 0; i < spellCount; i++)
		{
			std::cout << "Spell #" << i + 1 << ": " << entity.GetSpellVector().at(i).data->baseModifiers.name << " (" << entity.GetSpellVector().at(i).roundAquisition + entity.GetSpellVector().at(i).data->roundDuration - aRound << " rounds left)\n";
		}
		std::cout << "\n";
	}

	void ItemDropCallout()
	{
		std::cout <<
			"As the body falls to the ground, something shiny falls and clangs on the floor...\n";
	}
	void ItemPickupCallout(const Entity& aEntity, const Item& aItem)
	{
		std::cout <<
			aEntity.GetName() << " picked up a " << aItem.GetBaseData().name << "!\n";
	}
	void ItemPickupFailedCallout(const Entity& aEntity)
	{
		std::cout <<
			aEntity.GetName() << "'s inventory is already full! (" << aEntity.GetCarryingCapacity() << ")\n";
	}

	void ChestSpillCallout()
	{
		std::cout <<
			"The chest ejects an item with force, and you are too encumbered to grab it!\n";
	}
	void ChestGrabCallout()
	{
		std::cout <<
			"An item is flung out of the chest, and you grab it!\n";
	}

	void SpellActivateCallout(const SpellData::SpellInstanceData& aSpell)
	{
		std::cout <<
			"Swirls of arcane energy swell into you as you become the conduit for a " << aSpell.baseModifiers.name << " spell. (" << aSpell.roundDuration << " rounds)\n";
	}
	void SpellEndCallout(const SpellData::SpellInstanceData& aSpell)
	{
		std::cout <<
			"The magic from a " << aSpell.baseModifiers.name << " spell fades from the world.\n";
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
		generatedStringVector.reserve(doorTotal);
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
	void MoveThroughDoor(Door& aDoor, const bool aIsMovingToPreviousRoom)
	{
		const char* previousName = aDoor.GetPreviousRoom()->GetName();
		const char* nextName = aDoor.GetNextRoom()->GetName();
		std::cout << "You leave " << (aIsMovingToPreviousRoom ? nextName : previousName) << ", and go through the door to " << (aIsMovingToPreviousRoom ? previousName : nextName) << "\n";
	}

	void GameStart(Dungeon& aDungeon, int aKillsToWin)
	{
		std::cout << "Thunder and lighting gather around you, scrounging forward in the wet mud, when a great sight falls before your eyes.\n"
			<< aDungeon.GetName() << " stands before you, inviting you with dread. With no other choice, you must enter.\n"
			"Once you have slayed " << aKillsToWin << " enemies, your quest will be done, and you may pay the ferryman for a ride home.\n"
			"Unless he comes to take you before your time.\n";
	}
	void GameOver()
	{
		system("cls");
		std::cout << "A tragic fate befell you, and you stumble into the ferryman without enough souls to save your own.\n"
			"Game Over\n\n";
	}
	void Win()
	{
		system("cls");
		std::cout << "Quickly you make your way out of that terrible place, paying for your ride down the river, back home to the warmth of your hearth.\n"
			"You Win!\n\n";
	}
}