// heroExceptions.cpp --- 
// 
// Filename: heroExceptions.cpp
// Author: George Liontos
// Created: Fri Jan  5 12:08:33 2018 (+0200)

#include <iostream>
#include <string>

#include "../../include/heroExceptions.h"

using namespace std;

HeroMoveException :: HeroMoveException(const string& _message)

  :message(_message) {}

HeroMoveException :: ~HeroMoveException() throw() {}

const char* HeroMoveException :: what() const throw() {
  return message.c_str();
}
