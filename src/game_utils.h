// game_utils.h --- 
// 
// Filename: game_utils.h
// Author: George Liontos
// Created: Sun Jan 28 02:35:37 2018 (+0200)

#if !defined(__GAME_UTILS_HEADER__)
#define __GAME_UTILS_HEADER__

#include <iostream>
#include <fstream>
#include <vector>
#include <list>

#include "random/Random.h"

// NOTE (George): These numbers are just for testing
#define MIN_MONSTERS 1
#define MAX_MONSTERS 1

using namespace std;

class Hero;
class Monster;
class Grid;

extern const Random rng;
extern vector<Hero*> heroes;
extern vector<string> names;
extern vector<string> weapons;
extern vector<string> armors;
extern vector<string> potions;
extern vector<string> spells;
extern list<Monster*> monsters;
extern Grid* gameGrid;
extern bool quitGame;

void initGrid(void);
void initGrid(ifstream& stream);
bool isCommentOrWhitespace(const string& str);
void skipCommentsAndWhitespace(ifstream& stream);
void tokenize(vector<string>& tokens);
void createHeroes(int numberOfHeroes);
void handleMoveCase(Hero* currentHero);
void handleQuitCase(void);
void handleBasicCase(Hero* currentHero);
void handleBattleCase(void);
void createMonsters(void);
void claimRewards(void);
void receivePenalty(void);
void restoreHeroes(void);
void cleanupMonsters(void);
bool heroesWon(void);
bool monstersWon(void);
int heroesAlive(void);
void readData(int argc, char* argv[]);
void readSpecificData(ifstream& stream, vector<string>& data);

#endif
