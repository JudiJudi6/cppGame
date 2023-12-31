#include <SFML/Graphics.hpp>
#include "BonusEvent.h"
#include "Global.h"

BonusEvent::BonusEvent(int flag, sf::Vector2f position) {
	this->flag = flag;
	
	body.setSize(sf::Vector2f(35, 35));
	body.setPosition(position);

	if (flag == 0) {
		body.setTexture(&Global::getInstance().texture1);
	}
	if (flag == 1) {
		body.setTexture(&Global::getInstance().texture2);
	}
	if (flag == 2) {
		body.setTexture(&Global::getInstance().texture3);
	}
	if (flag == 3) {
		body.setTexture(&Global::getInstance().texture4);
	}
	body.setOrigin(sf::Vector2f(17.5f, 17.5f));
}

void BonusEvent::drawEvent(sf::RenderWindow& window) {
    window.draw(body);
}

void BonusEvent::action(Tank &tank) {
	//hp bonus
	if (flag == 0) {
		tank.setHealthPoints(tank.getHealthPoints() + 50);
		body.setPosition(-100, -100);
	}

	//dmg bonus
	if (flag == 1) {
		tank.setDamage(tank.getDamage() + 20);
		body.setPosition(-100, -150);
	}

	//speed bonus
	if (flag == 2) {
		tank.setSpeed(tank.getSpeed() + 0.2f);
		body.setPosition(-100, -200);
	}

	//bomb
	if (flag == 3) {
		tank.setAddMines();
		body.setPosition(-100, -250);
	}
}

void BonusEvent::getDestroyed(Bullet &bullet) {
	sf::FloatRect wallBounds = body.getGlobalBounds();
	sf::FloatRect bulletBounds = bullet.body.getGlobalBounds();
	if (wallBounds.intersects(bulletBounds)) {
		bullet.setActive(false);
		body.setPosition(-100, -300);
	}
}