#include <iostream>
#include <cstdint>
#include "living.h"

using namespace std;

Living :: Living(const string& _name, uint32_t _level, uint64_t _health,
		 uint16_t _x, uint16_t _y)
  
  : passed_out(false), name(_name),
    level(_level), health(_health),
    max_health(_health), co(_x, _y) {

  cout << "Creating an instance of Living" << endl;
}

Living :: ~Living() { cout << "Destroying a Living" << endl; }

Living :: Coordinates :: Coordinates(uint16_t _x, uint16_t _y)
  : x(_x), y(_y) {

  cout << "Creating a Coordinates instance" << endl;
}

Living :: Coordinates :: ~Coordinates() {
  cout << "Destroying Coordinates" << endl;
}

string Living :: get_name() const { return name; }

uint32_t Living :: get_level() const { return level; }

uint64_t Living :: get_health() const { return health; }

uint64_t Living :: get_max_health() const { return max_health; }

bool Living :: get_passed_out() const { return passed_out; }

void Living :: update_max_health(uint64_t _max_health) {
  max_health = _max_health;
}

Hero :: Coordinates Living :: get_coordinates() const { return co; }

Hero :: Hero(const string& _name, uint32_t _level, uint64_t _health,
	     uint32_t _mana, uint32_t _strength, uint32_t _dexterity,
	     uint32_t _agility, double _money, double _xp, uint16_t _x,
	     uint16_t _y, uint8_t _smult, uint8_t _dmult, uint8_t _amult)

  : Living(_name, _level, _health, _x, _y), mana(_mana),
    strength(_strength), dexterity(_dexterity),
    agility(_agility), money(_money), xp(_xp),
    max_mana(_mana), smult(_smult), dmult(_dmult), amult(_amult),
    defence(0U), min_damage(_strength* 2U), max_damage(_strength* 3U) {
  
  cout << "Creating an instance of Hero" << endl;
}

Hero :: ~Hero() { cout << "Destroying a Hero" << endl; }

uint8_t Hero :: get_smult() const { return smult; }

uint8_t Hero :: get_dmult() const { return dmult; }

uint8_t Hero :: get_amult() const { return amult; }

uint32_t Hero :: get_mana() const { return mana; }

uint32_t Hero :: get_max_mana() const { return max_mana; }

uint32_t Hero :: get_strength() const { return strength; }

uint32_t Hero :: get_dexterity() const { return dexterity; }

uint32_t Hero :: get_agility() const { return agility; }

uint64_t Hero :: get_min_damage() const { return min_damage; }

uint64_t Hero :: get_max_damage() const { return max_damage; }

uint64_t Hero :: get_defence() const { return defence; }

double Hero :: get_money() const { return money; }

double Hero :: get_experience() const { return xp; }

void Hero :: update_money(double _money) {
  money = _money;
}

void Hero :: set_strength(uint32_t _strength) {
  strength = _strength;
}

void Hero :: set_dexterity(uint32_t _dexterity) {
  dexterity = _dexterity;
}

void Hero :: set_agility(uint32_t _agility) {
  agility = _agility;
}

void Hero :: update_max_mana(uint64_t _max_mana) {
  max_mana = _max_mana;
}

Warrior :: Warrior(const string& _name, uint32_t _level, uint64_t _health,
		   uint32_t _mana, uint32_t _strength, uint32_t _dexterity,
		   uint32_t _agility, double _money, double _xp,
		   uint16_t _x, uint16_t _y, uint8_t _smult,
		   uint8_t _dmult, uint8_t _amult)

  : Hero(_name, _level, _health, _mana, _strength, _dexterity,
	 _agility, _money, _xp, _x, _y, _smult, _dmult, _amult) {

    cout << "Creating an instance of Warrior" << endl;
}

Warrior :: ~Warrior() { cout << "Destroying a Warrior" << endl; }

void Warrior :: level_up() {
  this->set_strength(this->get_strength() + this->get_smult());
  this->set_dexterity(this->get_dexterity() + this->get_dmult());
  this->set_agility(this->get_agility() + this->get_amult());
  this->update_max_health(this->get_max_health() + WARRIOR_HEALTH_UP);
  this->update_max_mana(this->get_max_mana() + WARRIOR_MANA_UP);
}

