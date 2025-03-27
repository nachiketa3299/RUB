#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
template <typename T>
void printv(const vector<T>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    cout << vec[i] << ' ';
  }
}

int main() {
  vector<char> vec {'a', 'b', 'a'};

  cout << "Printing Normal: ";
  printv(vec);
  cout << '\n';

  int counter = 0;

  do {
    cout << "Counter: " << counter << ": ";
    printv(vec);
    cout << '\n';
    ++counter;
  } while (next_permutation(vec.begin(), vec.end()));
}