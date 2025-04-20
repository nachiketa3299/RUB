#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n; // 정점의 개수 [1, 10^4]
vector<int> node_vals;
vector<vector<int>> tree;
constexpr int NO_PARENT = -1;

int tree_dfs(int c_n_idx, int p_n_idx) {
  int max_sum = 0;

  for (const int& a_n_idx: tree[c_n_idx]) {
    if (a_n_idx == p_n_idx) {
      continue;
    }

    max_sum = max(max_sum, tree_dfs(a_n_idx, c_n_idx));
  }
  return max_sum + node_vals[c_n_idx];
}

int main() {
  cin >> n;
  node_vals.resize(n);
  for (int& node_val: node_vals) {
    cin >> node_val;
  }
  tree.resize(n);
  for (int i = 0; i < n - 1; ++i) {
    int a, b; cin >> a >> b;
    tree[a - 1].push_back(b - 1);
    tree[b - 1].push_back(a - 1);
  }

  int max_val = 0;
  int s_idx = 0;

  for (int i = 0; i < n; ++i) {
    int total = tree_dfs(i, NO_PARENT);

    if (total > max_val) {
      max_val = total;
      s_idx = i;
    } else if (total == max_val && i < s_idx) {
      s_idx = i;
    }
  }

  cout << max_val << ' ' << s_idx + 1 << '\n';
}