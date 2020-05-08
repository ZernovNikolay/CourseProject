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
	bool flag_keyboardQ = true;
	bool flag_keyboardE = true;
	bool flag_keyboardR = true;

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

		CheckMoveHero(Our_Hero,current_room);
		CheckPassDoors(flag_keyboardQ, Our_Hero, current_room, window_H);
		CheckGiveItems(flag_keyboardE, Our_Hero, current_room);
		WorkWithInventory(flag_keyboardR, Our_Hero, current_room);
	}
}
