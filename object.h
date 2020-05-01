#ifndef OBJECT_H_
#define OBJECT_H_

#include <SFML/Graphics.hpp>

/*class Object{
public:
	Obj

	virtual void SetPosition(float x, float y);
};*/

class Weapon{
public:
	Weapon(float x, float y); // создать оружие в данной точке

	void SetPosition(float x, float y); // переместить оружие

	sf::CircleShape GetBound() const; // получить модельку оружия

private:
	sf::CircleShape bound;
};

#endif /* OBJECT_H_ */
