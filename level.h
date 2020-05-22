#ifndef LEVEL_H_
#define LEVEL_H_

#include "room.h"
#include <string>
#include "person.h"
#include "menu.h"
#include "gameplay.h"

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
	bool first_room_flag = true;
};

void RenderLevel(Person& Our_Hero); // сделать и прорисовывать уровень

#endif /* LEVEL_H_ */
