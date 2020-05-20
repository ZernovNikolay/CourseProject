#include "gameplay.h"


void CheckMoveHero(Person& Our_Hero, Room* current_room){
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				if(Our_Hero.GetPosition().x - velocity >= current_room->GetBound().getPosition().x){
					Our_Hero.move(-velocity, 0);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				if(Our_Hero.GetPosition().x + velocity <= current_room->GetBound().getPosition().x
						+ current_room->GetBound().getSize().x - current_room->GetBound().getOutlineThickness()){
					Our_Hero.move(velocity, 0);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				if(Our_Hero.GetPosition().y - velocity >= current_room->GetBound().getPosition().y){
					Our_Hero.move(0, -velocity);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				if(Our_Hero.GetPosition().y + velocity <= current_room->GetBound().getPosition().y
						+ current_room->GetBound().getSize().y - current_room->GetBound().getOutlineThickness()){
					Our_Hero.move(0, velocity);
				}
			}
}

void CheckPassDoors(bool& flag_keyboardQ, Person& Our_Hero, Room*& current_room, sf::RenderWindow& window_H){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if(flag_keyboardQ){
			//std::cout << current_room << std::endl;
			//std::cout << current_room->toLeft() << std::endl;
			//std::cout << "Pressed Q " << std::endl;
			flag_keyboardQ = false;

			/*for(size_t i = 0; i < current_room->GetDoors().size(); i++){
				std::cout << current_room->GetDoors()[i]->GetWay() << std::endl;
			}*/
			int number_of_door = CheckDoors(current_room, Our_Hero);
			if(number_of_door != 5){

				//std::cout << number_of_door << " Hello" << std::endl;
				if(current_room->GetDoors()[number_of_door]->GetOpen() ||
						CheckClosedDoor(current_room->GetDoors()[number_of_door], Our_Hero.GetInventory())){

					window_H.clear(sf::Color::White);
					window_H.draw(current_room->GetBound());
					for(size_t i = 0; i < current_room->GetDoors().size(); i++){
						window_H.draw(current_room->GetDoors()[i]->GetBound());
					}
					for(size_t i = 0; i < current_room->GetObjects().size(); i++){
						window_H.draw(current_room->GetObjects()[i]->GetBound());
					}
					window_H.draw(Our_Hero.GetModel());
					window_H.display();

					switch (current_room->GetDoors()[number_of_door]->GetWay()){

					case 1:
						Our_Hero.SetPosition(current_room->GetDoors()[number_of_door]->GetPosition().x,
								current_room->GetDoors()[number_of_door]->GetPosition().y + current_room->GetBound().getSize().y);
						current_room = current_room->toUp();
						//std::cout << "Here1" << std::endl;
						break;
					case 2:
						Our_Hero.SetPosition(current_room->GetDoors()[number_of_door]->GetPosition().x - current_room->GetBound().getSize().x,
								current_room->GetDoors()[number_of_door]->GetPosition().y);
						current_room = current_room->toRight();
						//std::cout << "Here2" << std::endl;
						break;
					case 3:
						Our_Hero.SetPosition(current_room->GetDoors()[number_of_door]->GetPosition().x,
								current_room->GetDoors()[number_of_door]->GetPosition().y - current_room->GetBound().getSize().y);
						current_room = current_room->toDown();
						//std::cout << "Here3" << std::endl;
						break;
					case 4:
						Our_Hero.SetPosition(current_room->GetDoors()[number_of_door]->GetPosition().x + current_room->GetBound().getSize().x,
								current_room->GetDoors()[number_of_door]->GetPosition().y);
						current_room = current_room->toLeft();
						//std::cout << "Here4" << std::endl;
						break;
					case 0:
						break;
					}
				}
			}
		}
	}else{
		flag_keyboardQ = true;
	}
}

void WorkWithInventory(bool& flag_keyboardR, Person& Our_Hero, Room*& current_room){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if(flag_keyboardR){
			ShowInventory(Our_Hero, current_room);
			flag_keyboardR = false;
		}
	}else{
		flag_keyboardR = true;
	}
}

void ShowInventory(Person& Our_Hero, Room* current_room){
	sf::RenderWindow window_R(sf::VideoMode(350, 350), "My window");

	float point = 25;

	sf::RectangleShape menu;
	menu.setSize(sf::Vector2f(300, 300));
	menu.setPosition(sf::Vector2f(point, point));
	menu.setOutlineThickness(10);
	menu.setOutlineColor(sf::Color(0, 0, 0));
	menu.setFillColor(sf::Color(255, 255, 255));

	std::vector<sf::RectangleShape> lineV;
	lineV.resize(5);

	std::vector<sf::RectangleShape> lineG;
	lineG.resize(5);

	for(size_t i = 0; i < lineV.size(); i++){
		lineV[i].setSize(sf::Vector2f(5.f, 300.f));
		lineV[i].setFillColor(sf::Color(0, 0, 0));
		lineV[i].setPosition(75.f + i*50, 25.f);
	}

	for(size_t i = 0; i < lineG.size(); i++){
		lineG[i].setSize(sf::Vector2f(300.f, 5.f));
		lineG[i].setFillColor(sf::Color(0, 0, 0));
		lineG[i].setPosition(25.f, 75.f + i*50);
	}

	bool flagLeft = true;
	bool flagRight = false;

	while (window_R.isOpen())
	{
		sf::Event event;
		while (window_R.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_R.close();
		}
		window_R.clear(sf::Color::White);
		window_R.draw(menu);
		for(size_t i = 0; i < lineV.size(); i++){
			window_R.draw(lineV[i]);
			window_R.draw(lineG[i]);
		}
		size_t gh = Our_Hero.GetInventory()->GetSize();
		for(size_t i = 0; i < gh; i++){
			Our_Hero.GetInventory()->GetItem(i)->SetPosition(point + i * 60, point + i/5 * 60);
			window_R.draw(Our_Hero.GetInventory()->GetItem(i)->GetBound());
		}
		window_R.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		{
			window_R.close();
		}

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window_R);

		CheckButtonLeftOnInventory(flagLeft, Our_Hero, pixelPos);

		CheckButtonRightOnInventory(flagRight, Our_Hero, pixelPos, current_room);
	}
}
