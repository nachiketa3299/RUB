#include "Singleton.h"

Singleton *Singleton::Instance() {
  if (instance == nullptr) 
    instance = new Singleton();

  return instance;
}

Singleton *Singleton::instance = nullptr;