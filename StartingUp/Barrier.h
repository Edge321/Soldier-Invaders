#include <SFML/Graphics.hpp>

#pragma once
class Barrier
{
public:
	void init(sf::Vector2f rectangleSize, sf::Vector2f position, sf::Color color, int startingHealth);
	bool changeHealth(int healthModifier);
	void setColor();
	sf::FloatRect getCollider();
	sf::RectangleShape getRectangle();

private:
	sf::RectangleShape m_textureRectangle;
	int rColor = 255;
	int m_totalHealth = 1;
	int m_moddedHealth;

};

