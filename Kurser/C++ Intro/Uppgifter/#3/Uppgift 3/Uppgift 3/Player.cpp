#include "Player.h"
#include <iostream>

Player::Player() : Player::Player(100)
{

}

Player::Player(int aMoney)
{
	myMoney = aMoney;

	bool nameValid = false;
	do
	{
		std::cout << "Please, enter your name (2-16 characters): ";
		std::cin.get(Player::myName, 18);
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		for (int i = 0; i < 17; i++)
		{
			if (i >= 2 && Player::myName[i] == '\0')
			{
				nameValid = true;
				break;
			}
			else if (Player::myName[i] == '\0')
			{
				std::cout << "\nError: Name too short. Please stick to 2 character or more.\n\n";
				break;
			}
			else if (i >= 16)
			{
				std::cout << "\nError: Name too long. Please stick to 16 character or less.\n\n";
				break;
			}

			int nameIndexIntCasted = static_cast<int>(Player::myName[i]);
			if (i == 0 && !(nameIndexIntCasted >= 65 && nameIndexIntCasted <= 90))
			{
				std::cout << "\nError: The first input must be a capital letter.\n\n";
				break;
			}
			else if (i > 0 && !(nameIndexIntCasted >= 97 && nameIndexIntCasted <= 122))
			{
				std::cout << "\nError: Name may only consist of letters.\n\n";
				break;
			}
		}

	} while (!nameValid);

	std::cout <<
		"\nWelcome, " << Player::GetName() << "!\n"
		"You are entering with " << myMoney << "$ Good luck!\n";
	system("pause");
	system("cls");
}

const char* Player::GetName() const
{
	return Player::myName;
}

const int& Player::GetMoney() const
{
	return myMoney;
}

void Player::SetMoney(int aValue)
{
	myMoney = aValue;
}

const Player::Wins& Player::GetWinsStruct() const
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