#include <iostream>

struct Foo {
explicit Foo(double x, double y):x_(x),y_(y) {}
double x_, y_;
};

int main() {
  Foo f{10, 10};
  Foo f2(10, 10);
}