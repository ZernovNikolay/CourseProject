#ifndef GAMEPLAYSUPPORT_H_
#define GAMEPLAYSUPPORT_H_

#include "person.h"
#include "room.h"

bool CheckWall(const Wall* wall, float x, float y); //проверка конкретной стены

bool CheckWalls(const std::vector<Wall*> walls, float x, float y); //проверить, не мешают ли движению героя стены

void CheckGiveItems(bool& flag_keyboardE, Person& Our_Hero, Room*& current_room);//поднять предмет, если можно

int CheckItems(const std::vector<std::shared_ptr<Object>>& gh, const Person& Our_Hero); //проверить, можно ли поднять предмет

bool CheckItem(const std::shared_ptr<Object>& item, const Person& Our_Hero); //проверить конкретный предмет

int CheckDoors(Room* current_room, const Person& Our_Hero); //проверить можно ли использовать дверь

bool CheckDoor(Door* door, const Person& Our_Hero); //проверить конкретную дверь

bool CheckClosedDoor(Door* door, Inventory* sd); //проверить, открыта ли дверь

void CheckButtonLeftOnInventory(bool& flagLeft, Person& Our_Hero, const sf::Vector2i& pixelPos); //использовать левую кнопку мыши в инвентаре

void CheckButtonRightOnInventory(bool& flagRight, Person& Our_Hero, const sf::Vector2i& pixelPos, Room*& current_room); //использовать правую кнопку мыши в инвентаре

#endif /* GAMEPLAYSUPPORT_H_ */
