class Parent {
public:
  Parent() {}
  ~Parent() {}

private:
  int p = 10;
};

class ChildA {
public:
  ChildA() {}
  ~ChildA() {}

private:
  char arr[10] { 'c' };
};

class ChildB {
public:
  ChildB() {
    vec = new char[10] { 'a' };
  }
  ~ChildB() {
    delete[] vec;
  }

private:
  char *vec;
};

int main() {
  ChildB b0();
  ChildB b1 = ChildB();
}