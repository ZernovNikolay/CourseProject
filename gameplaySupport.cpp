#include "gameplaySupport.h"

int CheckItems(const std::vector<std::shared_ptr<Object>>& gh, const Person& Our_Hero){
	for(size_t i = 0; i < gh.size(); i++){
		if(CheckItem(gh[i], Our_Hero)){
			return i;
		}
	}
	return -1;
}

bool CheckItem(const std::shared_ptr<Object>& item, const Person& Our_Hero){
	if(Our_Hero.GetPosition().y < item -> GetPosition().y + 15 &&
			Our_Hero.GetPosition().x < item-> GetPosition().x + 15 &&
			Our_Hero.GetPosition().x > item-> GetPosition().x - 5 &&
			Our_Hero.GetPosition().y > item-> GetPosition().y - 5){
		return true;
	}
	return false;
}

int CheckDoors(Room* current_room, const Person& Our_Hero){
	for(size_t i = 0; i < current_room->GetDoors().size(); i++){
		if(CheckDoor(current_room->GetDoors()[i], Our_Hero)){
			return i;
		}
	}
	return 5;
}

bool CheckDoor(Door* door, const Person& Our_Hero){
	if(Our_Hero.GetPosition().y < door-> GetPosition().y + 15 &&
			Our_Hero.GetPosition().x < door-> GetPosition().x + 15 &&
			Our_Hero.GetPosition().x > door-> GetPosition().x - 15 &&
			Our_Hero.GetPosition().y > door-> GetPosition().y - 15){
		return true;
	}
	return false;
}

void CheckGiveItems(bool& flag_keyboardE, Person& Our_Hero, Room*& current_room){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		if(flag_keyboardE){
			int number_of_item = CheckItems(current_room->GetObjects(), Our_Hero);
			if(number_of_item != -1){
				current_room->GiveItem(Our_Hero.GetInventory(), number_of_item);
			}
			flag_keyboardE = false;
		}
	}else{
		flag_keyboardE = true;
	}
}

bool CheckClosedDoor(Door* door, Inventory* sd){
	if(!door->GetOpen()){
		for(size_t i = 0; i < sd->GetSize(); i++){
			if(sd->GetItem(i)->GetType() == "Key"){
				if(sd->GetItem(i)->GetStats() == door->GetQuest()){
					door->SetOpen();
					sd->EraseItem(i);
					return true;
				}
			}
		}
		return false;
	}else{
		return true;
	}
}

void CheckButtonLeftOnInventory(bool& flagLeft, Person& Our_Hero, const sf::Vector2i& pixelPos){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		if(flagLeft){
			if(pixelPos.x < 330){
				int numberG = (pixelPos.x - 25)/50;
				int numberV = (pixelPos.y - 25)/50;
				int count = numberG + 6 * numberV;
				Our_Hero.UseItem(count);
				//current_room->SetItem(Our_Hero.GetInventory(), count, Our_Hero.GetPosition().x, Our_Hero.GetPosition().y);
				//std::cout << count << " " << pixelPos.x << std::endl;
			}
		}
		flagLeft = false;
	}else{
		flagLeft = true;
	}
}

void CheckButtonRightOnInventory(bool& flagRight, Person& Our_Hero, const sf::Vector2i& pixelPos, Room*& current_room){
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				if(flagRight){
					if(pixelPos.x < 330){
						int flagLI = 0;
						int numberG = (pixelPos.x - 25)/50;
						int numberV = (pixelPos.y - 25)/50;
						int count = numberG + 6 * numberV;
						//current_room->SetItem(Our_Hero.GetInventory(), count, Our_Hero.GetPosition().x, Our_Hero.GetPosition().y);
						//std::cout << count << " " << pixelPos.x << std::endl;
						sf::RenderWindow window_Choice(sf::VideoMode(120, 100), "My window");
						window_Choice.setPosition(sf::Vector2i(500, 500));

						std::vector<sf::RectangleShape> choiceItem;
						choiceItem.resize(3);

						const std::string _src_path_texture = "../src/textures/";//"/home/nikolay/Desktop/Eclipse/smfl/src/textures/";

						const std::vector<std::string> Array_texture_menu = {_src_path_texture + "use.jpg",
																		_src_path_texture + "drop.jpg",
																		_src_path_texture + "inform.jpg"};

						std::vector<sf::Texture> Array_sprite_menu;
						Array_sprite_menu.resize(Array_texture_menu.size());

						for(size_t j = 0; j < 3; j++){
							Array_sprite_menu[j].loadFromFile(Array_texture_menu[j]);
							choiceItem[j].setSize(sf::Vector2f(80, 15));
							choiceItem[j].setPosition(sf::Vector2f(20, 15 + j*28));
							choiceItem[j].setTexture(&Array_sprite_menu[j]);
							/*choiceItem[j].setOutlineThickness(3);
							choiceItem[j].setOutlineColor(sf::Color(0, 0, 0));
							choiceItem[j].setFillColor(sf::Color(255, 255, 255));*/
						}

						/*std::vector<MenuItem> choice;
						choice.resize(3);

						for(size_t j = 0; j < 3; j++){
							choice[j].setBound(80, 15, 20, 15+j);
							choice[j].setOutlineThickness(3);
							choice[j].setOutlineColor(sf::Color(0, 0, 0));
							choiceItem[j].setFillColor(sf::Color(255, 255, 255));
						}*/

						while (window_Choice.isOpen())
						{
							sf::Event event;
							while (window_Choice.pollEvent(event))
							{
								if (event.type == sf::Event::Closed)
									window_Choice.close();
							}

							window_Choice.clear(sf::Color::White);
							for(size_t j = 0; j < 3; j++){
								window_Choice.draw(choiceItem[j]);
							}
							window_Choice.display();

							sf::Vector2i pixelPosI = sf::Mouse::getPosition(window_Choice);

							if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
								if(flagLI == 0){
									int command = 0;
									for(size_t gh = 0; gh < 3; gh++){
										if(pixelPosI.x > choiceItem[gh].getPosition().x &&
												pixelPosI.x < choiceItem[gh].getPosition().x + choiceItem[gh].getSize().x &&
												pixelPosI.y > choiceItem[gh].getPosition().y &&
												pixelPosI.y < choiceItem[gh].getPosition().y + choiceItem[gh].getSize().y){
											command = gh;
											break;
										}
									}
									//std::cout << count << " of thing" << std::endl;
									switch(command){
									case 0:
										Our_Hero.UseItem(count);
										//std::cout << count << "USE" << std::endl;
										window_Choice.close();
										break;
									case 1:
										current_room->SetItem(Our_Hero.GetInventory(), count, Our_Hero.GetPosition().x, Our_Hero.GetPosition().y);
										window_Choice.close();
										break;
									case 2:
										std::cout << "More Information" << std::endl;
										window_Choice.close();
										break;
									}
								}
								flagLI = 1;
							}else{
								flagLI = 0;
							}
						}
					}
				}
				flagRight = false;
			}else{
				flagRight = true;
			}
}
