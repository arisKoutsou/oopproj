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
#define MIN_MONSTERS 3
#define MAX_MONSTERS 10

using namespace std;

class Hero;
class Monster;
class Grid;
class Market;

extern bool quitGame;
extern void handleQuitCase(void);

void generateMap();
void initGrid(void);
bool isCommentOrWhitespace(const string& str);
void skipCommentsAndWhitespace(ifstream& stream);
void tokenize(vector<string>& tokens);
void createHeroes(int numberOfHeroes);
void handleMoveCase(Hero* currentHero);
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
void readData(void);
void readSpecificData(ifstream& stream, vector<string>& data);
void regenerateStats(void);
void checkArgumentsAndSetMap(void);
int getNumberOfHeroes(void);
void cleanupResources(void);
void fillMarket(Market* market);
void updatePotionsAndNerfs(void);
void run(void);
void printHeroFrame(void);
void printMonsterFrame(void);
int getDigits(int n);
void clearScreen(void);

#endif



