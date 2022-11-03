#include "Projectile.h"

bool checkOutOfBounds(sf::Sprite sprite);

Projectile::Projectile() {}
Projectile::~Projectile() {}

void Projectile::update(float dt) {
	float pi = 3.14159265f;
	sf::Vector2i windowSize(1024, 768);

	//Converting degrees to radians here
	float x = cos(m_sprite.getRotation() * pi / 180.0f);
	float y = sin(m_sprite.getRotation() * pi / 180.0f);
	m_sprite.move(x * m_projectileSpeed * dt, y * m_projectileSpeed * dt);

	m_outOfBounds = checkOutOfBounds(m_sprite);

	printf("x:%lf\ty:%lf\n", m_sprite.getPosition().x, m_sprite.getPosition().y);
}

void Projectile::rotate(float angleChange) {
	m_sprite.rotate(angleChange);
}

void Projectile::setProjectileSpeed(float projectileSpeed) {
	m_projectileSpeed = projectileSpeed;
}

void Projectile::disabled() {
	m_sprite.setColor(sf::Color::Transparent);
	m_status = false;
}

void Projectile::enabled() {
	m_sprite.setColor(sf::Color::White);
	m_status = true;
}

bool checkOutOfBounds(sf::Sprite sprite) {
	sf::Vector2i windowSize(1024, 768);
	int offScreen = 10;

	if (sprite.getPosition().x > (windowSize.x + offScreen) || sprite.getPosition().x < 0 - offScreen ||
		sprite.getPosition().y > (windowSize.y + offScreen) || sprite.getPosition().y < 0 - offScreen)
		return true;

	return false;
}