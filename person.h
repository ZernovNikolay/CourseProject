#ifndef PERSON_H_
#define PERSON_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "object.h"

const float velocity = 0.2;

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
	Person(std::string gh); // добавить имя для персонажа

	Person();

	~Person();

	void SetCharacter(std::string gh); // добавить класс персонажа и установить его хп

	void YouAreWarrior(); // сделать воином

	void YouAreArcher(); // сделать лучником

	void YouAreRogue(); // сделать вором

	void SetHP(int gh); // установить хп

	void SetModel(sf::Sprite new_model); // установить модельку

	void SetTexture(const std::string& name); // установить имя файла для модельки

	void SetPosition(float x, float y); // установить местоположение для персонажа

	void move(float x, float y); // передвижение персонажа

	sf::Vector2f GetPosition() const; // получить местоположение персонажа

	sf::Sprite GetModel() const; // получить модельку героя

	Inventory* GetInventory();

private:

	void SetClass(std::string gh); // установить класс

	std::string class_type;
	int health_point = 0;
	std::string name;
	sf::Sprite model_of_hero;
	std::string name_texture;

	Inventory* inventory;
};

#endif /* PERSON_H_ */
