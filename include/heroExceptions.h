// heroExceptions.h --- 
// 
// Filename: heroExceptions.h
// Author: George Liontos
// Created: Fri Jan  5 12:08:21 2018 (+0200)

#if !defined(__HERO_EXCEPTION_HEADER__)
#define __HERO_EXCEPTION_HEADER__

#include <string>
#include <exception>

using namespace std;

class HeroMoveException : public exception {
public:
  HeroMoveException(const string& message);
  virtual ~HeroMoveException() throw();
  const char* what() const throw();
private:
  string message;
};

#endif
