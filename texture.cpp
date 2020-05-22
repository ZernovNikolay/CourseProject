#include "texture.h"

void GetTexture(int gh, std::vector<sf::Texture>& Array_texture, std::vector<sf::Sprite>& Array_sprite){
	switch (gh){
	case 0:{
		for(size_t i = 0; i < Archer_textures.size(); i++){
			Array_texture[i].loadFromFile(Archer_textures[i]);
			sf::Sprite hero(Array_texture[i]);
			hero.setScale(0.5f, 0.5f);
			hero.setPosition(200, 100);
			Array_sprite.push_back(hero);
		}
		break;
	}
	case 1:
		for(size_t i = 0; i < Warrior_textures.size(); i++){
			Array_texture[i].loadFromFile(Warrior_textures[i]);
			sf::Sprite hero(Array_texture[i]);
			hero.setScale(0.5f, 0.5f);
			hero.setPosition(200, 100);
			Array_sprite.push_back(hero);
		}
		break;
	case 2:
		for(size_t i = 0; i < Mage_textures.size(); i++){
			Array_texture[i].loadFromFile(Mage_textures[i]);
			sf::Sprite hero(Array_texture[i]);
			hero.setScale(0.5f, 0.5f);
			hero.setPosition(200, 100);
			Array_sprite.push_back(hero);
		}
		break;
	}
	//std::cout << "NEW CHAPTER" << std::endl;
}
