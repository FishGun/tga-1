#include "GameLoop.h"
#include "MenuData.h"

GameLoop::GameLoop()
{
	int mainMenuChoice = 0;
	bool InvincibilityCheat = false;
	bool instakillCheat = false;
	do
	{
		mainMenuChoice = MainMenu();

		if (mainMenuChoice == 1)
		{
			Play(InvincibilityCheat, instakillCheat);
		}
		else if (mainMenuChoice == 2)
		{
			DisplayManager::CheatStatus(InvincibilityCheat, instakillCheat);
			DisplayManager::CheatMenu();
			const int cheatInput = InputController::IntegerRange(MenuData::globalCheatOptionsSize);
			if (cheatInput == 1)
			{
				InvincibilityCheat = !InvincibilityCheat;
			}
			else if (cheatInput == 2)
			{
				instakillCheat = !instakillCheat;
			}
			DisplayManager::CheatStatus(InvincibilityCheat, instakillCheat);
		}
		system("pause");
		system("cls");
	} while (mainMenuChoice != 3);
}

const int GameLoop::MainMenu() const
{
	DisplayManager::MainMenu();
	return InputController::IntegerRange(MenuData::globalMainOptionsSize);
}

void GameLoop::Play(bool aInvincibilityOn, bool aInstakillOn)
{
	Dungeon myDungeon(DungeonData::GenerationTypes::TheHold);

	Player::AddPlayer(&myDungeon, aInvincibilityOn, aInstakillOn);
	int roundTracker = 1;
	while (Player::GetPlayerCount() > 0)
	{
		system("cls");
		DisplayManager::Round(roundTracker);
		Player::PlayRound();
		Event::PlayRound();
		Player::CheckForDeaths();
		roundTracker++;
		system("pause");
	}
}