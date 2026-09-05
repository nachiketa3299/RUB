#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define V_MIN 1
#define C_MIN 2

bool is_vowel(char c) {
  switch (c) {
    case 'a': case 'e': case 'u': case 'i': case 'o':
      return true;
    default:
      return false;
  }
}

void gen_print(
  const vector<char>& letters, int idx, int size, 
  vector<char>& buff, int vcount, int ccount
) {
  // Pruning
  if (vcount + C_MIN > size) return;
  if (ccount + V_MIN > size) return;

  if (buff.size() == size) {
    for (const auto& c: buff) {
      cout << c;
    }
    cout << '\n';
    return;
  }

  for (int i = idx; i < letters.size(); ++i) {
    const char& c = letters[i];
    buff.push_back(c);

    if (is_vowel(c)) 
      gen_print(letters, i + 1, size, buff, vcount + 1, ccount);
    else      
      gen_print(letters, i + 1, size, buff, vcount, ccount + 1);

    buff.pop_back(); // Backtracking
  }
}

int main() {
  int L, C; cin >> L >> C;

  vector<char> letters(C);
  for (auto& letter: letters) {
    cin >> letter;
  }

  sort(letters.begin(), letters.end());
  vector<char> buff; buff.reserve(L);

  gen_print(letters, 0, L, buff, 0, 0);
}