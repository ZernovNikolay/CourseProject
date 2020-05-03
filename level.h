#ifndef LEVEL_H_
#define LEVEL_H_

#include <room.h>
#include <string>
#include "person.h"

const float SIZE_WINDOW = 800;

class Level{
public:
	Level(int countRoom); // сделать уровень с заданным количеством комнат

	~Level(); // очистить все комнаты

	void NewRoom(); // создать тестовый левел

	sf::RectangleShape GetBegin(); // получить модель первой комнаты

	Room* GetBeginRoom(); // получить первую комнату

private:
	std::vector<Room*> collection;
	int count;
};

void RenderLevel(Person& Our_Hero); // сделать и прорисовывать уровень

int CheckDoors(Room* current_room, const Person& Our_Hero); // проверить объекты (двери)

bool CheckDoor(Door* door, const Person& Our_Hero); // проверить дверь на взаимодействие

int CheckItems(const std::vector<std::shared_ptr<Object>>& gh, const Person& Our_Hero);

bool CheckItem(const std::shared_ptr<Object>& gh, const Person& Our_Hero);

bool CheckClosedDoor(Door* door, Inventory* sd);

#endif /* LEVEL_H_ */
