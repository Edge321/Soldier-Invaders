#include "Background.h"
#include "Character.h"
#include "Player.h"
#include "Projectile.h"
#include "Soldier.h"
#include "Bindings.h"
#include "Barrier.h"
#include <iostream>

/*
The game to make: can guide your missile, space invaders-like

Ideas:
Make the rocket have a limited time active
Player is able to kill themselves with their rocket
Have the player choose a fast normal rocket, and a somewhat fast guided rocket
*/

void soldierSpawning();
void movement(float xDirection);
void shoot();
void projectileDestroyed();
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
bool checkCollision(sf::Sprite sprite1, sf::FloatRect shape2);
void shutdown();

Bindings binds;
/* Window parameters */
sf::Vector2i windowSize(1024, 768);
sf::VideoMode vm(windowSize.x, windowSize.y);
sf::RenderWindow window(vm, "Soldier Invaders", sf::Style::Default);
int frameLimit = 60;

Background bg;
Background sky;
/* Player parameters */
Player hero;
int xOffset = 900;
int yOffset = 75;
float heroRotation = 270.0f;
float heroMovement = 250.0f;
/* Projectile parameters */
Projectile projectile = Projectile();
sf::Vector2f projectileOffest(6.0f, -35.0f);
sf::Vector2f projectileScale(0.8f, 0.5f);
float startingRocketRotation = 270.0f;
float rotationSpeed = 160.0f;
float guidedRocketSpeed = 550.0f;
float normalRocketSpeed = 1000.0f;
/* Soldier parameters */
std::vector<Soldier*> soldiers;
sf::Vector2f soldierPosition(80, 30); //Position where first soldier will spawn
sf::Vector2f soldierScale(0.4f, 0.4f);
int totalSoldiers = 40;
int soldierLimit = 10; //How many soldiers allowed in one row
int solSpacing = 80; //Spacing between soldiers when spawning
float soldierSpeed = 10.0f;
float soldierRotation = 270.0f;
float soldierSpeedChange = 2.5f; //How fast soldiers become when allies killed
/* Barrier parameters */
std::vector<Barrier*> barriers;
sf::Vector2f barrierSize(80.0f, 30.0f);
int totalBarriers = 6;
int xBarrierOffset = 960;
int yBarrierOffset = 170;
int spacing = 180;
int barrierHealth = 8;

void initBindings() {
	binds.storeBinding("Shoot", sf::Keyboard::Space);
	binds.storeBinding("Left", sf::Keyboard::A);
	binds.storeBinding("Right", sf::Keyboard::D);
	binds.storeBinding("Switch", sf::Keyboard::S);
}

void init() {
	sf::Vector2f heroPosition(window.getSize().x - xOffset, window.getSize().y - yOffset);

	bg.init("Assets/Graphics/bg.png");
	sky.init("Assets/Graphics/sky.png");
	hero.init("Assets/Graphics/hero.png", heroPosition);
	hero.setScale(sf::Vector2f(0.5f, 0.5f));
	hero.changeRotation(heroRotation);
	projectile.init("Assets/Graphics/rocket.png", sf::Vector2f(0, 0));
	projectile.setGuidedSpeed(guidedRocketSpeed);
	projectile.setNormalSpeed(normalRocketSpeed);
	projectile.setScale(projectileScale);
	projectile.disabled();

	for (int i = 0; i < totalBarriers; i++) {
		barriers.push_back(new Barrier());
	}

	for (int i = 0; i < barriers.size(); i++) {
		sf::Vector2f startPosition(window.getSize().x - xBarrierOffset + (i * spacing), 
									window.getSize().y - yBarrierOffset);
		barriers[i]->init(barrierSize, startPosition, sf::Color::Red, barrierHealth);
	}

	for (int i = 0; i < totalSoldiers; i++) {
		soldiers.push_back(new Soldier());
	}

	soldierSpawning();
}

void draw() {
	window.draw(sky.getSprite());
	window.draw(bg.getSprite());
	window.draw(hero.getSprite());
	if (projectile.getStatus())
		window.draw(projectile.getSprite());
	//window.draw(soldier.getSprite());

	for (int i = 0; i < soldiers.size(); i++) {
		window.draw(soldiers[i]->getSprite());
	}

	for (int i = 0; i < barriers.size(); i++) {
		barriers[i]->setColor();
		window.draw(barriers[i]->getRectangle());
	}
}

