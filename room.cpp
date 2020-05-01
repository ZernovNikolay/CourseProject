#include <room.h>
#include <iostream>

Door::Door(const float x, const float y, int new_way){
	door.setSize(sf::Vector2f(10.f, 10.f));
	door.setOutlineThickness(10);
	door.setPosition(sf::Vector2f(x, y));
	door.setOutlineColor(sf::Color(255, 255, 255));
	door.setFillColor(sf::Color(0, 0, 0));
	way = new_way;
	//std::cout << x << " " << y << " " << way << std::endl;
}

sf::RectangleShape Door::GetBound() const{
	return door;
}

sf::Vector2f Door::GetPosition() const{
	return door.getPosition();
}

int Door::GetWay() const{
	return way;
}

Room::Room(){
	bound.setSize(sf::Vector2f(200.f, 200.f));
	bound.setOutlineThickness(10);
}

Room::~Room(){
	//std::cout << "FUCK YOU!" << std::endl;
	for(size_t i = 0; i < door.size(); i++){
		delete door[i];
	}
}

void Room::SetLeftDoor(){
	door.push_back(new Door(bound.getPosition().x, bound.getPosition().y + bound.getSize().y/2, 4));
}

void Room::SetRightDoor(){
	door.push_back(new Door(bound.getPosition().x + bound.getSize().x, bound.getPosition().y + bound.getSize().y/2, 2));
}

void Room::SetUpDoor(){
	door.push_back(new Door(bound.getPosition().x + bound.getSize().x/2, bound.getPosition().y, 1));
}

void Room::SetDownDoor(){
	door.push_back(new Door(bound.getPosition().x + bound.getSize().x/2, bound.getPosition().y + bound.getSize().y, 3));
}

void Room::SetLeft(Room* gh){
	left = gh;
	SetLeftDoor();
}

void Room::SetRight(Room* gh){
	right = gh;
	SetRightDoor();
}

void Room::SetUp(Room* gh){
	up = gh;
	SetUpDoor();
}

void Room::SetDown(Room* gh){
	down = gh;
	SetDownDoor();
}

void Room::SetWeapon(float x, float y){
	items.push_back(std::make_shared<Weapon>("Weapon", x, y));
}

void Room::SetBound(float length, float high, int* color, float x, float y){
	bound.setSize(sf::Vector2f(200.f, 200.f));
	bound.setFillColor(sf::Color(color[0], color[1], color[2]));
	bound.setPosition(sf::Vector2f(x, y));
	bound.setOutlineColor(sf::Color(0, 0, 0));
}

sf::RectangleShape Room::GetBound(){
	return bound;
}

std::vector<Door*> Room::GetDoors(){
	return door;
}

std::vector<std::shared_ptr<Object>> Room::GetObjects(){
	return items;
}

void Room::GiveItem(Inventory& sd, int gh){
	sd.SetItem(items[gh]);
	items.erase(items.begin() + gh);
}

void Room::SetItem(Inventory& sd, int gh, float x, float y){
	items.push_back(sd.GetItem(gh));
	items[items.size()-1]->SetPosition(x,y);
	sd.EraseItem(gh);
}

Room* Room::toLeft() const{
	return left;
}

Room* Room::toRight() const{
	return right;
}

Room* Room::toUp() const{
	return up;
}

Room* Room::toDown() const{
	return down;
}

void RoomBindLR(Room* lhs, Room* rhs){
	rhs->SetLeft(lhs);
	lhs->SetRight(rhs);
}

void RoomBindUD(Room* up, Room* down){
	up->SetDown(down);
	down->SetUp(up);
}
