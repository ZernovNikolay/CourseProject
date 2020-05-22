#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "gameplaySupport.h"

void CheckMoveHero(Person& Our_Hero, Room* current_room); //движение героя, если это возможно

void CheckPassDoors(bool& flag_keyboardQ, Person& Our_Hero, Room*& current_room, sf::RenderWindow& window_H); //войти в дверь если это возможно

void WorkWithInventory(bool& flag_keyboardR, Person& Our_Hero, Room*& current_room); //взаимодействовать с инвентарём

void ShowInventory(Person& Our_Hero, Room* current_room);//показать инвентарь

#endif /* GAMEPLAY_H_ */
