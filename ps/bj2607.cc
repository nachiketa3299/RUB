#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int n;
vector<string> words;

int main() {
  cin >> n; // 100개
  words.reserve(n);

  for (int i = 0; i < n; ++i) {
    string word; cin >> word; // 10 이하
    words.push_back(word);
  }

  auto make_map = [](const string& str) {
    map<char, int> word;
    for (const char& c: str) {
      ++word[c];
    }
    return word;
  };

  // 첫 번째 단어와 비슷한 단어 몇 개?
  int count = 0;

  map<char, int> fword = make_map(words.front());

  for (int i = 1; i < words.size(); ++i) {
    map<char, int> word = make_map(words[i]);

    map<char, int> l, r;

    for (const auto& [key, val]: fword) {
      if (word.find(key) == word.cend()) {
        l[key] = val;
        continue;
      }

      if (val == word[key]) {
        continue;
      }

      if (val > word[key]) {
        l[key] = val - word[key];
      }
    }

    for (const auto& [key, val]: word) {
      if (fword.find(key) == fword.cend()) {
        r[key] = val;
        continue;
      }

      if (val == fword[key]) {
        continue;
      }

      if (val > fword[key]) {
        r[key] =  val - fword[key];
      }
    }

    if (l.empty() && r.empty()) {
      ++count;
    }
    else if (l.size() == 1 && r.size() == 1) {
      if((*l.cbegin()).second == 1 && (*r.cbegin()).second == 1) {
        ++count; 
      }
    }
    else if (l.size() == 0 && r.size() == 1) {
      if ((*r.cbegin()).second == 1) {
        ++count;
      }
    } else if (l.size() == 1 && r.size() == 0) {
      if ((*l.cbegin()).second == 1) {
        ++count;
      }
    }
  }
  cout << count;
}