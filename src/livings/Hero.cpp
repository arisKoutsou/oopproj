/*
 * Hero.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */

#include "Hero.h"
#include "../grid/Grid.h"
#include "../exceptions/heroExceptions.h"

Hero::Hero(
	string nam,
	int hp,
	int mp,
	int s,
	int a,
	int d
)
: Living(nam, hp),
  magicPower(mp),
  strength(s), agility(a),
  dexterity(d), money(450),
  expirience(0), inventory()
{
	//
}

int Hero::getAgility() const {
	return agility;
}

int Hero::getDexterity() const {
	return dexterity;
}

int Hero::getExpirience() const {
	return expirience;
}

int Hero::getMagicPower() const {
	return magicPower;
}

int Hero::getMoney() const {
	return money;
}

int Hero::getStrength() const {
	return strength;
}

// Implemented by: (George Liontos)
bool Hero :: operator==(const Hero& rValue) const {
  bool sameLiving;
  bool sameMagicPower;
  bool sameStrength;
  bool sameAgility;
  bool sameDexterity;
  bool sameMoney;
  bool sameExperience;
  // There's no need to check if they've got the same inventory

  sameLiving = (static_cast<Living>(*this) == rValue);
  sameMagicPower = (this->magicPower == rValue.magicPower) ? true : false;
  sameStrength = (this->strength == rValue.strength) ? true : false;
  sameAgility = (this->agility == rValue.agility) ? true : false;
  sameDexterity = (this->dexterity == rValue.dexterity) ? true : false;
  sameMoney = (this->money == rValue.money) ? true : false;
  sameExperience = (this->expirience == rValue.expirience) ? true : false;

  return (sameLiving && sameMagicPower &&
	  sameStrength && sameDexterity &&
	  sameAgility && sameMoney &&
	  sameExperience);
}

void Hero :: moveUp(Grid& grid) throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroY == grid.getMaxY()) {
    throw HeroMoveException("You can't move up any further");
  } else {
    grid.removeLiving(heroY, heroX, this);
    this->getPosition().setY(heroY + 1);
  }
}

void Hero :: moveDown(Grid& grid) throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();
 
  if (heroY == 0) {
    throw HeroMoveException("You can't move down any further");
  } else {
    grid.removeLiving(heroY, heroX, this);
    this->getPosition().setY(heroY - 1);
  }
}

void Hero :: moveLeft(Grid& grid) throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroX == 0) {
    throw HeroMoveException("You can't move left any further");
  } else {
    grid.removeLiving(heroY, heroX, this);
    this->getPosition().setX(heroX - 1);
  }
}

void Hero :: moveRight(Grid& grid) throw() {
  int heroY = this->getPosition().getY();
  int heroX = this->getPosition().getX();

  if (heroX == grid.getMaxX()) {
    throw HeroMoveException("You can't move right any further");
  } else {
    grid.removeLiving(heroY, heroX, this);
    this->getPosition().setX(heroX + 1);
  }
}

void Hero :: move(Grid& grid, directions direction) throw() {
  switch (direction) {
  case UP: moveUp(grid); return;
  case DOWN: moveDown(grid); return;
  case LEFT: moveLeft(grid); return;
  case RIGHT: moveRight(grid); return;
  default: throw HeroMoveException("Unknown direction"); return;
  }
}
