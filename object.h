#ifndef OBJECT_H_
#define OBJECT_H_

#include <SFML/Graphics.hpp>

#include <memory>
//const std::string _src_path_ = "../src/textures/";
const std::string _src_path_ = "/home/nikolay/Desktop/Eclipse/smfl/src/textures/";
static sf::Texture texture_weapon;
static sf::Texture texture_heal;
static sf::Texture texture_key;

void LoadTextures();

class Object{
public:

	Object(const std::string& name); //создать объект

	virtual ~Object(); //виртуальный деструктор

	virtual void SetPosition(float x, float y) = 0; //Установить положение предмета

	virtual sf::Vector2f GetPosition() const = 0; //Получить положение предмета

	virtual sf::Sprite GetBound() const = 0; //Получить текстуру

	virtual std::string GetName() const = 0; //Получить имя объекта

	virtual int GetStats() const = 0; //Получить статы предмета

	std::string GetType() const; //Получить тип предмета

	int GetTypeInt() const; //Получить тип предмета

private:
	std::string type;
	int typeInt = -1;
};

class Weapon : public Object{
public:
	Weapon(const std::string& type, float x, float y, int new_damage, const std::string& new_name); // создать оружие в данной точке
	~Weapon() override;

	void SetPosition(float x, float y) override; // переместить оружие

	sf::Vector2f GetPosition() const override; //получить местоположение

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
