#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string EMPTY = "FRULA";

int main() {
  // [1, 10^6]
  string str; cin >> str; 

  // [1, 36]
  string boom_str; cin >> boom_str; 

  size_t pos;

  do {
    pos = str.find(boom_str);

    if (pos != string::npos) {
      str.erase(pos, boom_str.length());
    }

  } while (pos != string::npos);

  if (str.empty()) {
    cout << EMPTY;
  } else {
    cout << str;
  }
}