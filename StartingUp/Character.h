#include <SFML/Graphics.hpp>

#pragma once
class Character
{
public:
	Character();
	~Character();

	//Sets the basic initialization for a character
	void init(std::string texturePath, sf::Vector2f position);
	void changeRotation(float rotation);
	void update(float dt);
	sf::Sprite getSprite();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};