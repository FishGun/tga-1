/*
* TODO:
	4.1 - Diablo I: Dungeon
		0: (For fun only) Dungeon Generator
			a: Randomly generate name from 2 arrays (prefix & suffix. E.g. "The" "Dungeon", "Lord Gorak's" "Lair", "The Holy" "Circus")
		1: Event System
			a: Combat
				I: Any amount of Enemies in a given Combat.
				II: Attack value & efense should be used to calculate damage to the player & enemies.
				III: Player should be able to choose a target.
				IV: Enemy dies and is removed from Combat as soon as it has no hp.
		3: Enemy
			a: Enemies & Player should use a Entity class for generic data/functions.
			b:
		2: Player
			a: Enemies & Player should use a Entity class for generic data/functions.
			b: Name
			c: Primary attributes: Strength, Dexterity, Physique.
				I: Derived attributes (examples, could be differently calculated if desired): Attack-value (Str*Dex), Max-hp (Pys * 4 + Str * 6 + Dex * 3), Carrying-capacity (Str + Dex / 3), Defense (Phy * Dex)
		3: Navigation System
			a: Rooms
				I: Between 3-5 rooms.
				II: One or more doors to other rooms. Should support up to 4 doors.
				III: All rooms don't have to have enemies.
				IV: When entering a room, information about it should be displayed (see player's status display).
					1. Name and/or description should be displayed, so the player can tell which room they are in.
			b: Doors
				I: Keeps track of which rooms they connect to (an #include "Rooms.h" makes sense to me). The Door is what should be used to know what room the player goes into.
				II: Should be able to connect between any two rooms (referenses to two rooms makes sense to me).
				III: Should be able to be locked or unlocked. If the door is locked, a Lockpick (Dex) and a Smash (Str) check should both be performable, comparing the stat to a DC.
					1. The door should be unlocked both ways. Only one "locked state" that changes.
			c: Should be disabled during Events (Combat).
		4: Menu system
			a: Room Menu
				I: Select door, stats, and more in the future (e.g. inventory, pick up loot)
				II: Should not be availiable during an Event (Combat).
			b: Main Menu
				I: Select Play Game, or Cheats
					1. A Invincibility cheat & a Instakill cheat.
			c: Having menus be numbered 1-9 makes sense. Could have a generic function with a "Prompt string", and then an array of "choice strings", which then returns the int chosen (making sure it is a number and within the range).
		5: Win-condition
			a: Whatever I want (kill enough enemies, kill all enemies, kill a boss, whatever). It should be clear to the player though.
		6: Display System
			a: Display player's status (room, health, kills)
			b: Display stats (when asked by menu system).
			c: Display Event occurances (which Enemies damaged the player, who the player damaged, how many enemies are left, and how much health all participans have)
			d: Display what happened if the player dies.
	4.2 - Diablo II: Loots
	4.3 - Diablo II: Hell Factory
	5 (endast för VG) - Diablo - Inventory
*/

/*
	Actionable Steps:
		Make .h structure, deepest-first.
			Entity Class
				Generic Data
			Player Class
			Enemy Class
			Event Class
				Combat possiblity
			Room Class
				Event possibility
				Door storage.
			Door Class
				Room storage.
			Dungeon Class
			Game Manager Class
*/
// Tasks: Make Events make sense. How can a room possibly both have an event, and not?
// Room should not have a type currently (or maybe just a dummy enum), currently it only specifies event data.
// Random dungeon gen.
// Enemies should be able to die (and get removed from the myEnemies vector in the Event class).

#include "GameLoop.h"

int main()
{
	GameLoop();
	system("pause");
}