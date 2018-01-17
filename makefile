CC=g++
CFLAGS= -std=c++98 -ggdb -Wall -fPIC

alltests : all bin/inventoryTest bin/itemTest bin/marketTest bin/spellTest bin/heroOnGridTest bin/attackTest

all : objects/exceptions/heroExceptions.o objects/grid/Grid.o objects/inventory/Inventory.o \
      objects/menu/Menu.o objects/market/Market.o objects/random/Random.o objects/items/Item.o \
      objects/items/Weapon.o objects/items/Armor.o objects/items/Potion.o objects/spells/Spell.o \
      objects/spells/FireSpell.o objects/spells/IceSpell.o objects/spells/LightningSpell.o \
      objects/livings/Living.o objects/livings/Hero.o objects/livings/Monster.o \
      objects/livings/heroes/Warrior.o objects/livings/heroes/Paladin.o objects/livings/heroes/Sorcerer.o \
      objects/livings/monsters/Dragon.o objects/livings/monsters/Spirit.o objects/livings/monsters/Exoskeleton.o

bin/inventoryTest : src/tests/inventoryTest.cpp objects/inventory/*.o objects/menu/*.o \
                      objects/items/*.o objects/spells/*.o
	$(CC) $(CFLAGS) src/tests/inventoryTest.cpp objects/inventory/*.o objects/menu/*.o \
			objects/items/*.o objects/spells/*.o -o bin/inventoryTest

bin/itemTest : src/tests/itemTest.cpp objects/items/*.o objects/random/*.o
	$(CC) $(CFLAGS) src/tests/itemTest.cpp objects/items/*.o objects/random/*.o -o bin/itemTest

bin/marketTest : src/tests/marketTest.cpp objects/market/*.o objects/menu/*.o objects/items/*.o objects/spells/*.o
	$(CC) $(CFLAGS) src/tests/marketTest.cpp objects/market/*.o objects/menu/*.o objects/items/*.o objects/spells/*.o \
			-o bin/marketTest

bin/spellTest : src/tests/spellTest.cpp objects/spells/*.o
	$(CC) $(CFLAGS) src/tests/spellTest.cpp objects/spells/*.o -o bin/spellTest

bin/heroOnGridTest : src/tests/heroOnGridTest.cpp objects/grid/*.o objects/livings/*.o objects/livings/heroes/*.o \
		       objects/exceptions/*.o objects/inventory/*.o objects/menu/*.o objects/market/*.o objects/random/*.o \
		       objects/items/*.o objects/spells/*.o
	$(CC) $(CFLAGS) src/tests/heroOnGridTest.cpp objects/grid/*.o objects/livings/*.o objects/livings/heroes/*.o \
		        objects/exceptions/*.o objects/inventory/*.o objects/menu/*.o objects/market/*.o objects/random/*.o \
			objects/items/*.o objects/spells/*.o \
			-o bin/heroOnGridTest

bin/attackTest : src/tests/attackTest.cpp objects/grid/*.o objects/livings/*.o objects/livings/heroes/*.o \
		  objects/livings/monsters/*.o objects/market/*.o objects/menu/*.o  objects/items/*.o
	$(CC) $(CFLAGS)	src/tests/attackTest.cpp objects/grid/*.o objects/livings/*.o objects/livings/heroes/*.o \
			objects/livings/monsters/*.o objects/market/*.o objects/menu/*.o  objects/items/*.o \
			objects/inventory/*.o objects/spells/*.o objects/random/*.o objects/exceptions/*.o \
			-o bin/attackTest

objects/exceptions/heroExceptions.o : src/exceptions/heroExceptions.cpp src/exceptions/heroExceptions.h
	$(CC) $(CFLAGS) -c src/exceptions/heroExceptions.cpp -o objects/exceptions/heroExceptions.o

objects/grid/Grid.o : src/grid/Grid.cpp src/grid/Grid.h src/market/Market.h src/livings/Living.h
	$(CC) $(CFLAGS) -c src/grid/Grid.cpp -o objects/grid/Grid.o

objects/inventory/Inventory.o : src/inventory/Inventory.cpp src/inventory/Inventory.h \
				   src/items/Item.h src/spells/Spell.h src/livings/Hero.h src/menu/Menu.h
	$(CC) $(CFLAGS) -c src/inventory/Inventory.cpp -o objects/inventory/Inventory.o

objects/menu/Menu.o : src/menu/Menu.cpp src/menu/Menu.h
	$(CC) $(CFLAGS) -c src/menu/Menu.cpp -o objects/menu/Menu.o

objects/market/Market.o : src/market/Market.cpp src/market/Market.h src/items/Item.h src/spells/Spell.h \
			     src/menu/Menu.h
	$(CC) $(CFLAGS) -c src/market/Market.cpp -o objects/market/Market.o

objects/random/Random.o : src/random/Random.cpp src/random/Random.h
	$(CC) $(CFLAGS) -c src/random/Random.cpp -o objects/random/Random.o

objects/items/Item.o : src/items/Item.cpp src/items/Item.h
	$(CC) $(CFLAGS) -c src/items/Item.cpp -o objects/items/Item.o

objects/items/Weapon.o : src/items/Weapon.cpp src/items/Weapon.h src/items/Item.h
	$(CC) $(CFLAGS) -c src/items/Weapon.cpp -o objects/items/Weapon.o

objects/items/Armor.o : src/items/Armor.cpp src/items/Armor.h src/items/Item.h
	$(CC) $(CFLAGS) -c src/items/Armor.cpp -o objects/items/Armor.o

objects/items/Potion.o : src/items/Potion.cpp src/items/Potion.h src/items/Item.h
	$(CC) $(CFLAGS) -c src/items/Potion.cpp -o objects/items/Potion.o

objects/spells/Spell.o : src/spells/Spell.cpp src/spells/Spell.h
	$(CC) $(CFLAGS) -c src/spells/Spell.cpp -o objects/spells/Spell.o

objects/spells/FireSpell.o : src/spells/FireSpell.cpp src/spells/FireSpell.h src/spells/Spell.h
	$(CC) $(CFLAGS) -c src/spells/FireSpell.cpp -o objects/spells/FireSpell.o

objects/spells/IceSpell.o : src/spells/IceSpell.cpp src/spells/IceSpell.h src/spells/Spell.h
	$(CC) $(CFLAGS) -c src/spells/IceSpell.cpp -o objects/spells/IceSpell.o

objects/spells/LightningSpell.o : src/spells/LightningSpell.cpp src/spells/LightningSpell.h src/spells/Spell.h
	$(CC) $(CFLAGS) -c src/spells/LightningSpell.cpp -o objects/spells/LightningSpell.o

objects/livings/Living.o : src/livings/Living.cpp src/livings/Living.h src/grid/Grid.h
	$(CC) $(CFLAGS) -c src/livings/Living.cpp -o objects/livings/Living.o

objects/livings/Hero.o : src/livings/Hero.cpp src/livings/Hero.h src/livings/Living.h \
			   src/menu/Menu.h src/grid/Grid.h src/exceptions/heroExceptions.h \
			   src/items/Item.h src/items/Weapon.h src/items/Armor.h src/items/Potion.h \
			   src/spells/Spell.h src/market/Market.h
	$(CC) $(CFLAGS) -c src/livings/Hero.cpp -o objects/livings/Hero.o

objects/livings/Monster.o : src/livings/Monster.cpp src/livings/Monster.h src/livings/Living.h
	$(CC) $(CFLAGS) -c src/livings/Monster.cpp -o objects/livings/Monster.o

objects/livings/heroes/Warrior.o : src/livings/heroes/Warrior.cpp src/livings/heroes/Warrior.h \
				      src/livings/Hero.h src/livings/Living.h src/inventory/Inventory.h \
				      src/menu/Menu.h
	$(CC) $(CFLAGS) -c src/livings/heroes/Warrior.cpp -o objects/livings/heroes/Warrior.o

objects/livings/heroes/Paladin.o : src/livings/heroes/Paladin.cpp src/livings/heroes/Paladin.h \
				      src/livings/Hero.h src/livings/Living.h src/inventory/Inventory.h \
				      src/menu/Menu.h
	$(CC) $(CFLAGS) -c src/livings/heroes/Paladin.cpp -o objects/livings/heroes/Paladin.o

objects/livings/heroes/Sorcerer.o : src/livings/heroes/Sorcerer.cpp src/livings/heroes/Sorcerer.h \
				      src/livings/Hero.h src/livings/Living.h src/inventory/Inventory.h \
				      src/menu/Menu.h
	$(CC) $(CFLAGS) -c src/livings/heroes/Sorcerer.cpp -o objects/livings/heroes/Sorcerer.o

objects/livings/monsters/Dragon.o : src/livings/monsters/Dragon.cpp src/livings/monsters/Dragon.h \
					src/livings/Monster.h src/livings/Living.h
	$(CC) $(CFLAGS) -c src/livings/monsters/Dragon.cpp -o objects/livings/monsters/Dragon.o

objects/livings/monsters/Spirit.o : src/livings/monsters/Spirit.cpp src/livings/monsters/Spirit.h \
					src/livings/Monster.h src/livings/Living.h
	$(CC) $(CFLAGS) -c src/livings/monsters/Spirit.cpp -o objects/livings/monsters/Spirit.o

objects/livings/monsters/Exoskeleton.o : src/livings/monsters/Exoskeleton.cpp src/livings/monsters/Exoskeleton.h \
				             src/livings/Monster.h src/livings/Living.h
	$(CC) $(CFLAGS) -c src/livings/monsters/Exoskeleton.cpp -o objects/livings/monsters/Exoskeleton.o
