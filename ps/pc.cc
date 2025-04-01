#include <iostream>
#include <vector>
#include <functional>

using namespace std;

void _perm_dfs(
  const vector<int>& vec, 
  int size, 
  function<void(vector<int>)> fun,
  vector<bool>& used, 
  vector<int>& path
) {
  if (path.size() == size) {
    fun(path);
    return;
  }

  for (int i = 0; i < used.size(); ++i) {
    if (used[i]) {
      continue;
    }

    used[i] = true;
    path.push_back(vec[i]);

    _perm_dfs(vec, size, fun, used, path);

    path.pop_back();
    used[i] = false;
  }
}

void perm(
  const vector<int>& vec, 
  int size, 
  function<void(vector<int>)> fun
) {
  vector<bool> used(vec.size(), false);
  vector<int> path; path.reserve(size);
  _perm_dfs(vec, size, fun, used, path);
}

void _comb_dfs(
  const vector<int>& vec, 
  int size, 
  function<void(vector<int>)> fun,
  int start,
  vector<int>& path
) {
  if (path.size() == size) {
    fun(path);
    return;
  }

  for (int i = start; i < vec.size(); ++i) {
    path.push_back(vec[i]);
    _comb_dfs(vec, size, fun, i + 1, path);
    path.pop_back();
  }
}

void comb(
  const vector<int>& vec, 
  int size, 
  function<void(vector<int>)> fun
) {
  vector<int> path;
  path.reserve(size);
  _comb_dfs(vec, size, fun, 0, path);
}

int main() {
  vector<int> vec {1, 2, 3};

  auto print = [](const auto& vec) {
    for (const auto& e: vec) {
      cout << e << ' ';
    }
    cout << '\n';
  };

  cout << "Permutation:\n";
  perm(vec, 2, print);

  cout << "Combination:\n";
  comb(vec, 2, print);
}