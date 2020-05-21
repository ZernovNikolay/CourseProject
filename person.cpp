#include "person.h"

Person::Person(std::string gh){
	name = gh;
	inventory = new Inventory;
}

Person::Person(){}

Person::~Person(){
	std::string s;
	switch (type) {
	case(class_type::Archer):
		s = "Archer";
		break;
	case(class_type::Warrior):
		s = "Warrior";
		break;
	case(class_type::Mage):
		s = "Mage";
		break;
	}
	std::cout << "Your name is " << name << "\n" << "Your class is " << s
			<< "\n" << "Your health is " << health_point << "\n" << "Texture is on file: " << name_texture << std::endl;
	delete inventory;
}

void Person::SetCharacter(std::string gh){
	if(gh == "Warrior"){
		YouAreWarrior();
	}else if(gh == "Archer"){
		YouAreArcher();
	}else if(gh == "Mage"){
		YouAreMage();
	}
}

void Person::YouAreWarrior(){
	SetClass(class_type::Warrior);
	SetHP(100);
}

void Person::YouAreArcher(){
	SetClass(class_type::Archer);
	SetHP(70);
}

void Person::YouAreMage(){
	SetClass(class_type::Mage);
	SetHP(87);
}

void Person::SetClass(Person::class_type ct) {
	type = ct;
}

void Person::SetHP(int gh){
	health_point = gh;
}

void Person::SetModel(sf::Sprite new_model){
	model_of_hero = new_model;
}

void Person::SetTexture(const std::string& name){
	name_texture = name;
}

void Person::SetPosition(float x, float y){
	model_of_hero.setPosition(x, y);
}

void Person::move(float x, float y){
	model_of_hero.setPosition(model_of_hero.getPosition().x + x, model_of_hero.getPosition().y + y);
}

sf::Vector2f Person::GetPosition() const{
	return sf::Vector2f(model_of_hero.getPosition().x, model_of_hero.getPosition().y);
}

sf::Sprite Person::GetModel() const{
	return model_of_hero;
}

Inventory* Person::GetInventory(){
	return inventory;
}

void Person::UseItem(int number){
	int gh = inventory->GetItem(number)->GetTypeInt();
	int made = inventory->GetItem(number)->GetStats();
	switch(gh){
	case 0:
		damage+=made;
		inventory->EraseItem(number);
		break;
	case 1:
		health_point+=made;
		inventory->EraseItem(number);
		break;
	case 2:
		std::cout << "You can't use this" << std::endl;
		break;
	}
}

void Person::receiveDamage(int damage) {
	if (checkTimer()) {
		health_point -= damage;
		std::cout << "got hit" << std::endl;
	}
	if (health_point <= 0){
		std::cout << "Game over!" << std::endl;
		exit(0);
	}
}
Inventory::Inventory(){}

Inventory::~Inventory(){
	std::cout << "Your inventory:\n";
	for(size_t i = 0; i < items.size(); i++){
		std::cout << items[i]->GetType() << " /" << items[i]->GetName() << "/ " << items[i]->GetStats() << "\n";
	}
};

void Inventory::SetItem(std::shared_ptr<Object> gh){
	items.push_back(gh);
}

size_t Inventory::GetSize() const{
	return items.size();
}

std::shared_ptr<Object> Inventory::GetItem (int gh){
	return items[gh];
}

void Inventory::EraseItem(int gh){
	items.erase(items.begin() + gh);
}

int Person::getDamage() const {
	return damage;
}

bool Person::checkTimer() {
	if (std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - current_time).count() >
		invul_time_milliseconds) {
		current_time = std::chrono::steady_clock::now();
		return true;
	}
	return false;
}
Person::class_type Person::getClassType() const {
	return type;
}