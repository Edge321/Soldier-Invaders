#include "Background.h"

void Background::init(std::string textureName) {
	bgTexture.loadFromFile(textureName.c_str());
	bgSprite.setTexture(bgTexture);
}

sf::Sprite Background::getSprite() {
	return bgSprite;
}