//#include <SFML/Graphics.hpp>
//#include <iostream>
#include <cmath>
#include <stack>
#include <set>
#include <utility>
#include <fstream>
#include <list>
#include <cstdlib>
#include "menu.h"
#include "level.h"

/* Написать общий класс для всех объектов
 * Функция для взятия этих объектов
 * Написать инвентарь
 * Найти кучу текстур
 * встроить инвентарь в человека и исправить в level.cpp проверку итемов
 * объединить проверку дверей и объектов
 * в перетаскивании итема сделать нормальный выбор слота
 */

const float Pi = 3.14159f;
const int NUMBER = 1000;
const int CountRoom = 7;

class Vector{
public:
	Vector(float new_x, float new_y){
		x = new_x;
		y = new_y;
	}

	Vector(){}

	Vector norm() const{
		float d, f;
		d = x/sqrt(x*x + y*y);
		f = y/sqrt(x*x + y*y);
		Vector gh(d, f);
		return gh;
	}

	float GetX(){
		return x;
	}

	float GetY(){
		return y;
	}

private:
	float x;
	float y;
};

//создаем структуру, в которую передаем текстуру и координаты - направление движения текстуры
struct moving_texture {
	sf::Sprite ball;
	float x;
	float y;
	bool exist = true;
};

struct bullet{
	moving_texture object;
	bool exist = true;
	int number;
};

bool operator< (const bullet& lhs, const bullet& rhs){
	return lhs.number < rhs.number;
}

//функция движения текстуры - ссылка для того чтобы изменить объект т.к. он двигается
void move(sf::Sprite& circle, float x, float y) {
	circle.move(-x, -y);
	//circle.move(0, y);
}

enum class ClassType{
	Warrior,
	Archer,
	Mage,
	Rogue,
};

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

int main()
{
	std::string name;
	std::cin >> name;
	Person Our_Hero(name);
	int gh = StartMenu(Our_Hero);
	CastomizeMenu(Our_Hero, gh);
	RenderLevel(Our_Hero);

	return 0;
}
