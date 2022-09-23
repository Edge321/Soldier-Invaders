#include "Player.h"

void Player::setMovement(float movement) {
	m_movement = movement;
}

void Player::update(float dt) {
	sf::Vector2f currentPosition(m_sprite.getPosition());
	m_sprite.setPosition(currentPosition.x + (m_movement * dt), currentPosition.y);
}