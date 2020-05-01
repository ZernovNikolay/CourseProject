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
	gh->SetBound(200, 200, colorA, 200, 200);
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

	down1->SetBound(200, 200, colorA, 200, 200);
	RoomBindUD(collection[0], down1);

	Room* up1 = new Room;

	colorA[0] = 255;
	colorA[1] = 255;
	colorA[2] = 0;

	up1->SetBound(200, 200, colorA, 200, 200);
	RoomBindUD(up1, collection[0]);

	Room* left1 = new Room;

	colorA[0] = 0;
	colorA[1] = 128;
	colorA[2] = 0;
	left1->SetBound(200, 200, colorA, 200, 200);

	RoomBindLR(left1, collection[0]);

	Room* right1 = new Room;

	colorA[0] = 0;
	colorA[1] = 0;
	colorA[2] = 255;

	right1->SetBound(200, 200, colorA, 200, 200);
	RoomBindLR(collection[0], right1);

	Room* hui1 = new Room;

	colorA[0] = 192;
	colorA[1] = 192;
	colorA[2] = 192;

	hui1->SetBound(200, 200, colorA, 200, 200);
	RoomBindLR(up1, hui1);

	collection[1] = down1;
	collection[2] = up1;
	collection[3] = left1;
	collection[4] = hui1;
	free(colorA);
	collection[count - 1] = right1;

	collection[0]->SetWeapon(350, 300);
}

sf::RectangleShape Level::GetBegin(){
	return collection[0]->GetBound();
}

Room* Level::GetBeginRoom(){
	return collection[0];
}

void RenderLevel(Person& Our_Hero){
	Level QQQ(6);
	Inventory sd;
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

	Our_Hero.SetPosition(300.f, 300.f);

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
			Our_Hero.move(-0.1, 0);
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
			Our_Hero.move(0.1, 0);
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
			Our_Hero.move(0, -0.1);
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
			Our_Hero.move(0, 0.1);
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
		}else{
			flag_keyboardQ = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			if(flag_keyboardE == 0){
				int number_of_item = CheckItems(current_room->GetObjects(), Our_Hero);
				if(number_of_item != -1){
					current_room->GiveItem(sd, number_of_item);
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
				current_room->SetItem(sd, gh, Our_Hero.GetPosition().x, Our_Hero.GetPosition().y);
				flag_keyboardF = 1;
			}
		}else{
			flag_keyboardF = 0;
		}

	}
}

int CheckDoors(Room* current_room, const Person& Our_Hero){
	for(size_t i = 0; i < current_room->GetDoors().size(); i++){
		if(CheckDoor(current_room->GetDoors()[i], Our_Hero)){
			return i;
		}
	}
	//std::cout << "WRITE THIS FUNCTION!" << std::endl;
	return 5;
}

bool CheckDoor(Door* door, const Person& Our_Hero){
	if(Our_Hero.GetPosition().y < door-> GetPosition().y + 15 &&
			Our_Hero.GetPosition().x < door-> GetPosition().x + 15 &&
			Our_Hero.GetPosition().x > door-> GetPosition().x - 5 &&
			Our_Hero.GetPosition().y > door-> GetPosition().y - 5){
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
