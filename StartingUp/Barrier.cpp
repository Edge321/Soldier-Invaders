#include "Barrier.h"

void Barrier::init(sf::Vector2f rectangleSize, sf::Vector2f position, sf::Color color) {
	m_textureRectangle.setSize(rectangleSize);
	m_textureRectangle.setFillColor(color);
	m_textureRectangle.setPosition(position);

	sf::Vector2f rectSize = m_textureRectangle.getSize();

	m_textureRectangle.setOrigin(sf::Vector2f(rectSize.x / 2, rectSize.y / 2));
}

sf::FloatRect Barrier::getCollider() {
	return m_textureRectangle.getGlobalBounds();
}

sf::RectangleShape Barrier::getRectangle() {
	return m_textureRectangle;
}
