#include <SFML/Graphics.hpp>

#pragma once
class Barrier
{
public:
	void init(sf::Vector2f rectangleSize, sf::Vector2f position, sf::Color color);
	sf::FloatRect getCollider();
	sf::RectangleShape getRectangle();

private:
	sf::RectangleShape m_textureRectangle;
};

