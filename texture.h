#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SFML/Graphics.hpp>
#include <iostream>

const std::string _src_path_texture = "../src/textures/";

const std::vector<std::string> Archer_textures = { _src_path_texture + "cricket.png",
												_src_path_texture + "smile.png"};

const std::vector<std::string> Warrior_textures = {};


const std::vector<std::string> Rogue_textures = {};


void GetTexture(int gh, std::vector<sf::Texture>& Array_texture, std::vector<sf::Sprite>& Array_sprite); // получить текстуры для массива

#endif /* TEXTURE_H_ */
