#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<pair<int, int>>> tree;
constexpr int NO_PARENT = -1;

int dfs_max_path(int c_n_idx, int p_n_idx) {
  int first = 0, second = 0;

  for (const auto& [w, a_n_idx]: tree[c_n_idx]) {
    if (a_n_idx == p_n_idx) {
      continue;
    }

    int child_sum = dfs_max_path(a_n_idx, c_n_idx) + w;

    if (child_sum > first) {
      second = first;
      first = child_sum;
    } else if (child_sum > second) {
      second = child_sum;
    }
  }
  return first;
}

int main() {
  cin >> n;
  tree.resize(n + 1);
  for (int i = 1; i <= n - 1; ++i) {
    int p, c, w; 
    cin >> p >> c >> w;

    tree[p].push_back({w, c});
    tree[c].push_back({w, p});
  }

  int radius = 0;

  for (int i = 1; i <= n; ++i) {
    radius = max(radius, dfs_max_path(i, NO_PARENT));
  }

  cout << radius;
}