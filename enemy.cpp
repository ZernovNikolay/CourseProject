#include "enemy.h"
#include <iostream>
sf::Vector2f Enemy::GetPosition() const {
	return sf::Vector2f(enemy_model.getPosition().x, enemy_model.getPosition().y);
}

sf::Sprite& Enemy::GetModel() {
	return enemy_model;
}


void Enemy::SetPosition() {
	const float room_middle_coordinate = ROOM_SIZE / 2;
	//std::srand(unsigned(std::time(0)));

	float x = room_middle_coordinate +
		(std::rand() % static_cast<int>(ROOM_SIZE / 5));
	float y = room_middle_coordinate +
		(std::rand() %	static_cast<int>(ROOM_SIZE / 5));

	enemy_model.setPosition(x, y);
	//std::cout << "setpos" << x << " " << y << std::endl;
}

bool Enemy::checkTimer() {
	if (std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - current_time).count() >
			direction_swap_time_milliseconds) {
		current_time = std::chrono::steady_clock::now();
		return true;
	}
	return false;
}

sf::Vector2f Rat::toMove(Person& player) {
	auto player_position = player.GetPosition();
	sf::Vector2f ratPos = GetPosition();
	float rat_x = ratPos.x, rat_y = ratPos.y;
	float player_x = player_position.x, player_y = player_position.y;
	int xsign = (player_x - rat_x) / fabs(player_x - rat_x);
	int ysign = (player_y - rat_y) / fabs(player_y - rat_y);
	int curstep = step;
	if (step_count++ % 10 == 0) {
		//std::srand(unsigned(std::time(0)));
		xsign = std::rand() / 2 == 1 ? -1 : 1;
		ysign = std::rand() / 2 == 1 ? -1 : 1;
		curstep = step * 2;
	}	
	GetModel().setPosition(rat_x + curstep * xsign, rat_y + curstep * ysign);
	sf::Vector2f resPos = GetPosition();
	float xdist = player_position.x - resPos.x;
	float ydist = player_position.y - resPos.y;
	if (sqrt(xdist * xdist + ydist * ydist) <= step) {
		player.receiveDamage(damage);
		//std::cout << "got hit" << std::endl;
	}
	return resPos;
}

void Rat::SetModel() {
	if (!texture.loadFromFile(_src_path_ + "rat.png"))//"/home/nikolay/Desktop/Eclipse/smfl/src/archer.jpg"))
	{
		std::cout << "rat.png not found" << std::endl;
	}
	GetModel() = sf::Sprite(texture);
	GetModel().setScale(0.2, 0.2);
}

Rat::~Rat() {
	std::cout << "rat died" << this->health_point << std::endl;
}


void Rat::toMoveSecondAlgorithm(Person& player, sf::RectangleShape bounds) {
	auto player_position = player.GetPosition();
	sf::Vector2f ratPos = GetPosition();
	float rat_x = ratPos.x, rat_y = ratPos.y;
	float new_rat_x = ratPos.x + direction_vector.x * velocity;
	float new_rat_y = ratPos.y + direction_vector.y * velocity;
	if (new_rat_x <= bounds.getPosition().x || new_rat_x >=
		bounds.getPosition().x + bounds.getSize().x) {
		new_rat_x = ratPos.x;
		direction_vector.x = -direction_vector.x;
	}
	if (new_rat_y <= bounds.getPosition().y || new_rat_y >=
		bounds.getPosition().y + bounds.getSize().y) {
		new_rat_y = ratPos.y;
		direction_vector.y = -direction_vector.y;
	}
	GetModel().setPosition(new_rat_x, 
		new_rat_y);
	if (checkTimer()) {
		setDirVector(player);
	}
}

