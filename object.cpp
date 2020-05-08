#include "object.h"
#include <iostream>

void LoadTextures(){
	texture_weapon.loadFromFile("/home/nikolay/Desktop/Eclipse/smfl/src/sword.png");
	texture_heal.loadFromFile("/home/nikolay/Desktop/Eclipse/smfl/src/heal.png");
	texture_key.loadFromFile("/home/nikolay/Desktop/Eclipse/smfl/src/key.png");
}

Object::Object(const std::string& name){
	type = name;
	if(type == "Weapon"){
		typeInt = 0;
	}else if(type == "Heal"){
		typeInt = 1;
	}else if(type == "Key"){
		typeInt = 2;
	}
}

Object::~Object(){
}

std::string Object::GetType() const{
	return type;
}

int Object::GetTypeInt() const{
	return typeInt;
}

Weapon::Weapon(const std::string& type, float x, float y, int new_damage, const std::string& new_name) : Object(type){
	/*bound.setRadius(5);
	bound.setOutlineThickness(3);
	bound.setPosition(sf::Vector2f(x, y));
	bound.setOutlineColor(sf::Color(0, 0, 0));
	bound.setFillColor(sf::Color(255, 255, 255));*/
	damage = new_damage;
	name = new_name;

	bound.setTexture(texture_weapon, true);
	bound.setScale(0.03f, 0.03f);//уменьшаем размер текстуры вдвое
	bound.setPosition(sf::Vector2f(x, y));

}

Weapon::~Weapon(){
	//std::cout << "Weapon -" << std::endl;
}

void Weapon::SetPosition(float x, float y){
	bound.setPosition(x, y);
}

sf::Vector2f Weapon::GetPosition() const {
	return bound.getPosition();
}

sf::Sprite Weapon::GetBound() const{
	return bound;
}

std::string Weapon::GetName() const{
	return name;
}

int Weapon::GetStats() const{
	return damage;
}

Heal::Heal(const std::string& type, float x, float y, int new_healing, const std::string& new_name) : Object(type){
	/*bound.setRadius(5);
	bound.setOutlineThickness(3);
	bound.setPosition(sf::Vector2f(x, y));
	bound.setOutlineColor(sf::Color(0, 0, 0));
	bound.setFillColor(sf::Color(0, 255, 0));*/

	bound.setTexture(texture_heal, true);//называем нашу текстуру circle
	bound.setScale(0.9f, 0.9f);//уменьшаем размер текстуры вдвое
	bound.setPosition(sf::Vector2f(x, y));
	healing = new_healing;
	name = new_name;
}

Heal::~Heal(){

}

void Heal::SetPosition(float x, float y){
	bound.setPosition(x, y);
}

sf::Vector2f Heal::GetPosition() const {
	return bound.getPosition();
}

sf::Sprite Heal::GetBound() const{
	return bound;
}

std::string Heal::GetName() const{
	return name;
}

int Heal::GetStats() const{
	return healing;
}

Key::Key(const std::string& type, float x, float y, int new_key) : Object(type){
	/*bound.setRadius(5);
	bound.setOutlineThickness(3);
	bound.setPosition(sf::Vector2f(x, y));
	bound.setOutlineColor(sf::Color(0, 0, 0));
	bound.setFillColor(sf::Color(255, 69, 0));*/

	bound.setTexture(texture_key, true);//называем нашу текстуру circle
	bound.setScale(0.04f, 0.04f);//уменьшаем размер текстуры вдвое
	bound.setPosition(sf::Vector2f(x, y));
	key = new_key;
}

Key::~Key(){

}

void Key::SetPosition(float x, float y){
	bound.setPosition(x, y);
}

sf::Vector2f Key::GetPosition() const {
	return bound.getPosition();
}

sf::Sprite Key::GetBound() const{
	return bound;
}

std::string Key::GetName() const{
	return "KEY DOESN'T HAVE NAME";
}

int Key::GetStats() const{
	return key;
}
