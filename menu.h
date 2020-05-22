#ifndef MENU_H_
#define MENU_H_

#include "person.h"
#include "texture.h"
#include <tuple>
#include <utility>

const float SIZE = 800;

class MenuItem{
public:
	MenuItem(float length, float high, int* color, float x, float y, const sf::Texture& texture); //создать вариант меню

	MenuItem(); //создать

	void setBound(float length, float high, int* color, float x, float y); //обозначить его контур

	void DrawItem(sf::RenderWindow& window); //нарисовать вариант меню

	std::tuple<float, float, float, float> getBound(); //получить границы вариантов

	bool Check(float a, float b); //проверить, нажат ли этот вариант

private:
	sf::RectangleShape item;
};

int StartMenu(Person& Our_Hero); //меню выбора персонажа

void CastomizeMenu(Person& Our_Hero, int class_Our_Hero); //меню выбора текстуры

#endif /* MENU_H_ */
