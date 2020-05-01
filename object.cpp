#include "object.h"
#include <iostream>

Object::Object(const std::string& name, float x, float y){
	type = name;
	bound.setRadius(5);
	bound.setOutlineThickness(3);
	bound.setPosition(sf::Vector2f(x, y));
	bound.setOutlineColor(sf::Color(0, 0, 0));
	bound.setFillColor(sf::Color(255, 255, 255));
}

Object::~Object(){
}

void Object::SetPosition(float x, float y){
	bound.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Object::GetPosition() const {
	return bound.getPosition();
}

sf::CircleShape Object::GetBound() const{
	return bound;
}

std::string Object::GetType() const{
	return type;
}

Weapon::Weapon(const std::string& type, float x, float y) : Object(type, x, y){
	//std::cout << "Weapon +" << std::endl;

	/*sf::RenderWindow window_H(sf::VideoMode(800, 800), "My window");

	while (window_H.isOpen())
	{
		sf::Event event;
		while (window_H.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_H.close();
		}
		window_H.clear(sf::Color::White);
		window_H.draw(bound);
		window_H.display();
	}*/
}

Weapon::~Weapon(){
	//std::cout << "Weapon -" << std::endl;
}

void Weapon::SetPosition(float x, float y){
	Object::SetPosition(x, y);
}

sf::Vector2f Weapon::GetPosition() const {
	return Object::GetPosition();
}

sf::CircleShape Weapon::GetBound() const{
	return Object::GetBound();
}