void updateInput(float dt) {
	sf::Event event;
	int xDirection = 1;

	while (window.pollEvent(event)) {
		//Player bindings
		if (binds.validBinding("Shoot", event) && !projectile.getStatus()) {
			shoot();
			//printf("Shoot\n");
		}
		if (binds.validBinding("Switch", event) && !projectile.getStatus()) {
			projectile.switchModes();
			//printf("Switched!\n");
		}
		if (binds.validBinding("Left", event)) {
			movement(-xDirection);
			//printf("Left\n");
		}
		else if (binds.validBinding("Right", event)) {
			movement(xDirection);
			//printf("Right\n");
		}

		if (event.type == sf::Event::KeyReleased) {
			movement(0);
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void update(float dt) {
	bool outOfBounds = false;
	
	hero.update(dt);

	for (int i = 0; i < soldiers.size(); i++) {
		soldiers[i]->update(dt);
		if (soldiers[i]->checkOutOfBound())
			outOfBounds = true;
	}
	//Changes all soldiers movement, and moves them down the screen
	if (outOfBounds) {
		for (int i = 0; i < soldiers.size(); i++) {
			soldiers[i]->changeDirection();
			soldiers[i]->moveDown();
		}
	}

	if (projectile.getStatus()) {
		projectile.update(dt);
		hero.setMovement(0);
		if (projectile.getOutofBounds()) {
			projectileDestroyed();
		}
		//If projectile has collided with enemy soldier
		for (int i = 0; i < soldiers.size(); i++) {
			if (checkCollision(projectile.getSprite(), soldiers[i]->getSprite())) {
				projectileDestroyed();
				Soldier* tempSol = soldiers[i];
				soldiers.erase(soldiers.begin() + i);
				delete(tempSol);

				for (int k = 0; k < soldiers.size(); k++) {
					soldiers[k]->changeSpeed(soldierSpeedChange);
				}

				break;
			}
		}
		if (checkCollision(projectile.getSprite(), hero.getSprite())) {
			projectileDestroyed();
			printf("You killed yourself?!\n");
		}
		//If projectile has collided with any barriers
		for (int i = 0; i < barriers.size(); i++) {
			if (checkCollision(projectile.getSprite(), barriers[i]->getCollider())) {
				projectileDestroyed();
				if (barriers[i]->changeHealth(-1)) {
					Barrier* tempBar = barriers[i];
					barriers.erase(barriers.begin() + i);
					delete(tempBar);
				}
				break;
			}
		}

	}
}

int main() {
	sf::Clock clock;
	window.setFramerateLimit(frameLimit);

	initBindings();
	init();

	while (window.isOpen()) {
		sf::Time dt = clock.restart();
		updateInput(dt.asSeconds());
		update(dt.asSeconds());

		window.clear(sf::Color::Red);

		draw();
		window.display();
	}

	shutdown();

	return 0;
}
/**
 * @brief Spawns soldiers in a square/rectangle space
 */
void soldierSpawning() {
	float startPosX = soldierPosition.x;
	float startPosY = soldierPosition.y;
	sf::Vector2f startPosition(startPosX, startPosY);

	//This is to avoid k being incremented at the beginning as xPos would start at 0
	soldiers[0]->init("Assets/Graphics/enemy.png", startPosition);
	soldiers[0]->setSpeed(soldierSpeed);
	soldiers[0]->changeRotation(soldierRotation);
	soldiers[0]->setScale(soldierScale);

	int k = 0;
	int xPos;

	for (int i = 1; i < soldiers.size(); i++) {
		xPos = i % soldierLimit;
		if (xPos == 0)
			k++;
		//Setting positions of soldiers in a square/rectangle-like space
		startPosX = soldierPosition.x + (xPos * solSpacing);
		startPosY = soldierPosition.y + (k * solSpacing);
		startPosition = sf::Vector2f(startPosX, startPosY);

		soldiers[i]->init("Assets/Graphics/enemy.png", startPosition);
		soldiers[i]->setSpeed(soldierSpeed);
		soldiers[i]->changeRotation(soldierRotation);
		soldiers[i]->setScale(soldierScale);
	}
}
/**
 * @brief Decides movement based on if the player/projectile is active
 * 
 * @param keyDirection negative number to go left, positive number to go right
 * @param dt Delta time
 */
void movement(float keyDirection) {
	if (projectile.getStatus())
		projectile.setRotater(rotationSpeed * keyDirection);
	else
		hero.setMovement(heroMovement * keyDirection);
}
/**
 * @brief Creates a projectile object which the player will control manually
 */
void shoot() {
	sf::Vector2f projectilePosition(hero.getSprite().getPosition().x + projectileOffest.x,
		hero.getSprite().getPosition().y + projectileOffest.y);

	projectile.enabled();
	projectile.setPosition(projectilePosition);
	projectile.changeRotation(startingRocketRotation);
	projectile.setRotater(0); //Prevents projectile rotation without player's input on spawn
	hero.setHeroMove(false);
	hero.disabled();
}
/**
 * @brief Sets parameters to indicate projectile is destroyed
 */
void projectileDestroyed() {
	projectile.disabled();
	hero.setHeroMove(true);
	hero.enabled();
}
/**
 * @brief Checks if sprite1 collided with sprite2
 * 
 * @return true or false
 */
bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {
	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if (shape1.intersects(shape2))
		return true;
	else
		return false;
}
/**
 * @brief Checks if sprite1 collided with shape2
 *
 * @return true or false
 */
bool checkCollision(sf::Sprite sprite1, sf::FloatRect shape2) {
	sf::FloatRect shape1 = sprite1.getGlobalBounds();

	if (shape1.intersects(shape2))
		return true;
	else
		return false;
}
/**
 * @brief Frees up all space used in-game
 */
void shutdown() {
	//Frees barriers
	for (int i = 0; i < barriers.size(); i++) {
		Barrier *tempBar = barriers[i];
		barriers.erase(barriers.begin() + i);
		delete(tempBar);
	}
	//Frees soldiers
	for (int i = 0; i < soldiers.size(); i++) {
		Soldier* tempSol = soldiers[i];
		soldiers.erase(soldiers.begin() + i);
		delete(tempSol);
	}
}
