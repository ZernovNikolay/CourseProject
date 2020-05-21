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


	std::set<std::list<Projectile>::iterator> projectiles_to_be_deleted;
	std::set<std::list<Enemy*>::iterator> enemies_to_be_deleted;
	std::list<std::list<DeathAnimation*>::iterator> death_animations_to_be_erased;


	moveProjectiles(projectiles_to_be_deleted, enemies_to_be_deleted);
	checkDeathAnimations(death_animations_to_be_erased);

	/*for (auto& it : death_animations_to_be_erased) {
		delete *it;
		death_animations.erase(it);
	}
	for (auto& it : projectiles_to_be_deleted) {
		//it;
		player_projectiles.erase(it);
	}
	for (auto& it : enemies_to_be_deleted) {
		delete *it;
		enemies.erase(it);
	}*/
	if (attack_cur_timedif % attack_generating_timedif == 0) {
		if (beam_flag) {
			beam = sf::ConvexShape();
			beam_flag = false;
			attack_dir_x = 0;
			attack_dir_y = 0;
			//std::cout << beam.getPointCount() << std::endl;
		}
		checkAttack();
		sf::Vector2f player_pos = player.GetPosition();
		switch (player.getClassType()) {
			case Person::Archer:
				if (createProjectile(player_pos, player.getDamage()))
					attack_cur_timedif = 1;
				break;
			case Person::Mage:
				if (beam_generation_current_timer % beam_generation_time_coef <= 25) {
					if (attack_dir_x || attack_dir_y) {
						generateBeam(player, enemies_to_be_deleted);
						/*if (generateBeam(player))
							attack_cur_timedif = 1;*/
						beam_flag = true;
						beam_generation_current_timer++;
						attack_dir_x = 0;
						attack_dir_y = 0;
					}
				}
				else {
					beam_generation_current_timer++;
				}
				break;
		}
	}
	else {
		attack_cur_timedif++;
	}

	for (auto& it : death_animations_to_be_erased) {
		delete* it;
		death_animations.erase(it);
	}
	for (auto& it : projectiles_to_be_deleted) {
		//it;
		player_projectiles.erase(it);
	}
	for (auto& it : enemies_to_be_deleted) {
		delete* it;
		enemies.erase(it);
	}
}

