#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <algorithm>

using namespace std;

struct Trie {
  struct Node {
    unordered_map<char, unique_ptr<Node>> children;
    bool isEnd{false};
  };

  bool InsertAndTest(const string& number) {
    Node* node{root.get()};

    for (char c: number) {
      if (node->children.find(c) == node->children.cend()) {
        node->children[c] = make_unique<Node>();

      }

      node = node->children[c].get();

      if (node->isEnd) {
        return false;
      }
    }

    node->isEnd = true;

    // 다음 노드가 존재함? - 얘는 접두사로서 완전 흡수됐음
    if (!node->children.empty()) {
      return false;
    }

    return true;
  }

  unique_ptr<Node> root{make_unique<Node>()};
};

int main() {

  int t; cin >> t;

  for (int tc = 0; tc < t; ++tc) {
    int n; cin >> n;
    vector<string> numbers(n);

    Trie trie;
    bool isConsistent{true};

    for (string& number: numbers) {
  cin >> number;
}
sort(numbers.begin(), numbers.end());  // 정렬 추가

for (const string& number: numbers) {
  isConsistent &= trie.InsertAndTest(number);
}

    cout << (isConsistent ? "YES" : "NO") << '\n';
  }
}