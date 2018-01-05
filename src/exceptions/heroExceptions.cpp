// heroExceptions.cpp --- 
// 
// Filename: heroExceptions.cpp
// Author: George Liontos
// Created: Fri Jan  5 12:08:33 2018 (+0200)

#include <iostream>
#include <string>
#include "heroExceptions.h"

using namespace std;

HeroMoveException :: HeroMoveException(const string& _message)

  :message(_message) {}

string HeroMoveException :: getMessage() {
  return message;
}
