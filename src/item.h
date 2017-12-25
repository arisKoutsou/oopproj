#ifndef __ITEM__
#define __ITEM__

#include <iostream>
#include <cstdint>

using namespace std;

class Item {
public:
  virtual ~Item();
  string get_name() const;
  uint32_t get_price() const;
  uint32_t get_min_level() const;
protected:
  Item(const string& name, uint32_t price, uint32_t min_level);
private:
  string name;
  uint32_t price;
  uint32_t min_level;
};

class Weapon : public Item {
public:
  Weapon(const string& name, uint32_t price, uint32_t min_level,
	 uint64_t min_damage, uint64_t max_damage, bool two_handed);
  ~Weapon();
  uint64_t get_min_damage() const;
  uint64_t get_max_damage() const;
  bool get_two_handed() const;
private:
  uint64_t min_damage;
  uint64_t max_damage;
  bool two_handed;
};

class Armor : public Item {
public:
  Armor(const string& name, uint32_t price, uint32_t min_level,
	uint64_t defence);
  ~Armor();
  uint64_t get_defence() const;
private:
  uint64_t defence;
};

class Potion : public Item {
public:
  Potion(const string& name, uint32_t price, uint32_t min_level,
	 const string& stat, uint32_t amount);
  ~Potion();
  string get_stat() const;
  uint32_t get_amount() const;
private:
  string stat;
  uint32_t amount;
};

#endif
