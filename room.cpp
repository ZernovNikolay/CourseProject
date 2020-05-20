#include "room.h"
#include <iostream>

Door::Door(const float x, const float y, int new_way){
	door.setSize(sf::Vector2f(10.f, 10.f));
	door.setOutlineThickness(10);
	door.setPosition(sf::Vector2f(x, y));
	door.setOutlineColor(sf::Color(255, 255, 255));
	door.setFillColor(sf::Color(0, 0, 0));
	way = new_way;
	opened = true;
	quest = 0;
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

void Door::SetOpen(){
	if(!opened){
		door.setOutlineColor(sf::Color(255, 255, 255));
		opened = true;
		quest = 0;
	}
}

void Door::SetClose(int answer){
	if(opened){
		door.setOutlineColor(sf::Color(0, 0, 0));
		opened = false;
		quest = answer;
	}
}

int Door::GetQuest() const{
	return quest;
}

bool Door::GetOpen() const{
	return opened;
}

bool Room::checkTimer() {
	if (std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - current_time).count() > timedif) {
		current_time = std::chrono::steady_clock::now();
		return true;
	}
	return false;
}

void Room::timeBasedEvents(Person& player) {

	auto cur_bound = GetBound();
	int curbound_right_x = cur_bound.getPosition().x
		+ cur_bound.getSize().x - cur_bound.getOutlineThickness();
	int curbound_left_x = cur_bound.getPosition().x;
	int curbound_bottom_y = cur_bound.getPosition().y
		+ cur_bound.getSize().y - cur_bound.getOutlineThickness();
	int curbound_top_y = cur_bound.getPosition().y;

	std::set<std::list<Projectile>::iterator> projectiles_to_be_deleted;
	std::set<std::list<Enemy*>::iterator> enemies_to_be_deleted;
	std::list<std::list<DeathAnimation*>::iterator> death_animations_to_be_erased;
	/*for (const auto& enemy : enemies) {
		enemy->toMove(player);
	}*/

	for (auto player_projectile = player_projectiles.begin();
		player_projectile != player_projectiles.end(); 
		player_projectile++) {

		player_projectile->toMove();

		for (auto enemy = enemies.begin();
			enemy != enemies.end(); enemy++) {
			if (player_projectile->checkCollision((*enemy)->GetPosition())) {
				projectiles_to_be_deleted.insert(player_projectile);
				if ((*enemy)->receiveDamage(player_projectile->getDamage())) {
					enemies_to_be_deleted.insert(enemy);
					death_animations.
						push_back(new DeathAnimation{ (*enemy)->GetPosition(),
							death_animation_tick_count });
				}
				break;
			}
		}

		auto pp_pos = player_projectile->getPosition();
		int pp_x = pp_pos.x, pp_y = pp_pos.y;
		if (pp_x <= curbound_left_x || pp_x >= curbound_right_x
			|| pp_y <= curbound_top_y || pp_y >= curbound_bottom_y) {
			projectiles_to_be_deleted.insert(player_projectile);
		}

	}

	for (auto death_animation = death_animations.begin();
		death_animation != death_animations.end(); death_animation++) {
		if ((*death_animation)->checkTime()) {
			death_animations_to_be_erased.push_back(death_animation);
		}
	}

	for (auto& it : death_animations_to_be_erased) {
		death_animations.erase(it);
	}

	for (auto& it : projectiles_to_be_deleted) {
		player_projectiles.erase(it);
	}

	for (auto& it : enemies_to_be_deleted) {
		enemies.erase(it);
	}

	if (attack_cur_timedif % attack_generating_timedif == 0) {
		checkAttack();
		sf::Vector2f player_pos = player.GetPosition();
		if (createProjectile(player_pos, player.getDamage()))
			attack_cur_timedif = 1;
	}
	else {
		attack_cur_timedif++;
	}
}

Room::Room(bool first_room_flag){
	if (!first_room_flag) {
		int enemy_num = std::rand() % 4;
		std::cout << enemy_num << std::endl;
		for (int i = 0; i < enemy_num; i++) {
			enemies.push_back(new Rat());
		}
	}
	bound.setSize(sf::Vector2f(400.f, 400.f));
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

void Room::SetWeapon(float x, float y, int damage, const std::string& new_name){
	items.push_back(std::make_shared<Weapon>("Weapon", x, y, damage, new_name));
}

void Room::SetHeal(float x, float y, int healing, const std::string& new_name){
	items.push_back(std::make_shared<Heal>("Heal", x, y, healing, new_name));
}

void Room::SetKey(float x, float y, int new_key){
	items.push_back(std::make_shared<Key>("Key", x, y, new_key));
}

void Room::SetBound(int* color){
	bound.setSize(sf::Vector2f(400.f, 400.f));
	bound.setFillColor(sf::Color(color[0], color[1], color[2]));
	bound.setPosition(sf::Vector2f(200, 200));
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

void Room::GiveItem(Inventory* sd, int gh){
	sd->SetItem(items[gh]);
	items.erase(items.begin() + gh);
}

void Room::SetItem(Inventory* sd, int gh, float x, float y){
	items.push_back(sd->GetItem(gh));
	items[items.size()-1]->SetPosition(x,y);
	sd->EraseItem(gh);
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

int& Room::getBulletX() {
	return bullet_x;
}
int& Room::getBulletY() {
	return bullet_y;
}

const std::list<Enemy*>& Room::getEnemies() const {
	return enemies;
}

void Room::checkAttack() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		bullet_x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		bullet_x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		bullet_y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		bullet_y = 1;
	}
}
bool Room::createProjectile(sf::Vector2f& player_pos, int damage) {
	if (bullet_x != 0 || bullet_y != 0) {
		player_projectiles.push_back(Projectile(player_pos, damage, bullet_x, bullet_y));
		std::cout << bullet_x << " " << bullet_y << std::endl;
		bullet_x = 0;
		bullet_y = 0;
		return true;
	}
	return false;
}
const std::list<Projectile>& Room::getPlayerProjectiles() const {
	return player_projectiles;
}

const std::list<Projectile>& Room::getEnemyProjectiles() const {
	return enemy_projectiles;
}

std::list<DeathAnimation*>& Room::getDeathAnimations() {
	return death_animations;
}