void Rat::setDirVector(Person& player) {
	float x = 0, y = 0;
	sf::Vector2f ratPos = GetPosition();
	float rat_x = ratPos.x, rat_y = ratPos.y, 
		p_x = player.GetPosition().x, p_y = player.GetPosition().y;
	x = p_x - rat_x;
	y = p_y - rat_y;
	float module = sqrt(x * x + y * y);
	x /= module;
	y /= module;
	if (step_count++ % 10 == 0) {
		if (std::rand() % 2 == 0) {
			float tempx = x;
			x = y;
			y = -tempx;
		}
		else {
			float tempy = y;
			y = x;
			x = -tempy;
		}
	}
	direction_vector.x = x;
	direction_vector.y = y;
	if (module <= velocity * 100) {
		player.receiveDamage(damage);
	}
}

void Projectile::toMove() {
	float cur_x = projectile.getPosition().x, 
		cur_y = projectile.getPosition().y;
	projectile.setPosition(cur_x + x_sign * step, cur_y + y_sign * step);
}

Projectile::Projectile(sf::Vector2f curpos, int damage, int x_sign, int y_sign) {
	projectile.setPosition(curpos);
	this->damage = damage;
	this->x_sign = x_sign;
	this->y_sign = y_sign;
}

sf::Vector2f Projectile::getPosition() {
	return projectile.getPosition();
}

bool Projectile::checkCollision(sf::Vector2f object_pos) {
	auto cur_pos = getPosition();
	float xdif = cur_pos.x - object_pos.x,
		ydif = cur_pos.y - object_pos.y;
	if (sqrt(xdif * xdif + ydif * ydif) < 1.4 * step + 3)
		return true;
	return false;
}

sf::CircleShape Projectile::getBullet() {
	return projectile;
}

bool Enemy::receiveDamage(int damage) {
	if (std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - last_time_being_hit).count() >
		direction_swap_time_milliseconds) {
		last_time_being_hit = std::chrono::steady_clock::now();
		if ((health_point -= damage) < 0)
			return true;
	}
	return false;
}

int Projectile::getDamage() {
	return damage;
}
sf::CircleShape Projectile::getCircleShape() const{
	return projectile;
}

Projectile::~Projectile() {
	//std::cout << "Deleted" << std::endl;
}


const sf::Sprite& DeathAnimation::getModel() const {
	return sprite;
}
void DeathAnimation::setModel() {
	if (!texture.loadFromFile(_src_path_ + "Ghost.png"))//"/home/nikolay/Desktop/Eclipse/smfl/src/archer.jpg"))
	{
		std::cout << "Ghost.png not found" << std::endl;
	}
	sprite = sf::Sprite(texture);
	sprite.setScale(0.2, 0.2);
}

void DeathAnimation::setPosition(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

DeathAnimation::DeathAnimation(sf::Vector2f pos, int max_tick_count) {
	setModel();
	setPosition(pos);
	this->max_tick_count = max_tick_count;
	/*std::cout << "DeathAnimation created " << getModel().getPosition().x <<
		" " << getModel().getPosition().y << " " << max_tick_count <<std::endl;*/
}

bool DeathAnimation::checkTime() {
	cur_tick_count++;
	if (cur_tick_count >= max_tick_count)
		return true;
	return false;
}

bool operator< (const std::list<Projectile>::iterator& lhs, 
	const std::list<Projectile>::iterator& rhs) {
	//return lhs.getCircleShape().getPosition() < rhs.getCircleShape().getPosition();
	sf::Vector2f lhs_pos = lhs->getCircleShape().getPosition();
	sf::Vector2f rhs_pos = rhs->getCircleShape().getPosition();
	float lhsx = lhs_pos.x, lhsy = lhs_pos.y;
	float rhsx = rhs_pos.x, rhsy = rhs_pos.y;
	if (lhsx < rhsx)
		return true;
	if (lhsy < rhsy)
		return true;
	return false;
}


bool operator< (const std::list<Enemy*>::iterator& lhs,
	const std::list<Enemy*>::iterator& rhs) {
	auto lhs_pos = (*lhs)->GetPosition();
	auto rhs_pos = (*rhs)->GetPosition();
	float lhsx = lhs_pos.x, lhsy = lhs_pos.y;
	float rhsx = rhs_pos.x, rhsy = rhs_pos.y;
	if (lhsx < rhsx)
		return true;
	if (lhsy < rhsy)
		return true;
	return false;
}