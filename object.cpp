#include "object.h"

Weapon::Weapon(float x, float y){
	bound.setRadius(5);
	bound.setOutlineThickness(3);
	bound.setPosition(sf::Vector2f(x, y));
	bound.setOutlineColor(sf::Color(0, 0, 0));
	bound.setFillColor(sf::Color(255, 255, 255));
}

sf::CircleShape Weapon::GetBound() const{
	return bound;
}