Sorcerer :: Sorcerer(const string& _name, uint32_t _level, uint64_t _health,
		     uint32_t _mana, uint32_t _strength, uint32_t _dexterity,
		     uint32_t _agility, double _money, double _xp,
		     uint16_t _x, uint16_t _y, uint8_t _smult,
		     uint8_t _dmult, uint8_t _amult)

  : Hero(_name, _level, _health, _mana, _strength, _dexterity,
	 _agility, _money, _xp, _x, _y, _smult, _dmult, _amult) {

  cout << "Creating an instance of Sorcerer" << endl;
}

Sorcerer :: ~Sorcerer() { cout << "Destroying a Sorcerer" << endl; }

void Sorcerer :: level_up() {
  this->set_strength(this->get_strength() + this->get_smult());
  this->set_dexterity(this->get_dexterity() + this->get_dmult());
  this->set_agility(this->get_agility() + this->get_amult());
  this->update_max_health(this->get_max_health() + SORCERER_HEALTH_UP);
  this->update_max_mana(this->get_max_mana() + SORCERER_MANA_UP);
}

Paladin :: Paladin(const string& _name, uint32_t _level, uint64_t _health,
		   uint32_t _mana, uint32_t _strength, uint32_t _dexterity,
		   uint32_t _agility, double _money, double _xp,
		   uint16_t _x, uint16_t _y, uint8_t _smult,
		   uint8_t _dmult, uint8_t _amult)

  : Hero(_name, _level, _health, _mana, _strength, _dexterity,
	 _agility, _money, _xp, _x, _y, _smult, _dmult, _amult) {

  cout << "Creating an instance of Paladin" << endl;
}

Paladin :: ~Paladin() { cout << "Destroying a Paladin" << endl; }

void Paladin :: level_up() {
  this->set_strength(this->get_strength() + this->get_smult());
  this->set_dexterity(this->get_dexterity() + this->get_dmult());
  this->set_agility(this->get_agility() + this->get_amult());
  this->update_max_health(this->get_max_health() + PALADIN_HEALTH_UP);
  this->update_max_mana(this->get_max_mana() + PALADIN_MANA_UP);
}

Monster :: Monster(const string& _name, uint32_t _level, uint64_t _health,
		   uint64_t _min_damage, uint64_t _max_damage,
		   uint32_t _defence, double _dodge, uint16_t _x,
		   uint16_t _y)
  
  : Living(_name, _level, _health, _x, _y), defence(_defence),
    min_damage(_min_damage), max_damage(_max_damage), dodge(_dodge) {

  cout << "Creating an instance of Monster" << endl;
}

Monster :: ~Monster() { cout << "Destroying a Monster" << endl; }

Dragon :: Dragon(const string& _name, uint32_t _level, uint64_t _health,
		 uint64_t _min_damage, uint64_t _max_damage,
		 uint32_t _defence, double _dodge, uint16_t _x,
		 uint16_t _y)

  : Monster(_name, _level, _health, _min_damage, _max_damage,
	    _defence, _dodge, _x, _y) {

  cout << "Creating a Dragon" << endl;
}

Dragon :: ~Dragon() { cout << "Destroying a Dragon" << endl; }

Exoskeleton :: Exoskeleton(const string& _name, uint32_t _level,
			   uint64_t _health, uint64_t _min_damage,
			   uint64_t _max_damage, uint32_t _defence,
			   double _dodge, uint16_t _x, uint16_t _y)

  : Monster(_name, _level, _health, _min_damage, _max_damage,
	    _defence, _dodge, _x, _y) {

  cout << "Creating an instance of Exoskeleton" << endl;
}

Exoskeleton :: ~Exoskeleton() {
  cout << "Destroying an Exoskeleton" << endl;
}

Spirit :: Spirit(const string& _name, uint32_t _level, uint64_t _health,
		 uint64_t _min_damage, uint64_t _max_damage,
		 uint32_t _defence, double _dodge, uint16_t _x,
		 uint16_t _y)

  : Monster(_name, _level, _health, _min_damage, _max_damage,
	    _defence, _dodge, _x, _y) {

  cout << "Creating an instance of Spirit" << endl;
}

Spirit :: ~Spirit() { cout << "Destroying a Spirit" << endl; }
