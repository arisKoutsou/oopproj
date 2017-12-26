#include <iostream>
#include <cstdint>
#include "market.h"
#include "spell.h"
#include "item.h"
#include "living.h"

using namespace std;

Market :: Market(uint16_t _max_capacity, uint16_t _max_spells,
		 uint16_t _max_items)

  : max_capacity(_max_capacity),
    max_spells(_max_spells),
    max_items(_max_items) {

  cout << "Creating an instance of Market" << endl;
}

Market :: ~Market() {
  cout << "Destroying a Market" << endl;
}

uint16_t Market :: get_max_capacity() const { return max_capacity; }

uint16_t Market :: get_max_spells() const { return max_spells; }

uint16_t Market :: get_curr_spells() const {
  return (static_cast<uint16_t>(spells.size()));
}

uint16_t Market :: get_max_items() const { return max_items; }

uint16_t Market :: get_curr_items() const {
  return (static_cast<uint16_t>(items.size()));
}

void Market :: add_item(Item* item) {
  items.push_back(item);
}

// TODO (George): When I implement an inventory for the heroes I should
// add/remove the item just bought/selled into/from the inventory
// and also update it's info.

uint8_t Market :: buy(Item* item, size_t index, Hero* hero) {
  double price = static_cast<double>(item->get_price());
  double money = hero->get_money();
  if (item->get_min_level() <= hero->get_level() &&
      price <= money) {

    hero->update_money(money - price);
    //items.erase(index); FIXME (George): This has a problem
    return 0U;
    // If 1 gets returned the caller should print that the hero hasn't got enough money.
  } else if (price > money) return 1U; 
  // If 2 gets returned the caller should print that the hero hasn't got the
  // level required to aquire this item.
  else return 2U;
}

uint8_t Market :: buy(Spell* spell, size_t index, Hero* hero) {
  double price = static_cast<double>(spell->get_price());
  double money = hero->get_money();
  if (spell->get_min_level() <= hero->get_level() &&
      price <= money) {

    hero->update_money(money - price);
    //spells.erase(index); FIXME (George): This has a problem
    return 0U;
  } else if (price > money) return 1U;
  else return 2U;
}

void Market :: sell(Item* item, size_t index, Hero* hero) {
  double money = hero->get_money();
  double price = static_cast<double>(item->get_price());
  hero->update_money(money + (price / 2));
}

void Market :: sell(Spell* spell, size_t index, Hero* hero) {
  double money = hero->get_money();
  double price = static_cast<double>(spell->get_price());
  hero->update_money(money + (price / 2));
}
