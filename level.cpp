#include "level.h"

Level::Level(int countRoom){
	collection.resize(countRoom);
	for(int i = 0; i < countRoom; i++){
		collection[i] = (Room*)calloc(1, sizeof(Room));
	}

	count = countRoom;
	Room* gh = new Room;

	int* colorA = (int*)calloc(3, sizeof(int));
	colorA[0] = 128;
	colorA[1] = 0;
	colorA[2] = 128;
	gh->SetBound(colorA);
	free(colorA);
	collection[0] = gh;
	collection[count - 1] = (Room*)calloc(1, sizeof(Room));
}

Level::~Level(){
	//clear all room
	for(int i = 0; i < count; i++){
		delete collection[i];
	}
}

void Level::NewRoom(){
	Room* down1 = new Room;

	int* colorA = (int*)calloc(3, sizeof(int));
	colorA[0] = 255;
	colorA[1] = 69;
	colorA[2] = 0;

	down1->SetBound(colorA);
	RoomBindUD(collection[0], down1);

	Room* up1 = new Room;

	colorA[0] = 255;
	colorA[1] = 255;
	colorA[2] = 0;

	up1->SetBound(colorA);
	RoomBindUD(up1, collection[0]);

	Room* left1 = new Room;

	colorA[0] = 0;
	colorA[1] = 128;
	colorA[2] = 0;
	left1->SetBound(colorA);

	RoomBindLR(left1, collection[0]);

	Room* right1 = new Room;

	colorA[0] = 0;
	colorA[1] = 0;
	colorA[2] = 255;

	right1->SetBound(colorA);
	RoomBindLR(collection[0], right1);

	Room* hui1 = new Room;

	colorA[0] = 192;
	colorA[1] = 192;
	colorA[2] = 192;

	hui1->SetBound(colorA);
	RoomBindLR(up1, hui1);

	collection[1] = down1;
	collection[2] = up1;
	collection[3] = left1;
	collection[4] = hui1;
	free(colorA);
	collection[count - 1] = right1;

	collection[0]->SetWeapon(350, 300, 50, "Frostmorn");
	collection[0]->SetHeal(200, 250, 100, "Healing Salve");
	collection[0]->SetKey(250, 280, 3);
	collection[0]->GetDoors()[0]->SetClose(3);
}

sf::RectangleShape Level::GetBegin(){
	return collection[0]->GetBound();
}

Room* Level::GetBeginRoom(){
	return collection[0];
}

void RenderLevel(Person& Our_Hero){
	LoadTextures();
	Level QQQ(6);
	QQQ.NewRoom();
	sf::RenderWindow window_H(sf::VideoMode(SIZE_WINDOW, SIZE_WINDOW), "My window");
	Room* current_room = QQQ.GetBeginRoom();

	/*int flag_keyboardA = 0;
	int flag_keyboardS = 0;
	int flag_keyboardD = 0;
	int flag_keyboardW = 0;*/
	int flag_keyboardQ = 0;
	int flag_keyboardE = 0;
	int flag_keyboardF = 0;
	int flag_keyboardR = 0;

	Our_Hero.SetPosition(400.f, 400.f);

	while (window_H.isOpen())
	{
		sf::Event event;
		while (window_H.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window_H.close();
		}
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			/*if(flag_keyboardA == 0){
				//std::cout << "Pressed A " << std::endl;
				flag_keyboardA = 1;
				if(current_room->toLeft() != 0){
					current_room = current_room->toLeft();
				}
			}*/
			if(Our_Hero.GetPosition().x - velocity >= current_room->GetBound().getPosition().x){
				Our_Hero.move(-velocity, 0);
			}
		}else{
			//flag_keyboardA = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			/*if(flag_keyboardD == 0){
				//std::cout << "Pressed D " << std::endl;
				flag_keyboardD = 1;
				if(current_room->toRight() != 0){
					current_room = current_room->toRight();
				}
			}*/
			if(Our_Hero.GetPosition().x + velocity <= current_room->GetBound().getPosition().x
					+ current_room->GetBound().getSize().x - current_room->GetBound().getOutlineThickness()){
				Our_Hero.move(velocity, 0);
			}
		}else{
			//flag_keyboardD = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			/*if(flag_keyboardW == 0){
				//std::cout << "Pressed W " << std::endl;
				flag_keyboardW = 1;
				if(current_room->toUp() != 0){
					current_room = current_room->toUp();
				}
			}*/
			if(Our_Hero.GetPosition().y - velocity >= current_room->GetBound().getPosition().y){
				Our_Hero.move(0, -velocity);
			}
		}else{
			//flag_keyboardW = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			/*if(flag_keyboardS == 0){
				//std::cout << "Pressed S " << std::endl;
				flag_keyboardS = 1;
				if(current_room->toDown() != 0){
					current_room = current_room->toDown();
				}
			}*/
			if(Our_Hero.GetPosition().y + velocity <= current_room->GetBound().getPosition().y
					+ current_room->GetBound().getSize().y - current_room->GetBound().getOutlineThickness()){
				Our_Hero.move(0, velocity);
			}
		}else{
			//flag_keyboardS = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if(flag_keyboardQ == 0){
				//std::cout << "Pressed Q " << std::endl;
				flag_keyboardQ = 1;

				/*for(size_t i = 0; i < current_room->GetDoors().size(); i++){
					std::cout << current_room->GetDoors()[i]->GetWay() << std::endl;
				}*/
				int number_of_door = CheckDoors(current_room, Our_Hero);
				if(number_of_door != 5){

					//std::cout << number_of_door << " Hello" << std::endl;
					if(current_room->GetDoors()[number_of_door]->GetOpen() || CheckClosedDoor(current_room->GetDoors()[number_of_door], Our_Hero.GetInventory())){

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
			flag_keyboardQ = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if(flag_keyboardE == 0){
				int number_of_item = CheckItems(current_room->GetObjects(), Our_Hero);
				if(number_of_item != -1){
					current_room->GiveItem(Our_Hero.GetInventory(), number_of_item);
				}
				flag_keyboardE = 1;
			}
		}else{
			flag_keyboardE = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			if(flag_keyboardF == 0){
				int gh = 0;
				//std::cin >> gh;
				current_room->SetItem(Our_Hero.GetInventory(), gh, Our_Hero.GetPosition().x, Our_Hero.GetPosition().y);
				flag_keyboardF = 1;
			}
		}else{
			flag_keyboardF = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			if(flag_keyboardR == 0){
				sf::RenderWindow window_R(sf::VideoMode(350, 350), "My window");

				float point = 25;

				sf::RectangleShape menu;
				menu.setSize(sf::Vector2f(300, 300));
				menu.setPosition(sf::Vector2f(point, point));
				menu.setOutlineThickness(10);
				menu.setOutlineColor(sf::Color(0, 0, 0));
				menu.setFillColor(sf::Color(255, 255, 255));

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
				}

				flag_keyboardR = 1;
			}
		}else{
			flag_keyboardR = 0;
		}

	}
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
