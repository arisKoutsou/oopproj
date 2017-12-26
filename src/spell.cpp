#include <iostream>
#include <cstdint>
#include "spell.h"

using namespace std;

Spell :: Spell(const string& _name, uint32_t _price, uint32_t _min_level,
	       uint64_t _min_damage, uint64_t _max_damage,
	       uint32_t _mana_cost)
  
  : name(_name), price(_price), min_level(_min_level),
    min_damage(_min_damage), max_damage(_max_damage),
    mana_cost(_mana_cost) {

  cout << "Creating an instance of Spell" << endl;
}


Spell :: ~Spell() { cout << "Destroying a Spell" << endl; }

string Spell :: get_name() const { return name; }

uint32_t Spell :: get_price() const { return price; }

uint32_t Spell :: get_min_level() const { return min_level; }

uint32_t Spell :: get_mana_cost() const { return mana_cost; }

uint64_t Spell :: get_min_damage() const { return min_damage; }

uint64_t Spell :: get_max_damage() const { return max_damage; }

IceSpell :: IceSpell(const string& _name, uint32_t _price, uint32_t _min_level,
		     uint64_t _min_damage, uint64_t _max_damage,
		     uint32_t _mana_cost, uint64_t _amount,
		     uint16_t _rounds)
  
  : Spell(_name, _price, _min_level, _min_damage, _max_damage,
	  _mana_cost),
    amount(_amount), rounds(_rounds) {

  cout << "Creating an instance of IceSpell" << endl;
}

IceSpell :: ~IceSpell() { cout << "Destroying an IceSpell" << endl; }

uint64_t IceSpell :: get_amount() const { return amount; }

uint16_t IceSpell :: get_rounds() const { return rounds; }

FireSpell :: FireSpell(const string& _name, uint32_t _price, uint32_t _min_level,
		       uint64_t _min_damage, uint64_t _max_damage,
		       uint32_t _mana_cost, uint64_t _amount,
		       uint16_t _rounds)
  
  : Spell(_name, _price, _min_level, _min_damage, _max_damage,
	  _mana_cost),
    amount(_amount), rounds(_rounds) {

  cout << "Creating an instance of FireSpell" << endl;
}

FireSpell :: ~FireSpell() { cout << "Destroying an FireSpell" << endl; }

uint64_t FireSpell :: get_amount() const { return amount; }

uint16_t FireSpell :: get_rounds() const { return rounds; }

LightningSpell :: LightningSpell(const string& _name, uint32_t _price,
				 uint32_t _min_level, uint64_t _min_damage,
				 uint64_t _max_damage,
				 uint32_t _mana_cost, double _amount,
				 uint16_t _rounds)
  
  : Spell(_name, _price, _min_level, _min_damage, _max_damage,
	  _mana_cost),
    amount(_amount), rounds(_rounds) {

  cout << "Creating an instance of FireSpell" << endl;
}

LightningSpell :: ~LightningSpell() {
  cout << "Destroying an FireSpell" << endl;
}

double LightningSpell :: get_amount() const { return amount; }

uint16_t LightningSpell :: get_rounds() const { return rounds; }
