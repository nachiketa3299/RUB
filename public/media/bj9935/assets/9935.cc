#include <iostream>
#include <string>

using namespace std;

int main() {
  // [1, 10^6]
  string str; cin >> str;

  // [1, 36]
  string boom_str; cin >> boom_str;

  string result;

  for (char ch: str) {
    result += ch;

    if (result.length() < boom_str.length()) {
      continue;
    }

    if (result.back() != boom_str.back()) {
      continue;
    }

    bool match = true;
    size_t pos = result.length() - boom_str.length();

    // 이건 사실 result.substr(pos) 
    for (size_t i = 0; i < boom_str.length(); ++i) {
      if (result[i + pos] != boom_str[i]) {
        match = false;
        break;
      }
    }

    if (!match) {
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