#include <iostream>
#include <vector>

using namespace std;

void _perm_dfs(const vector<int>& seq, int size, vector<int>& path, vector<bool>& used) {
  if (path.size() == size) {
    for (const auto& e: path) {
      cout << e << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = 0; i < used.size(); ++i) {
    if (used[i]) continue;

    path.push_back(seq[i]);
    used[i] = true;

    _perm_dfs(seq, size, path, used);

    path.pop_back();
    used[i] = false;
  }
}

void perm(const vector<int>& seq, int size) {
  vector<int> path; path.reserve(size);
  vector<bool> used(seq.size(), false);

  _perm_dfs(seq, size, path, used);
}

void _comb_dfs(const vector<int>& seq, int size, vector<int>& path, int start) {
  if (path.size() == size) {
    for (const auto& e: path) {
      cout << e << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = start; i < seq.size(); ++i) {
    path.push_back(seq[i]);
    _comb_dfs(seq, size, path, i + 1);
    path.pop_back();
  }
}

void comb(const vector<int>& seq, int size) {
  vector<int> path; path.reserve(size);

  _comb_dfs(seq, size, path, 0);
}

int main() {
  vector<int> seq { 1, 2, 3, 4, 5, 6 };
  cout << "* Permutation:\n";
  perm(seq, 3);

  cout << "* Combination:\n";
  comb(seq, 3);
}
