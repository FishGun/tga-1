#include "GameLoop.h"
#include "MenuData.h"

GameLoop::GameLoop()
{
	myRoundTracker = 1;
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
			const int cheatInput = InputController::IntegerRange(MenuData::CHEAT_OPTIONS_SIZE);
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
		if (mainMenuChoice != 3)
		{
			system("pause");
			system("cls");
		}
	} while (mainMenuChoice != 3);
}

const int GameLoop::MainMenu() const
{
	DisplayManager::MainMenu();
	return InputController::IntegerRange(MenuData::MAIN_OPTIONS_SIZE);
}

void GameLoop::Play(bool aInvincibilityOn, bool aInstakillOn)
{
	Dungeon myDungeon(DungeonData::GenerationTypes::TheHold);

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
		Event::PlayRound(myRoundTracker);
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