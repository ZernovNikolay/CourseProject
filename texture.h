#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SFML/Graphics.hpp>
#include <iostream>

const std::string _src_path_texture = "../src/textures/";
//const std::string _src_path_texture = "/home/nikolay/Desktop/Eclipse/smfl/src/textures/";

const std::vector<std::string> Archer_textures = { _src_path_texture + "archer1.png",
												_src_path_texture + "archer2.png"};

const std::vector<std::string> Warrior_textures = {_src_path_texture + "war1.png",
												_src_path_texture + "war2.png"};


const std::vector<std::string> Mage_textures = {_src_path_texture + "mage1.png",
												_src_path_texture + "mage2.png"};


void GetTexture(int gh, std::vector<sf::Texture>& Array_texture, std::vector<sf::Sprite>& Array_sprite); // получить текстуры для массива

#endif /* TEXTURE_H_ */
