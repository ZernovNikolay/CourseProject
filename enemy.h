#pragma once
#include <SFML/Graphics.hpp>
#include "person.h"
#include <ctime>
#include <chrono>
#include <list>
const float ROOM_SIZE = 400;
//const std::string _src_path_ = "../src/textures/";
class Enemy {
private:
	std::chrono::time_point<std::chrono::steady_clock> current_time
		= std::chrono::steady_clock::now();
	std::chrono::time_point<std::chrono::steady_clock> last_time_being_hit = current_time;
	sf::Sprite enemy_model;
	virtual void SetModel() = 0; // установить модельку
	int health_point = 3;
	float velocity = 0.35;
public:
	int direction_swap_time_milliseconds = 500;
	bool checkTimer(); //проверяет, прошло
	sf::Vector2f GetPosition() const; // получить местоположение персонажа
	sf::Sprite& GetModel(); // получить модельку героя
	void SetPosition(); // установить местоположение для персонажа
	virtual sf::Vector2f toMove(Person& player) = 0;// переместить врага (проверяется таймер врага)
	virtual void toMoveSecondAlgorithm(Person& player, sf::RectangleShape) = 0;//переместить врага
	bool receiveDamage(int damage);
};

class Rat : public Enemy{
	float velocity = 0.35;
	int health_point = 3;
	const int damage = 1;
	const float step = 3;
	int step_count = 0;
	sf::Texture texture;
	void SetModel() override;
	sf::Vector2f direction_vector;
	~Rat();
	void setDirVector(Person& player);
public:
	Rat() {
		SetModel();
		SetPosition();
		//std::cout << GetPosition().x << " " << GetPosition().y;
	}
	sf::Vector2f toMove(Person& player) override;
	void toMoveSecondAlgorithm(Person& player, sf::RectangleShape) override;
};

class Projectile {
public:
	//sf::Sprite sprite(10);
	sf::CircleShape getBullet();
	Projectile(sf::Vector2f curpos, int damage, int x_sign, int y_sign);
	bool checkCollision(sf::Vector2f);
	void toMove();
	int getDamage();
	sf::Vector2f getPosition();
	sf::CircleShape getCircleShape() const;
	~Projectile();
private:
	int x_sign = 0, y_sign = 0;
	sf::CircleShape projectile = sf::CircleShape(7);
	float step = 5;
	int damage = 0;
};

class DeathAnimation {
public:
	const sf::Sprite& getModel() const;
	DeathAnimation(sf::Vector2f pos, int max_tick_count);
	bool checkTime();
private:
	sf::Texture texture;
	int cur_tick_count = 0;
	int max_tick_count = 0;
	void setPosition(sf::Vector2f);
	void setModel();
	sf::Sprite sprite;
};

bool operator< (const std::list<Projectile>::iterator& lhs,
	const std::list<Projectile>::iterator& rhs);

bool operator< (const std::list<Enemy*>::iterator& lhs,
	const std::list<Enemy*>::iterator& rhs);