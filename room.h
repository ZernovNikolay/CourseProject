#ifndef ROOM_H_
#define ROOM_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "object.h"
#include "person.h"
#include <memory>
#include <vector>
#include "enemy.h"
#include <chrono>
#include <list>
#include <set>
#include <utility>
enum class Ways{
	Up,
	Right,
	Down,
	Left,
};

class Door{
public:
	Door(const float x, const float y, const int new_way); // установить новую дверь

	void SetOpen();

	void SetClose(int answer);

	bool GetOpen() const;

	int GetQuest() const;

	sf::RectangleShape GetBound() const; // получить ее модельку

	sf::Vector2f GetPosition() const; // получить местоположение двери

	int GetWay() const; // получить направление двери установленное в WAYS

private:
	sf::RectangleShape door;
	int way;
	bool opened;
	int quest;
};

class Wall{
public:
	Wall(float xline, float yline, float x, float y);

	//void SetRotate(float angle);

	sf::Vector2f GetPosition() const;

	sf::Vector2f GetSize() const;

	sf::RectangleShape GetBound() const;

private:
	sf::RectangleShape wall;
};

class Room{
public:
	Room(bool first_room_flag); // создать комнату, SIZE = 400

	~Room(); // очистить все указатели

	void SetLeftDoor(); // установить дверь налево
	void SetRightDoor(); // установить дверь направо
	void SetDownDoor(); // установить дверь вниз
	void SetUpDoor(); // установить дверь наверх

	void SetWall(float xline, float yline, float x, float y);

	void SetLeft(Room* gh); // привязать комнату налево
	void SetRight(Room* gh); // привязать комнату направо
	void SetUp(Room* gh); // привязать комнату вверх
	void SetDown(Room* gh); // привязать комнату вниз

	void SetWeapon(float x, float y, int damage, const std::string& new_name); // создать оружие на точке комнаты
	void SetHeal(float x, float y, int healing, const std::string& new_name);
	void SetKey(float x, float y, int new_key);

	void SetBound(int* color); // создать контур и цвет комнаты

	sf::RectangleShape GetBound(); // получить модель комнаты
	std::vector<Door*> GetDoors(); // получить двери в комнате
	std::vector<Wall*> GetWalls();
	std::vector<std::shared_ptr<Object>> GetObjects(); // получить объекты в комнате

	void GiveItem(Inventory* sd, int gh);
	void SetItem(Inventory* sd, int gh, float x, float y);

	Room* toLeft() const; // получить комнату слева
	Room* toRight() const; // получить комнату справа
	Room* toUp() const; // получить комнату сверху
	Room* toDown() const; // получить комнату снизу
	bool checkTimer(); // проверить, прошло ли timedif с предыдущей проверки (используется для регулировки поведения врагов и снарядов)
	void timeBasedEvents(Person& player);//смещение проджектайлов, врагов, прием атак игрока
const std::list<Enemy*>& getEnemies() const;//вернуть массив врагов
	const std::list<Projectile>& getPlayerProjectiles() const;// вернуть массив снарядов игрока
	const std::list<Projectile>& getEnemyProjectiles() const;//вернуть массив снарядов врага
	std::list<DeathAnimation*>& getDeathAnimations();//вернуть массив анимаций смерти
	int& getBulletX();//возвращаем направление движения пули по горизонтали
	int& getBulletY();//возвращаем направление движения пули по вертикали
	void checkAttack();//в зависимости от нажатия стрелочек на клавиатуре выбирается направление атаки
	bool createProjectile(sf::Vector2f& player_pos, int damage);//создаем снаряд (игрока)
	const sf::ConvexShape getBeam() const;//возвращаем луч (для отрисовки)
	bool getBeamFlag() const;//true если можно рисовать луч
private:

	void moveProjectiles(std::set<std::list<Projectile>::iterator>& projectiles_to_be_deleted,
		std::set<std::list<Enemy*>::iterator>& enemies_to_be_deleted);//перемещаем снаряды (вызывем у них toMove)
	void checkDeathAnimations(std::list<std::list<DeathAnimation*>::iterator>&
		 death_animations_to_be_erased);//проверяем, какие анимации смерти пора удалить
	bool generateBeam(Person& player, 
		std::set<std::list<Enemy*>::iterator>& enemies_to_be_deleted);//создаем луч (заполняем beam точками и устанавливаем флаг beam_flag = true, наносим урон)

	bool beam_flag = false; 
	int beam_generation_time_coef = 50; // time between attacks multiplies on it to find time between beam attacks
	int beam_generation_current_timer = beam_generation_time_coef;
	sf::ConvexShape beam;
	int attack_generating_timedif = 20;
	int attack_cur_timedif = 0;
	int attack_dir_x = 0;
	int attack_dir_y = 0;
	sf::RectangleShape bound;
	std::vector<Door*> door = {};
	std::vector<Wall*> wall = {};
	std::vector<std::shared_ptr<Object>> items = {};
	Room* left = 0;
	Room* right = 0;
	Room* up = 0;
	Room* down = 0;
	std::list <Enemy*> enemies;
	std::list<Projectile> player_projectiles;
	std::list<Projectile> enemy_projectiles;
	std::list<DeathAnimation*> death_animations;
	std::chrono::time_point<std::chrono::steady_clock> current_time
		= std::chrono::steady_clock::now();

	float timedif = 40;
	int death_animation_tick_count = 1000 / timedif;
	
};

void RoomBindLR(Room* lhs, Room* rhs); // связать комнаты левую и правую

void RoomBindUD(Room* up, Room* down); // связать комнаты верхнюю и нижнюю


#endif /* ROOM_H_ */
