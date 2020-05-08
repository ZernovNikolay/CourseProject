#ifndef MENU_H_
#define MENU_H_

#include "person.h"
#include "texture.h"
#include <tuple>
#include <utility>

const float SIZE = 800;

class MenuItem{
public:
	MenuItem(float length, float high, int* color, float x, float y, const sf::Texture& texture);

	MenuItem();

	void setBound(float length, float high, int* color, float x, float y);

	void DrawItem(sf::RenderWindow& window);

	std::tuple<float, float, float, float> getBound();

	bool Check(float a, float b);

private:
	sf::RectangleShape item;
};

int StartMenu(Person& Our_Hero);

void CastomizeMenu(Person& Our_Hero, int class_Our_Hero);

#endif /* MENU_H_ */
