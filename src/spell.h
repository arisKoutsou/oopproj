#ifndef __SPELL__
#define __SPELL__

#include <iostream>
#include <cstdint>

using namespace std;

class Spell {
public:
  virtual ~Spell();
  string get_name() const;
  uint32_t get_price() const;
  uint32_t get_min_level() const;
  uint32_t get_mana_cost() const;
  uint64_t get_min_damage() const;
  uint64_t get_max_damage() const;
protected:
  Spell(const string& name, uint32_t price, uint32_t min_level,
	uint64_t min_damage, uint64_t max_damage, uint32_t mana_cost);
private:
  string name;
  uint32_t price;
  uint32_t min_level;
  uint32_t mana_cost;
  uint64_t min_damage;
  uint64_t max_damage;
};

class IceSpell : public Spell {
public:
  IceSpell(const string& name, uint32_t price, uint32_t min_level,
	   uint64_t min_damage, uint64_t max_damage, uint32_t mana_cost,
	   uint64_t amount, uint16_t rounds);
  ~IceSpell();
  uint64_t get_amount() const;
  uint16_t get_rounds() const;
private:
  uint64_t amount;
  uint16_t rounds;
};

class FireSpell : public Spell {
public:
  FireSpell(const string& name, uint32_t price, uint32_t min_level,
	    uint64_t min_damage, uint64_t max_damage, uint32_t mana_cost,
	    uint64_t amount, uint16_t rounds);
  ~FireSpell();
  uint64_t get_amount() const;
  uint16_t get_rounds() const;
private:
  uint32_t amount;
  uint16_t rounds;
};

class LightningSpell : public Spell {
public:
  LightningSpell(const string& name, uint32_t price, uint32_t min_level,
		 uint64_t min_damage, uint64_t max_damage,
		 uint32_t mana_cost, double amount, uint16_t rounds);
  ~LightningSpell();
  double get_amount() const;
  uint16_t get_rounds() const;
private:
  double amount;
  uint16_t rounds;
};
		     
#endif
