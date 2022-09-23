#include <SFML/Graphics.hpp>

#pragma once
class Background
{
public:
	void init(std::string textureName);
	sf::Sprite getSprite();
private:
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
};