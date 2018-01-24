/*
 * Living.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: aris
 */
#include <iostream>

#include "./Living.h"
#include "../grid/Grid.h"

Living::Living(
	Grid* gr,
	int y,
	int x,
	string nam,
	int hp
)
  : grid(gr), p(x, y),
    name(nam), level(1),
    healthPower(hp)	// Level start at 1.
{
}

Living::~Living() {}

int Living::getHealthPower() const {
	return healthPower;
}

int Living::getLevel() const {
	return level;
}

const string& Living::getName() const {
	return name;
}

void Living::receiveDamage(int damageDealt) {
	healthPower -= damageDealt;	// Derived classes use this.
								// And then kill the living.
}

// Implemented by: (George Liontos)
void Living :: setHealthPower(int health) {
  healthPower = health;
}

bool Living :: operator==(const Living& rValue) const {
  bool sameName;
  bool sameLevel;
  bool sameHealthPower;
  bool samePosition;

  sameName = (this->name == rValue.name) ? true : false;
  sameLevel = (this->level == rValue.level) ? true : false;
  sameHealthPower = (this->healthPower == rValue.healthPower) ? true : false;
  samePosition = (this->p == rValue.p) ? true : false;

  return (sameName && sameLevel && sameHealthPower && samePosition);
}

Living :: Position& Living :: getPosition() {
  return p;
}

Living :: Position :: Position(int _x, int _y)
  : x(_x), y(_y) {}

Living :: Position :: ~Position() {}

int Living :: Position :: getX() const {
  return x;
}

int Living :: Position :: getY() const {
  return y;
}

void Living :: Position :: setX(int _x) {
  x = _x;
}

void Living :: Position :: setY(int _y) {
  y = _y;
}

bool Living :: Position :: operator==(const Position& rValue) const {
  bool sameX;
  bool sameY;

  sameX = (this->x == rValue.x) ? true : false;
  sameY = (this->y == rValue.y) ? true : false;

  return (sameX && sameY);
}

void Living :: printStats() const {
  cout << "Name: " << this->name << endl
       << "Level: " << this->level << endl
       << "Health: " << this->healthPower << endl;
}
