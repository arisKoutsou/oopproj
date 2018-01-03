/*
 * Spell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>

#include "../../include/Spell.h"

Spell::Spell(
	string 	nam,
	int 	val,
	int 	minL,
	int 	magicP,
	int		minDmg,
	int 	maxDmg
)
: name(nam), value(val),
  minLevel(minL), magicPowerRequired(magicP),
  minDamage(minDmg), maxDamage(maxDmg), sellRate(0.4)
{
	cout << "Spell constructed..." << endl;
}

Spell::~Spell() {
	cout << "Spell destroyed !!!" << endl;
}

int Spell::getMagicPowerRequired() const {
	return magicPowerRequired;
}

int Spell::getMaxDamage() const {
	return maxDamage;
}

int Spell::getMinDamage() const {
	return minDamage;
}

int Spell::getMinLevel() const {
	return minLevel;
}

const string& Spell::getName() const {
	return name;
}

int Spell::getValue() const {
	return value;
}

int Spell::sellsFor() const {
	return (int)(value*sellRate);
}

string Spell::getInfo() const {
	stringstream result;

	result << "name: " << name << endl
		<< "price: " << getValue() << endl
		<< "sell for: " << sellsFor() << endl
		<< "min level to aquire: " << minLevel << endl
		<< "magic power required to cast: " << magicPowerRequired << endl
		<< "damage range: " << getMinDamage() << " to " << getMaxDamage() << endl;

	return result.str();

}

// Imlemented by: (George Liontos)
bool Spell :: operator==(const Spell& rValue) const {
  bool sameName;
  bool sameValue;
  bool sameMinLevel;
  bool sameMagicPowerRequired;
  bool sameMinDamage;
  bool sameMaxDamage;

  sameName = (this->name == rValue.name) ? true : false;
  sameValue = (this->value == rValue.value) ? true : false;
  sameMinLevel = (this->minLevel == rValue.minLevel) ? true : false;
  sameMagicPowerRequired =
    (this->magicPowerRequired == rValue.magicPowerRequired) ? true : false;
  sameMinDamage = (this->minDamage == rValue.minDamage) ? true : false;
  sameMaxDamage = (this->maxDamage == rValue.maxDamage) ? true : false;

  return (sameName && sameValue && sameMinLevel &&
	  sameMagicPowerRequired && sameMinDamage && sameMaxDamage);
}
