// heroExceptions.h --- 
// 
// Filename: heroExceptions.h
// Author: George Liontos
// Created: Fri Jan  5 12:08:21 2018 (+0200)

#if !defined(__HERO_EXCEPTION_HEADER__)
#define __HERO_EXCEPTION_HEADER__

#include <string>

using namespace std;

class HeroMoveException {
public:
  HeroMoveException(const string& message);
  string getMessage();
private:
  string message;
};

#endif
