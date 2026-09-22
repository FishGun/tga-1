#include "Player.h"
#include <iostream>

Player::Player() : Player::Player(100)
{

}

Player::Player(int aMoney)
{
	myWins.total = { 0 };
	myMoney = aMoney;

	bool nameValid = false;
	do
	{
		std::cout << "Please, enter your name (2-16 characters): ";
		std::cin.get(myName, 18);
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		for (int i = 0; i < 17; i++)
		{
			if (i >= 2 && myName[i] == '\0')
			{
				nameValid = true;
				break;
			}
			else if (myName[i] == '\0')
			{
				std::cout << "\nError: Name too short. Please stick to 2 character or more.\n\n";
				break;
			}
			else if (i >= 16)
			{
				std::cout << "\nError: Name too long. Please stick to 16 character or less.\n\n";
				break;
			}

			int nameIndexIntCasted = static_cast<int>(myName[i]);
			if (i == 0 && !(nameIndexIntCasted >= 65 && nameIndexIntCasted <= 90))
			{
				std::cout << "\nError: The first input must be a capital letter.\n\n";
				break;
			}
			else if (i > 0 && !((nameIndexIntCasted >= 97 && nameIndexIntCasted <= 122) || (nameIndexIntCasted >= 65 && nameIndexIntCasted <= 90)))
			{
				std::cout << "\nError: Name may only consist of letters.\n\n";
				break;
			}
		}

	} while (!nameValid);

	if (NameIsQrikko())
	{
		std::cout <<
			"\nQrikko mode unlocked! You start with 10x the normal money. What a rich guy!\n";
		myMoney *= 10;
	}
	else if (NameIsJoel())
	{
		std::cout <<
			"\nJoel mode unlocked! You have no bet limit. What a smooth talker!\n";
	}
	else if (NameIsClaudia())
	{
		std::cout <<
			"\nMahalo! Claudia mode unlocked! You have 5 000 000$! How bonita!\n";
		myMoney = 5000000;
	}
	else
	{
		std::cout <<
			"\nWelcome, " << GetName() << "!\n"
			"You are entering with " << myMoney << "$ Good luck!\n";
	}
	myStartingMoney = myMoney;
	system("pause");
	system("cls");
}

const char* Player::GetName() const
{
	return myName;
}

const int& Player::GetMoney() const
{
	return myMoney;
}

void Player::SetMoney(int aValue)
{
	myMoney = aValue;
}

const int& Player::GetStartingMoney() const
{
	return myStartingMoney;
}


Player::Wins& Player::GetWinsStruct()
{
	return myWins;
}

Player Player::operator+= (int rhs)
{
	this->myMoney += rhs;
	return *this;
}

Player Player::operator-= (int rhs)
{
	return operator+=(-rhs);
}

bool Player::NameIsQrikko()
{
	std::string name = myName;
	if (name == "Qrikko")
	{
		return true;
	}
	return false;
}

bool Player::NameIsJoel()
{
	std::string name = myName;
	if (name == "Joel")
	{
		return true;
	}
	return false;
}

bool Player::NameIsClaudia()
{
	std::string name = myName;
	if (name == "Claudia")
	{
		return true;
	}
	return false;
}