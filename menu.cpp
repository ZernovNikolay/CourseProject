#include "menu.h"
#include <vector>
//#include <filesystem>

MenuItem::MenuItem(float length, float high, int* color, float x, float y, const sf::Texture& texture){
	item.setSize(sf::Vector2f(length, high));
	item.setPosition(sf::Vector2f(x, y));
	item.setTexture(&texture);
}

MenuItem::MenuItem(){}

void MenuItem::setBound(float length, float high, int* color, float x, float y){
	item.setSize(sf::Vector2f(length, high));
	item.setPosition(sf::Vector2f(x, y));
}

void MenuItem::DrawItem(sf::RenderWindow& window){
	window.draw(item);
}

std::tuple<float, float, float, float> MenuItem::getBound(){
	return {item.getPosition().x, item.getPosition().x + item.getSize().x,
		item.getPosition().y, item.getPosition().y + item.getSize().y};
}

bool MenuItem::Check(float a, float b){
	float x1, x2, y1, y2;
	std::tie(x1, x2, y1, y2) = getBound();
	return ((a < x2) && (a > x1) && (b < y2) && (b > y1));
}

int StartMenu(Person& Our_Hero){
	int flag = 0;
	sf::RenderWindow window_start(sf::VideoMode(SIZE, SIZE), "My window");

	int* colorW = (int*)calloc(3, sizeof(int));
	colorW[0] = 255;
	colorW[1] = 255;
	colorW[2] = 255;

	int* colorA = (int*)calloc(3, sizeof(int));
	colorA[0] = 255;
	colorA[1] = 255;
	colorA[2] = 255;

	int* colorR = (int*)calloc(3, sizeof(int));
	colorR[0] = 255;
	colorR[1] = 255;
	colorR[2] = 255;

	std::vector<MenuItem> choice;

	sf::Texture texture;
	//std::string arch_path = "src/textures/archer.jpg";
	//std::string CurrentPath(std::filesystem::current_path().generic_string());
	//std::cout << CurrentPath << std::endl;
	if (!texture.loadFromFile(_src_path_ + "archer.jpg"))//"/home/nikolay/Desktop/Eclipse/smfl/src/archer.jpg"))
	{
	   std::cout << "Archer.png not found" << std::endl;
	}

	MenuItem rectangleW(500, 50, colorW, 150, 200, texture);
	choice.push_back(rectangleW);

	sf::Texture texture2;

	if (!texture2.loadFromFile(_src_path_ + "warrior.jpg"))
	{
	   std::cout << "Warrior.jpg not found" << std::endl;
	}

	MenuItem rectangleA(500, 50, colorA, 150, 300, texture2);
	choice.push_back(rectangleA);

	sf::Texture texture3;

	if (!texture3.loadFromFile(_src_path_ + "mage.jpg"))
	{
	   std::cout << "Mage.jpg not found" << std::endl;
	}

	MenuItem rectangleR(500, 50, colorR, 150, 400, texture3);
	choice.push_back(rectangleR);

	free(colorW);
	free(colorA);
	free(colorR);

	while (window_start.isOpen())
	{
		sf::Event event;
		while (window_start.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window_start.close();
		}
		window_start.clear(sf::Color::White);
		for(size_t i = 0; i < choice.size(); i++){
			choice[i].DrawItem(window_start);
		}
		window_start.display();

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window_start);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if(flag == 0){
				int flagChoice = 0;
				for(size_t i = 0; i < choice.size(); i++){
					if(choice[i].Check(pixelPos.x, pixelPos.y)){
						flagChoice = flagChoice + i;
						break;
					}
				}

				switch(flagChoice) {
					case 1:
						Our_Hero.SetCharacter("Warrior");
						return 1;
					case 0:
						{
						Our_Hero.SetCharacter("Archer");
						return 0;
						}
					case 2:
						Our_Hero.SetCharacter("Rogue");
						return 2;
				}
			}
			flag = 1;
		}else{
			flag = 0;
		}
	}
	return -1;
}

void CastomizeMenu(Person& Our_Hero, int class_Our_Hero){
	sf::RenderWindow window_castomize(sf::VideoMode(SIZE, SIZE), "My window");
	static std::vector<sf::Texture> Array_texture; //не весь а только нужный
	Array_texture.resize(Archer_textures.size());

	std::vector<sf::Sprite> Array_sprite;

	GetTexture(class_Our_Hero, Array_texture, Array_sprite);

	int* colorW = (int*)calloc(3, sizeof(int));
	colorW[0] = 255;
	colorW[1] = 255;
	colorW[2] = 255;

	sf::Texture texture;

	if (!texture.loadFromFile(_src_path_ + "archer.jpg"))
	{
	   std::cout << "Pizdec" << std::endl;
	}

	MenuItem rectangleOK(500, 50, colorW, 150, 400, texture);

	free(colorW);

	int flag_keyboardA = 0;
	int flag_keyboardD = 0;
	int flag = 0;
	int flagM = 0;
	while (window_castomize.isOpen()){
		sf::Event event;
		while (window_castomize.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_castomize.close();
		}
		window_castomize.clear(sf::Color::Green);
		window_castomize.draw(Array_sprite[flag]);
		rectangleOK.DrawItem(window_castomize);
		window_castomize.display();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			if(flag_keyboardA == 0){
				flag = (flag+1)%2;
				//std::cout << "Pressed A " << flag << std::endl;
				flag_keyboardA = 1;
			}
		}else{
			flag_keyboardA = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if(flag_keyboardD == 0){
				flag = (flag+1)%2;
				//std::cout << "Pressed D " << flag << std::endl;
				flag_keyboardD = 1;
			}
		}else{
			flag_keyboardD = 0;
		}

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window_castomize);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if(flagM == 0){
				if(rectangleOK.Check(pixelPos.x, pixelPos.y)){
					Array_sprite[flag].setScale(0.03f, 0.03f);
					Our_Hero.SetModel(Array_sprite[flag]);
					Our_Hero.SetTexture(Archer_textures[flag]);//не арчер а универсальный
					return;
				}
			}
			flagM = 1;
		}else{
			flagM = 0;
		}
	}
}
