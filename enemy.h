#pragma once
#include <SFML/Graphics.hpp>
#include "person.h"
#include <ctime>
const float ROOM_SIZE = 400;
//const std::string _src_path_ = "../src/textures/";
class Enemy {
private:
	sf::Sprite enemy_model;
	virtual void SetModel() = 0; // установить модельку
public:
	sf::Vector2f GetPosition() const; // получить местоположение персонажа
	sf::Sprite& GetModel(); // получить модельку героя
	void SetPosition(); // установить местоположение для персонажа
	virtual sf::Vector2f move(Person& player) = 0;
};

class Rat : public Enemy{
	int health_point = 3;
	const int damage = 1;
	const float step = 50;
	int step_count = 0;
	sf::Texture texture;
	void SetModel() override;
public:
	Rat() {
		SetPosition();
		SetModel();
	}
	sf::Vector2f move(Person& player) override;
};
