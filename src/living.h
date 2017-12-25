#ifndef __LIVING__
#define __LIVING__

#include <iostream>
#include <cstdint>

#define WARRIOR_HEALTH_UP 250U
#define WARRIOR_MANA_UP 25U

#define SORCERER_HEALTH_UP 100U
#define SORCERER_MANA_UP 100U

#define PALADIN_HEALTH_UP 180U
#define PALADIN_MANA_UP 60U

#define DRAGON_BONUS 10U
#define EXOSKELETON_BONUS 15U
#define SPIRIT_BONUS 0.2

using namespace std;

class Living {
public:
  struct Coordinates {
    Coordinates(uint16_t x, uint16_t y);
    ~Coordinates();
    uint16_t x;
    uint16_t y;
  };
  virtual ~Living();
  string get_name() const;
  uint32_t get_level() const;
  uint64_t get_health() const;
  uint64_t get_max_health() const;
  bool get_passed_out() const;
  Coordinates get_coordinates() const;
  void update_max_health(uint64_t max_health);
protected:
  Living(const string& name, uint32_t level, uint64_t health,
	 uint16_t x, uint16_t y);
private:
  Coordinates co;
  string name;
  uint32_t level;
  uint64_t health;
  uint64_t max_health;
  // TODO (George) I must rethink if this data member should exist
  bool passed_out;
};

class Hero : public Living {
public:
  Hero(const string& name, uint32_t level, uint64_t health,
       uint32_t mana, uint32_t strength,
       uint32_t dexterity, uint32_t agility,
       double money, double xp, uint16_t x, uint16_t y,
       uint8_t smult, uint8_t dmult, uint8_t amult);
  ~Hero();
  uint8_t get_smult() const;
  uint8_t get_dmult() const;
  uint8_t get_amult() const;
  uint32_t get_mana() const;
  uint32_t get_max_mana() const;
  uint32_t get_strength() const;
  uint32_t get_dexterity() const;
  uint32_t get_agility() const;
  uint64_t get_min_damage() const;
  uint64_t get_max_damage() const;
  uint64_t get_defence() const;
  double get_money() const;
  double get_experience() const;
  void set_strength(uint32_t strength);
  void set_dexterity(uint32_t dexterity);
  void set_agility(uint32_t agility);
  void update_max_mana(uint64_t max_mana);
  void update_money(double money);
  // TODO (George) Maybe I should replenish mana and health each time
  // our hero levels up.
  virtual void level_up() = 0;
private:
  uint32_t mana;
  uint32_t max_mana;
  uint32_t strength;
  uint32_t dexterity;
  uint32_t agility;
  uint64_t min_damage;
  uint64_t max_damage;
  uint64_t defence;
  double money;
  double xp;
  uint8_t smult;
  uint8_t dmult;
  uint8_t amult;
};

class Warrior : public Hero {
public:
  Warrior(const string& name, uint32_t level = 1U, uint64_t health = 800U,
	  uint32_t mana = 250U, uint32_t strength = 10U,
	  uint32_t dexterity = 5U, uint32_t agility = 8U,
	  double money = 300.0, double xp = 0.0,
	  uint16_t x = 0U, uint16_t y = 0U,
	  uint8_t smult = 3U, uint8_t dmult = 1U, uint8_t amult = 2U);
  ~Warrior();
  void level_up();
};

class Sorcerer : public Hero {
public:
  Sorcerer(const string& name, uint32_t level = 1U, uint64_t health = 450U,
	   uint32_t mana = 500U, uint32_t strength = 5U,
	   uint32_t dexterity = 10U, uint32_t agility = 7U,
	   double money = 300.0, double xp = 0.0,
	   uint16_t x = 0U, uint16_t y = 0U,
	   uint8_t smult = 1U, uint8_t dmult = 3U, uint8_t amult = 2U);
  ~Sorcerer();
  void level_up();
};

class Paladin : public Hero {
public:
  Paladin(const string& name, uint32_t level = 1U, uint64_t health = 600U,
	  uint32_t mana = 400U, uint32_t strength = 9U,
	  uint32_t dexterity = 8U, uint32_t agility = 5U,
	  double money = 300.0, double xp = 0.0,
	  uint16_t x = 0U, uint16_t y = 0U,
	  uint8_t smult = 3U, uint8_t dmult = 2U, uint8_t amult = 1U);
  ~Paladin();
  void level_up();
};

// TODO (George): Find a way that the stats of the monsters vary
// based on their level (which will be determined by the level of
// the heros).

class Monster : public Living {
public:
  ~Monster();
  string get_name() const;
  uint32_t get_level() const;
  uint64_t get_health() const;
  uint64_t get_max_health() const;
  uint64_t get_defence() const;
  uint64_t get_min_damage() const;
  uint64_t get_max_damage() const;
  double get_dodge() const;
protected:
  Monster(const string& name, uint32_t level, uint64_t health,
	  uint64_t min_damage, uint64_t max_damage, uint32_t defence,
	  double dodge, uint16_t x, uint16_t y);
private:
  uint64_t defence;
  uint64_t min_damage;
  uint64_t max_damage;
  double dodge;
};

class Dragon : public Monster {
public:
  Dragon(const string& name, uint32_t level, uint64_t health,
	 uint64_t min_damage, uint64_t max_damage, uint32_t defence,
	 double dodge, uint16_t x, uint16_t y);
  ~Dragon();
};

class Exoskeleton : public Monster {
public:
  Exoskeleton(const string& name, uint32_t level, uint64_t health,
	      uint64_t min_damage, uint64_t max_damage, uint32_t defence,
	      double dodge, uint16_t x, uint16_t y);
  ~Exoskeleton();
};

class Spirit : public Monster {
public:
  Spirit(const string& name, uint32_t level, uint64_t health,
	 uint64_t min_damage, uint64_t max_damage, uint32_t defence,
	 double dodge, uint16_t x, uint16_t y);
  ~Spirit();
};

#endif
