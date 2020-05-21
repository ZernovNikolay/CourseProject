#pragma once
#include <SFML/Graphics.hpp>
#include "person.h"
#include <cmath>
#include <ctime>
#include <list>
const float ROOM_SIZE = 400;
//const std::string _src_path_ = "../src/textures/";
//const std::string _src_path_ = "/home/nikolay/Desktop/Eclipse/smfl/src/textures/";
class Enemy {
private:
	sf::Sprite enemy_model;
	virtual void SetModel() = 0; // ���������� ��������
	int health_point = 3;
public:
	sf::Vector2f GetPosition() const; // �������� �������������� ���������
	sf::Sprite& GetModel(); // �������� �������� �����
	void SetPosition(); // ���������� �������������� ��� ���������
	virtual sf::Vector2f toMove(Person& player) = 0;
	bool receiveDamage(int damage);
};

class Rat : public Enemy{
	int health_point = 3;
	const int damage = 1;
	const float step = 3;
	int step_count = 0;
	sf::Texture texture;
	void SetModel() override;
	~Rat();
public:
	Rat() {
		SetModel();
		SetPosition();
		//std::cout << GetPosition().x << " " << GetPosition().y;
	}
	sf::Vector2f toMove(Person& player) override;
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
	//DeathAnimation(const DeathAnimation&);
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
