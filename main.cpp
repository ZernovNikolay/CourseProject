//#include <SFML/Graphics.hpp>
//#include <iostream>
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

enum class ClassType{
	Warrior,
	Archer,
	Mage,
	Rogue,
};

int main()
{
	std::cout << "Please, enter your name" << std::endl;
	std::string name;
	std::cin >> name;
	Person Our_Hero(name);
	int gh = StartMenu(Our_Hero);
	CastomizeMenu(Our_Hero, gh);
	RenderLevel(Our_Hero);

	return 0;
}
