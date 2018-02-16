1) Project contributors:
	•Aris Koutsouridis (1115201600078)
	•George Liontos (1115201600094)

2) In order to compile the compile just use the included makefile (write make).

==================================WARNING(!)===============================

The makefile uses the shell program "find" in order to compile the program
so make sure you create a directory and put all the files into that directory
and then run the command "make".

===========================================================================

3) To run the program just type "./game" and you're ready to go.

==================================WARNING(!)===============================

The game reads some files in order to work properly. These files are in the
"input" directory provided with the .zip you got. Make sure you have the
"input" directory at the same directory level of the executable.

===========================================================================

4-5) We mostly followed the given information about the project. The items,
spells are designed according to the information. The Livings are designed
based on the given information but we have added more things to it. We have
assumed that the Hero will handle the options of every menu, heroes have
a structure that represents their position on the map and that they have
a structure that represents the inventory. All the things a hero has in his
inventory can only be equiped, sold, discarded and used (only for potions).
The hero has some extra data which is the currently equiped weapons, spells(3)
and potions in use. The Grid is a 2D vector of Tiles. A tile is a structure that
holds information such as if the tile is non accessible, has a market, a hero or
a battle can occur (we assumed that common tiles are the tiles which a battle can occur).
We have added an exception which is thrown when a hero tries to go out of bounds.
Furthermore, we have added an Inventory class, a Market class(they are much alike)
which hold the items and spells a hero can buy/sell/have/discard. Finally we have made a
Menu class from which derive specific menus. These menus have the options a hero can choose
from such as battle options, basic options, inventory options etc.
