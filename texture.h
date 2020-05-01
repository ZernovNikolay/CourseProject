#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SFML/Graphics.hpp>
#include <iostream>

const std::vector<std::string> Archer_textures = {"/home/nikolay/Desktop/Eclipse/smfl/src/cricket.png",
												"/home/nikolay/Desktop/Eclipse/smfl/src/smile.png"};

void GetTexture(int gh, std::vector<sf::Texture>& Array_texture, std::vector<sf::Sprite>& Array_sprite); // получить текстуры для массива

#endif /* TEXTURE_H_ */
