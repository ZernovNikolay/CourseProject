#ifndef GAMEPLAYSUPPORT_H_
#define GAMEPLAYSUPPORT_H_

#include "person.h"
#include "room.h"

int CheckItems(const std::vector<std::shared_ptr<Object>>& gh, const Person& Our_Hero);

bool CheckItem(const std::shared_ptr<Object>& item, const Person& Our_Hero);

int CheckDoors(Room* current_room, const Person& Our_Hero);

bool CheckDoor(Door* door, const Person& Our_Hero);

bool CheckClosedDoor(Door* door, Inventory* sd);

void CheckButtonLeftOnInventory(bool& flagLeft, Person& Our_Hero, const sf::Vector2i& pixelPos);

void CheckButtonRightOnInventory(bool& flagRight, Person& Our_Hero, const sf::Vector2i& pixelPos, Room*& current_room);

#endif /* GAMEPLAYSUPPORT_H_ */
