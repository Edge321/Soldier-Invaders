#include "Projectile.h"

Projectile::Projectile() {}
Projectile::~Projectile() {}

void Projectile::update(float dt) {
	float pi = 3.14159265f;
	//m_sprite.move(0, -100.0f * dt);
	//Converting degrees to radians here
	float x = cos(m_sprite.getRotation() * pi / 180.0f);
	float y = sin(m_sprite.getRotation() * pi / 180.0f);
	//printf("cos:%lf\tsin:%lf\n", x, y);
	//printf("degrees:%lf\n", m_sprite.getRotation());
	m_sprite.move(x * m_projectileSpeed * dt, y * m_projectileSpeed * dt);
}

void Projectile::rotate(float angleChange) {
	//m_sprite.setRotation(m_sprite.getRotation() + angleChange);
	m_sprite.rotate(angleChange);
}

void Projectile::setProjectileSpeed(float projectileSpeed) {
	m_projectileSpeed = projectileSpeed;
}