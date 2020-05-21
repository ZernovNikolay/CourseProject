#ifndef PERSON_H_
#define PERSON_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <chrono>
#include "object.h"

const float velocity = 0.24;

class Inventory{
public:
	Inventory();

	~Inventory();

	void SetItem(std::shared_ptr<Object> gh);

	size_t GetSize() const;

	std::shared_ptr<Object> GetItem (int gh);

	void EraseItem(int gh);

private:
	std::vector<std::shared_ptr<Object>> items = {};
};

class Person{
public:
	enum class_type {Warrior, Mage, Archer};

	Person(std::string gh); // добавить имя для персонажа

	Person();

	~Person();

	void SetCharacter(std::string gh); // добавить класс персонажа и установить его хп

	void YouAreWarrior(); // сделать воином

	void YouAreArcher(); // сделать лучником

	void YouAreMage(); // сделать вором

	void SetModel(sf::Sprite new_model); // установить модельку

	void SetTexture(const std::string& name); // установить имя файла для модельки

	void SetPosition(float x, float y); // установить местоположение для персонажа

	void move(float x, float y); // передвижение персонажа

	sf::Vector2f GetPosition() const; // получить местоположение персонажа

	sf::Sprite GetModel() const; // получить модельку героя

	Inventory* GetInventory();

	void UseItem(int number);

	void receiveDamage(int damage);//нанести урон игроку

	int getDamage() const; //getter для damage

	enum class_type getClassType() const;
private:

	std::chrono::time_point<std::chrono::steady_clock> current_time
		= std::chrono::steady_clock::now();

	int invul_time_milliseconds = 500;

	bool checkTimer();

	void SetClass(enum class_type ct); // установить класс

	void SetHP(int gh); // установить хп


	int health_point = 10;
	//std::string class_type;
	class_type type;
	std::string name;
	sf::Sprite model_of_hero;
	std::string name_texture;
	int damage = 3;

	Inventory* inventory;
};

#endif /* PERSON_H_ */
