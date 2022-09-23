#include "Projectile.h"

Projectile::Projectile() {}
Projectile::~Projectile() {}

void Projectile::update(float dt) {

}

void Projectile::rotate(float dt, float angleChange) {
	m_sprite.setRotation(m_sprite.getRotation() + (dt * angleChange));
}