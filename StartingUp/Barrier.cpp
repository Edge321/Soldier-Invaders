#include "Barrier.h"

void Barrier::init(sf::Vector2f rectangleSize, sf::Vector2f position, sf::Color color, int startingHealth) {
	m_textureRectangle.setSize(rectangleSize);
	m_textureRectangle.setFillColor(color);
	m_textureRectangle.setPosition(position);

	sf::Vector2f rectSize = m_textureRectangle.getSize();

	m_textureRectangle.setOrigin(sf::Vector2f(rectSize.x / 2, rectSize.y / 2));

	m_totalHealth = startingHealth;
	m_moddedHealth = m_totalHealth;
}

bool Barrier::changeHealth(int healthModifier) {
	m_moddedHealth += healthModifier;

	if (m_moddedHealth <= 0)
		return true;
	else
		return false;
}

void Barrier::setColor() {
	float mH = m_moddedHealth;
	float tH = m_totalHealth;
	float red = 255.0f * (mH / tH);

	sf::Color color(red, 0, 0, 255);
	m_textureRectangle.setFillColor(color);
}

sf::FloatRect Barrier::getCollider() {
	return m_textureRectangle.getGlobalBounds();
}

sf::RectangleShape Barrier::getRectangle() {
	return m_textureRectangle;
}
