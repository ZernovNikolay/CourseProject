#ifndef OBJECT_H_
#define OBJECT_H_

#include <SFML/Graphics.hpp>

#include <memory>

class Object{
public:

	Object(const std::string& name, float x, float y);

	virtual ~Object();

	virtual void SetPosition(float x, float y);

	virtual sf::Vector2f GetPosition() const;

	virtual sf::CircleShape GetBound() const;

	std::string GetType() const;

private:
	sf::CircleShape bound;
	std::string type;
};

class Weapon : public Object{
public:
	Weapon(const std::string& type, float x, float y); // создать оружие в данной точке

	~Weapon() override;

	void SetPosition(float x, float y) override; // переместить оружие

	sf::Vector2f GetPosition() const override;

	sf::CircleShape GetBound() const override; // получить модельку оружия

private:
	//sf::CircleShape bound;
};

#endif /* OBJECT_H_ */
