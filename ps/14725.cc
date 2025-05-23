#include <vector>
#include <iostream>
#include <map>
#include <string>

using namespace std;

struct Trie {
  struct Node {
    map<string, Node*> children;
    bool isEnd{false};
  };

  void Insert(const vector<string>& words) const {
    Node* node{root_};
    for (const string& word: words) {
      if (node->children.find(word) == node->children.cend()) {
        node->children[word] = new Node();
      }
      node = node->children[word];
    }
    node->isEnd = true;
  } 

  void PrintTree() const {
    DFS(root_, 0);
  }

  void DFS(const Node* node, int indentLevel) const {
    for (const auto& [word, child]: node->children) {
      for (int i = 0; i < indentLevel; ++i) {
        cout << "--";
      }
      cout << word << '\n';
      DFS(child, indentLevel + 1);
    }
  }

  Node* root_{new Node()};
};

int main() {
  int N; cin >> N;

  Trie trie;

  for (int i = 0; i < N; ++i) {
    int K; cin >> K;
    vector<string> strs(K);
    for (string& str: strs) {
      cin >> str;
    }
    trie.Insert(strs);
  }

  trie.PrintTree();
}