#ifndef ROOM_H_
#define ROOM_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <object.h>
#include "person.h"
#include <memory>

enum class Ways{
	Up,
	Right,
	Down,
	Left,
};

class Door{
public:
	Door(const float x, const float y, const int new_way); // установить новую дверь

	sf::RectangleShape GetBound() const; // получить ее модельку

	sf::Vector2f GetPosition() const; // получить местоположение двери

	int GetWay() const; // получить направление двери установленное в WAYS

private:
	sf::RectangleShape door;
	int way;
};

class Room{
public:
	Room(); // создать комнату

	~Room(); // очистить все указатели

	void SetLeftDoor(); // установить дверь налево
	void SetRightDoor(); // установить дверь направо
	void SetDownDoor(); // установить дверь вниз
	void SetUpDoor(); // установить дверь наверх

	void SetLeft(Room* gh); // привязать комнату налево
	void SetRight(Room* gh); // привязать комнату направо
	void SetUp(Room* gh); // привязать комнату вверх
	void SetDown(Room* gh); // привязать комнату вниз

	void SetWeapon(float x, float y); // создать оружие на точке комнаты

	void SetBound(float length, float high, int* color, float x, float y); // создать контур и цвет комнаты

	sf::RectangleShape GetBound(); // получить модель комнаты
	std::vector<Door*> GetDoors(); // получить двери в комнате
	std::vector<std::shared_ptr<Object>> GetObjects(); // получить объекты в комнате

	void GiveItem(Inventory& sd, int gh);
	void SetItem(Inventory& sd, int gh, float x, float y);

	Room* toLeft() const; // получить комнату слева
	Room* toRight() const; // получить комнату справа
	Room* toUp() const; // получить комнату сверху
	Room* toDown() const; // получить комнату снизу

private:
	sf::RectangleShape bound;
	std::vector<Door*> door = {};
	std::vector<std::shared_ptr<Object>> items = {};
	Room* left = 0;
	Room* right = 0;
	Room* up = 0;
	Room* down = 0;
};

void RoomBindLR(Room* lhs, Room* rhs); // связать комнаты левую и правую

void RoomBindUD(Room* up, Room* down); // связать комнаты верхнюю и нижнюю

#endif /* ROOM_H_ */
