#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "gameplaySupport.h"

void CheckMoveHero(Person& Our_Hero, Room* current_room);

void CheckPassDoors(bool& flag_keyboardQ, Person& Our_Hero, Room*& current_room, sf::RenderWindow& window_H);

//void CheckGiveItems(bool& flag_keyboardE, Person& Our_Hero, Room*& current_room);

void WorkWithInventory(bool& flag_keyboardR, Person& Our_Hero, Room*& current_room);

void ShowInventory(Person& Our_Hero, Room* current_room);

#endif /* GAMEPLAY_H_ */
