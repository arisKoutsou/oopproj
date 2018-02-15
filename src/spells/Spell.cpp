/*
 * Spell.cpp
 *
 *  Created on: Dec 29, 2017
 *      Author: aris
 */
#include <iostream>
#include <sstream>

#include "Spell.h"

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
  minDamage(minDmg), maxDamage(maxDmg), sellRate(0.4) {}

Spell::~Spell() {}

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

void Spell :: getInfo() const {}

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
