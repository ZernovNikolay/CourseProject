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

sf::Vector2f Rat::move(Person& player) {
	auto player_position = player.GetPosition();
	sf::Vector2f roguePos = GetPosition();
	float rogue_x = roguePos.x, rogue_y = roguePos.y;
	float player_x = player_position.x, player_y = player_position.y;
	int xsign = (player_x - rogue_x) / fabs(player_x - rogue_x);
	int ysign = (player_y - rogue_y) / fabs(player_y - rogue_y);
	if (step_count++ % 3 == 0) {
		//std::srand(unsigned(std::time(0)));
		xsign = std::rand() / 2 == 1 ? -1 : 1;
		ysign = std::rand() / 2 == 1 ? -1 : 1;
	}	
	GetModel().setPosition(rogue_x + step * xsign, rogue_y + step * ysign);
	sf::Vector2f resPos = GetPosition();
	float xdist = player_position.x - resPos.x;
	float ydist = player_position.y - resPos.y;
	if (sqrt(xdist * xdist + ydist * ydist) <= step) {
		player.receiveDamage(damage);
		std::cout << "got hit" << std::endl;
	}
	return resPos;
}

void Rat::SetModel() {
	//sf::Texture texture;
	if (!texture.loadFromFile(_src_path_ + "rat.png"))//"/home/nikolay/Desktop/Eclipse/smfl/src/archer.jpg"))
	{
		std::cout << "rat.png not found" << std::endl;
	}
	GetModel() = sf::Sprite(texture);
	GetModel().setScale(0.2, 0.2);
	//hero.setScale(0.05f, 0.05f);
}
