#include <iostream>
#include <cstdint>
#include "item.h"

using namespace std;

Item :: Item(const string& _name, uint32_t _price, uint32_t _min_level)

  : name(_name), price(_price), min_level(_min_level) {

  cout << "Creating an instation of Item" << endl;
}

Item :: ~Item() { cout << "Destroying an Item" << endl; }

string Item :: get_name() const { return name; }

uint32_t Item :: get_price() const { return price; }

uint32_t Item :: get_min_level() const { return min_level; }

Weapon :: Weapon(const string& _name, uint32_t _price, uint32_t _min_level,
		 uint64_t _min_damage, uint64_t _max_damage, bool _two_handed)

  : Item(_name, _price, _min_level),
    min_damage(_min_damage), max_damage(_max_damage),
    two_handed(_two_handed) {

  cout << "Creating an instance of Weapon" << endl;
}

Weapon :: ~Weapon() { cout << "Destroying a Weapon" << endl; }

uint64_t Weapon :: get_min_damage() const { return min_damage; }

uint64_t Weapon :: get_max_damage() const { return max_damage; }

bool Weapon :: get_two_handed() const { return two_handed; }

Armor :: Armor(const string& _name, uint32_t _price, uint32_t _min_level,
	uint64_t _defence)
  : Item(_name, _price, _min_level), defence(_defence) {

  cout << "Creating an instance of Armor" << endl;
}

Armor :: ~Armor() { cout << "Destroying an Armor" << endl; }

uint64_t Armor :: get_defence() const { return defence; }

Potion :: Potion(const string& _name, uint32_t _price, uint32_t _min_level,
		 const string& _stat, uint32_t _amount)
  : Item(_name, _price, _min_level), stat(_stat), amount(_amount) {
  
  cout << "Creating an instance of Potion" << endl;
}

Potion :: ~Potion() { cout << "Destroying a Potion" << endl; }

string Potion :: get_stat() const { return stat; }

uint32_t Potion :: get_amount() const { return amount; }
