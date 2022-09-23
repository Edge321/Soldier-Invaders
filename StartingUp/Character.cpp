#include "Character.h"

Character::Character() {}
Character::~Character() {}

void Character::init(std::string texturePath, sf::Vector2f position) {
	m_position = position;

	m_texture.loadFromFile(texturePath.c_str());

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void Character::changeRotation(float rotation) {
	m_sprite.setRotation(rotation);
}

sf::Sprite Character::getSprite() {
	return m_sprite;
}