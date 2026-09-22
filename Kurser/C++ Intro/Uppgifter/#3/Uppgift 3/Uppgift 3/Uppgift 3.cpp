#include "GameManager.h"
#include "Player.h"
#include <iostream>

/*
* TODO:
* 1. Refactor with classes
*		a. 1 class/game, with header & cpp. membervariable tracking profits in that specific game.
*		b. A Casino class, that holds all the games, with a membervariable for each game.
*		c. (a & b +): Membervariables should be:
*			I: "private:", with Get() functions when necessary.
*			II: Can be "const" if useful.
*			III: If all classes of that type share it, it can be static!!!
***		d. Memberfunctions that don't alter membervariables should be "const".
*		c. Think about constructor parameters, and try to limit them.
* 2. Multiple alternatives in a game
*		a. Guessing Game should be able to have different betting limits. Think Low Stakes & High Stakes tables. Bet & ban-limits. A constructor could be used effectively for this.
*		b. The different bet-limits should be displayed.
*		c. If the player doesn't have enough to bet the min-bet, they should be returned to the main menu.
* 3. Player name (IMO, could be a Player class)
*		a. Entered at the beginning of the game.
*		b. Only letters.
*		c. Between 2-16 letters long.
***		d. Should be used throughout the game.
*		e. 17-element char array (last one for the \0). cin.get(nameVar, size(17)) could be the easiest way to access it.
*		f. Should not be sent or returned as a copy, always a const char*, to prevent copy-ing.
* 
* KNOWN BUGS/Issues:
* 1. SkyHighGame victory array. Unsure how to pass an array with multiple values in a good way for construction.
*	float myVictoryMultiplierArray[PlayData::multiplierArraySize] = { 1.2f, 1.5f, 2.0f, 3.0f, 5.0f, 8.0f ,12.0f ,20.0f }; doesn't seem to work well.
* 2. Roulette board size can not functionaly be made to have a dynamic size. Might be solved with a static struct with a color array & size, in theory.
*/

int main()
{
	Player player(400);
	GameManager manager(player);
	manager.StartPlaying();
}