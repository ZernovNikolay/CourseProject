#ifndef OBJECT_H_
#define OBJECT_H_

#include <SFML/Graphics.hpp>

#include <memory>

static sf::Texture texture_weapon;
static sf::Texture texture_heal;
static sf::Texture texture_key;

void LoadTextures();

class Object{
public:

	Object(const std::string& name);

	virtual ~Object();

	virtual void SetPosition(float x, float y) = 0;

	virtual sf::Vector2f GetPosition() const = 0;

	virtual sf::Sprite GetBound() const = 0;

	virtual std::string GetName() const = 0;

	virtual int GetStats() const = 0;

	std::string GetType() const;

private:
	std::string type;
};

class Weapon : public Object{
public:
	Weapon(const std::string& type, float x, float y, int new_damage, const std::string& new_name); // создать оружие в данной точке
	~Weapon() override;

	void SetPosition(float x, float y) override; // переместить оружие

	sf::Vector2f GetPosition() const override;

	sf::Sprite GetBound() const override; // получить модельку оружия

	std::string GetName() const override;

	int GetStats() const override;

private:
	sf::Sprite bound;
	std::string name;
	int damage;
};

class Heal : public Object{
public:
	Heal(const std::string& type, float x, float y, int new_healing, const std::string& new_name);
	~Heal();

	void SetPosition(float x, float y) override; // переместить оружие

	sf::Vector2f GetPosition() const override;

	sf::Sprite GetBound() const override; // получить модельку оружия

	std::string GetName() const override;

	int GetStats() const override;

private:
	sf::Sprite bound;
	std::string name;
	int healing;
};

class Key : public Object{
public:
	Key(const std::string& type, float x, float y, int new_healing);//red
	~Key();

	void SetPosition(float x, float y) override; // переместить оружие

	sf::Vector2f GetPosition() const override;

	sf::Sprite GetBound() const override; // получить модельку оружия

	std::string GetName() const override;

	int GetStats() const override;

private:
	sf::Sprite bound;
	int key;
};

#endif /* OBJECT_H_ */
