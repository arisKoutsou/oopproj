CC = g++
CFLAGS = -Wall -ggdb

bin: grid.o item.o living.o main.o market.o spell.o 
	$(CC) $(CFLAGS) grid.o item.o living.o main.o market.o spell.o -o fake_diablo 

grid.o : grid.cpp grid.h 
	$(CC) $(CFLAGS) -c grid.cpp 

item.o : item.cpp item.h 
	$(CC) $(CFLAGS) -c item.cpp 

living.o : living.cpp living.h 
	$(CC) $(CFLAGS) -c living.cpp 

main.o : main.cpp 
	$(CC) $(CFLAGS) -c main.cpp 

market.o : market.cpp market.h spell.h item.h living.h 
	$(CC) $(CFLAGS) -c market.cpp 

spell.o : spell.cpp spell.h 
	$(CC) $(CFLAGS) -c spell.cpp 

.PHONY : clear

clear :
	rm -f fake_diablo grid.o item.o living.o main.o market.o spell.o 


#Generated with makefile generator: https://github.com/GeorgeLS/Makefile-Generator/blob/master/mfbuilder.c
