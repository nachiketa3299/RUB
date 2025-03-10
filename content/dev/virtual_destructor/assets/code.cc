#include <iostream>


class Super {
public:
  int i_;
};

class Derived: public Super {
public:
  Derived(): i_(10) {}
  double d_;
};

int main() {
  Derived d;
}