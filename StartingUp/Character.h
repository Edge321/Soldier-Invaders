/*********************************************************************
 * @file   Character.h
 * @brief  Base class for defining any object in-game
 * 
 * @author Edge321
 * @date   December 2022
 *********************************************************************/

#include <SFML/Graphics.hpp>

#pragma once
class Character
{
public:
	Character();
	~Character();

	//Does the basic initialization of a character
	void init(std::string texturePath, sf::Vector2f position);
	void changeRotation(float rotation);
	sf::Sprite getSprite();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};