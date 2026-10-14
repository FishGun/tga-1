#include "GameLoop.h"
#include "MenuData.h"

GameLoop::GameLoop()
{
	myRoundTracker = 1;
	MenuData::MainOptionsEnum mainMenuChoice;
	bool invincibilityCheat = false;
	bool instakillCheat = false;
	do
	{
		mainMenuChoice = MainMenu();

		if (mainMenuChoice == MenuData::MainOptionsEnum::Play)
		{
			Play(invincibilityCheat, instakillCheat);
			// Breaks out of mainMenu after one play. Should be removed once restarting without closing is verified to work.
			mainMenuChoice = MenuData::MainOptionsEnum::Exit;
			system("pause");
			system("cls");
		}
		else if (mainMenuChoice == MenuData::MainOptionsEnum::Cheats)
		{
			DisplayManager::CheatStatus(invincibilityCheat, instakillCheat);
			DisplayManager::CheatMenu();
			const int cheatInput = InputController::IntegerRange(MenuData::CHEAT_OPTIONS_SIZE);
			if (cheatInput == 1)
			{
				invincibilityCheat = !invincibilityCheat;
			}
			else if (cheatInput == 2)
			{
				instakillCheat = !instakillCheat;
			}
			DisplayManager::CheatStatus(invincibilityCheat, instakillCheat);
		}
		if (mainMenuChoice != MenuData::MainOptionsEnum::Exit)
		{
			system("pause");
			system("cls");
		}
	} while (mainMenuChoice != MenuData::MainOptionsEnum::Exit);
}

const MenuData::MainOptionsEnum GameLoop::MainMenu() const
{
	DisplayManager::MainMenu();
	return static_cast<MenuData::MainOptionsEnum>(InputController::IntegerRange(MenuData::MAIN_OPTIONS_SIZE) - 1);
}

void GameLoop::Play(bool aInvincibilityOn, bool aInstakillOn)
{
	Dungeon myDungeon(DungeonData::GenerationType::TheHold);

	EntityData::BaseData playerData = EntityData::BASE_PLAYER_STATS;
	InputController::AskForName(playerData.name, EntityData::MIN_NAME_LENGTH, EntityData::MAX_NAME_LENGTH);
	Player::AddPlayer(&myDungeon, aInvincibilityOn, aInstakillOn, playerData);

	DisplayManager::GameStart(myDungeon, DungeonData::KILLS_TO_WIN);
	system("pause");
	system("cls");
	while (Player::GetPlayerCount() > 0 && !Player::PlayerHasWon())
	{
		system("cls");

		myDungeon.IncrementRound();
		DisplayManager::Round(myRoundTracker);

		Player::PlayRound(myRoundTracker);
		Event::PlayRound();
		Player::CheckForDeaths();

		myRoundTracker++;
		system("pause");
	}
	if (Player::GetPlayerCount() <= 0)
	{
		DisplayManager::GameOver();
	}
	else if (Player::PlayerHasWon())
	{
		DisplayManager::Win();
		Player::ClearPlayers();
	}
}