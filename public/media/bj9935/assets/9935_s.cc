#include <iostream>
#include <string>

using namespace std;

int main() {
  string str, boom_str; cin >> str >> boom_str;
  string result;

  for (char ch: str) {
    result += ch;

    if (result.length() < boom_str.length()) {
      continue;
    }

    if (result.back() != boom_str.back()) {
      continue;
    }

    size_t pos = result.length() - boom_str.length();

    if (result.substr(pos) != boom_str) {
      continue;
    }

    result.erase(pos);
  }

  if (result.empty()) {
    cout << "FRULA";
  } else {
    cout << result;
  }
}
