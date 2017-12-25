#ifndef __MARKET__
#define __MARKET__

#include <iostream>
#include <cstdint>
#include <list>

class Spell;
class Item;
class Hero;

using namespace std;

class Market {
public:
  Market(uint16_t max_capacity, uint16_t max_spells,
	 uint16_t max_items);
  ~Market();
  uint16_t get_max_capacity() const;
  uint16_t get_max_spells() const;
  uint16_t get_curr_spells() const;
  uint16_t get_max_items() const;
  uint16_t get_curr_items() const;
  uint8_t buy(Item* item, size_t index, Hero* hero);
  uint8_t buy(Spell* spell, size_t index, Hero* hero);
  void sell(Item* item, size_t index, Hero* hero);
  void sell(Spell* spell, size_t index, Hero* hero);
  void add_item(Item* item);
private:
  uint16_t max_capacity;
  uint16_t max_spells;
  uint16_t max_items;
  list<Spell*> spells;
  list<Item*> items;
};

#endif
