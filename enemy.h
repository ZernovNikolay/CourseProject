#pragma once
#include <SFML/Graphics.hpp>
#include "person.h"
#include <ctime>
const float ROOM_SIZE = 400;
//const std::string _src_path_ = "../src/textures/";
class Enemy {
private:
	sf::Sprite enemy_model;
	virtual void SetModel() = 0; // ���������� ��������
public:
	sf::Vector2f GetPosition() const; // �������� �������������� ���������
	sf::Sprite& GetModel(); // �������� �������� �����
	void SetPosition(); // ���������� �������������� ��� ���������
	virtual sf::Vector2f move(Person& player) = 0;
};

class Rat : public Enemy{
	int health_point = 3;
	const int damage = 1;
	const float step = 15;
	int step_count = 0;
	sf::Texture texture;
	void SetModel() override;
public:
	Rat() {
		SetModel();
		SetPosition();
		std::cout << GetPosition().x << " " << GetPosition().y;
	}
	sf::Vector2f move(Person& player) override;
};