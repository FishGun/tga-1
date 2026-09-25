#pragma once

class Player
{
public:
	const struct Wins
	{
		static const int gameHistoryArraySize = 5;
		int gameHistory[gameHistoryArraySize];
		int total;
	};

	Player();
	Player(int aMoney);

	const char* GetName() const;

	const int& GetMoney() const;
	void SetMoney(int aValue);
	const int& GetStartingMoney() const;

	Wins& GetWinsStruct();

	Player operator+= (int rhs);

	Player operator-= (int rhs);

	bool NameIsQrikko();
	bool NameIsJoel();
	bool NameIsClaudia();

private:
	char myName[17];
	int myMoney;
	int myStartingMoney;
	Wins myWins;
};