Room::Room(bool first_room_flag){
	if (!first_room_flag) {
		int enemy_num = std::rand() % 4;
		//std::cout << enemy_num << std::endl;
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
	return attack_dir_x;
}
int& Room::getBulletY() {
	return attack_dir_y;
}

const std::list<Enemy*>& Room::getEnemies() const {
	return enemies;
}

void Room::checkAttack() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		attack_dir_x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		attack_dir_x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		attack_dir_y = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		attack_dir_y = 1;
	}
}
bool Room::createProjectile(sf::Vector2f& player_pos, int damage) {
	if (attack_dir_x != 0 || attack_dir_y != 0) {
		player_projectiles.push_back(Projectile(player_pos, damage, 
			attack_dir_x, attack_dir_y));
		//std::cout << attack_dir_x << " " << attack_dir_y << std::endl;
		attack_dir_x = 0;
		attack_dir_y = 0;
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

void Room::moveProjectiles(std::set<std::list<Projectile>::iterator>& projectiles_to_be_deleted,
		std::set<std::list<Enemy*>::iterator>& enemies_to_be_deleted) {
	auto cur_bound = GetBound();
	int curbound_right_x = cur_bound.getPosition().x
		+ cur_bound.getSize().x - cur_bound.getOutlineThickness();
	int curbound_left_x = cur_bound.getPosition().x;
	int curbound_bottom_y = cur_bound.getPosition().y
		+ cur_bound.getSize().y - cur_bound.getOutlineThickness();
	int curbound_top_y = cur_bound.getPosition().y;
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
}

void Room::checkDeathAnimations(std::list<std::list<DeathAnimation*>::iterator>&
	death_animations_to_be_erased) {
	for (auto death_animation = death_animations.begin();
		death_animation != death_animations.end(); death_animation++) {
		if ((*death_animation)->checkTime()) {
			death_animations_to_be_erased.push_back(death_animation);
		}
	}
}

bool Room::generateBeam(Person& player, 
	std::set<std::list<Enemy*>::iterator>& enemies_to_be_deleted) {
	int ray_num = 10;
	beam = sf::ConvexShape(ray_num * 2);
	float left_bound = GetBound().getPosition().x;
	float right_bound = left_bound + GetBound().getSize().x;
	float top_bound = GetBound().getPosition().y;
	float bot_bound = top_bound + GetBound().getSize().y;

	auto find_bound = [right_bound, left_bound, top_bound, bot_bound]
	(float x, float y, int x_dir, int y_dir) {
		while ((x >= left_bound && x <= right_bound) && (y >= top_bound && y <= bot_bound)) {
			x += x_dir;
			y += y_dir;
		}
		return sf::Vector2f(x, y);
	};

	sf::Vector2u texture_size_unscaled = player.GetModel().getTexture()->getSize();
	sf::Vector2f texture_size{ texture_size_unscaled.x * player.GetModel().getScale().x,
		texture_size_unscaled.y * player.GetModel().getScale().y };
	//std::cout << "texture size is " << texture_size.x << " " << texture_size.y << std::endl;
	float texture_size_module = sqrt(texture_size.x * texture_size.x +
		texture_size.y * texture_size.y);
	float size_module = (attack_dir_x == attack_dir_y != 0) ? texture_size_module / 1.4 : texture_size_module;
	//10 / 1.4 : 10;


	float x_start_middle = player.GetPosition().x + texture_size.x / 2;// + attack_dir_x * 10;//texture_size.x;
	float y_start_middle = player.GetPosition().y + texture_size.y / 2;// + attack_dir_y * 10;//texture_size.y;*/ 
	sf::Vector2f normal(-attack_dir_y, attack_dir_x);
	sf::Vector2f right_start(x_start_middle + normal.x * size_module,
		y_start_middle + normal.y * size_module);
	sf::Vector2f left_start{ x_start_middle - normal.x * size_module / 2,
		y_start_middle - normal.y * size_module / 2 };
	//std::cout << "left start is " << left_start.x << " " << left_start.y << std::endl;
	sf::Vector2f mid_start(x_start_middle, y_start_middle);

	std::vector<sf::Vector2f> vertices(ray_num);
	for (int i = 0; i < ray_num; i++) {
		sf::Vector2f vertice{ left_start.x + i * normal.x * size_module / ray_num,
			left_start.y + i * normal.y * size_module / ray_num };
		vertices[i] = vertice;
		//std::cout << vertices[i].x << " " << vertices[i].y << std::endl;
	}
	for (int i = ray_num - 1; i >= 0; i--) {
		vertices.push_back(find_bound(vertices[i].x, vertices[i].y, attack_dir_x, attack_dir_y));
		auto test = find_bound(vertices[i].x, vertices[i].y, attack_dir_x, attack_dir_y);
		//std::cout << test.x << " " << test.y << std::endl;
	}
	//sf::Vector2f right
	//beam.setPointCount(ray_num * 2 - 1);
	for (int i = 0; i < ray_num * 2; i++) {
		beam.setPoint(i, vertices[i]);
		//std::cout << i << std::endl;
	}
	beam.setFillColor(sf::Color::Cyan);

	auto vector_multiplication_sign = []
	(sf::Vector2f line_first_point, sf::Vector2f line_second_point,
		sf::Vector2f enemy_pos) {
		float line_x = line_second_point.x - line_first_point.x;
		float line_y = line_second_point.y - line_first_point.y;
		float enemy_line_x = enemy_pos.x - line_first_point.x;
		float enemy_line_y = enemy_pos.y - line_first_point.y;
		return std::signbit(line_x * enemy_line_y - line_y * enemy_line_x);
		//return sf::Vector2f(x, y);
	};

	sf::Vector2f right_bot_point = beam.getPoint(ray_num - 1);
	sf::Vector2f right_top_point = beam.getPoint(ray_num);
	sf::Vector2f left_top_point = beam.getPoint(2 * ray_num - 1);
	sf::Vector2f left_bot_point = beam.getPoint(0);

	for (auto enemy_it = enemies.begin();
		enemy_it != enemies.end(); enemy_it++) {
		sf::Vector2f enemy_pos = (*enemy_it)->GetPosition();
		if (vector_multiplication_sign(right_bot_point, right_top_point, enemy_pos)
			!= vector_multiplication_sign(left_bot_point, left_top_point, enemy_pos)) {
			if ((*enemy_it)->receiveDamage(player.getDamage())) {
				enemies_to_be_deleted.insert(enemy_it);
				death_animations.
					push_back(new DeathAnimation{ (*enemy_it)->GetPosition(),
						death_animation_tick_count });
			}
		}
	}
	//attack_dir_x = 0;
	//attack_dir_y = 0;
	return true;
}

const sf::ConvexShape Room::getBeam() const {
	return beam;
}

bool Room::getBeamFlag() const {
	return beam_flag;
}

