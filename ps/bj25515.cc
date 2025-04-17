#include <iostream>
#include <vector>
#include <climits>
#include <functional>
#include <algorithm>

using namespace std;
using ll = long long;

int n;
vector<int> node_vals;
vector<vector<int>> tree;
vector<ll> dp;

constexpr int NO_PARENT = -1;

void tree_dfs(int n_idx, int p_idx) {
  // 일단 자기 자신의 값으로 초기화 해 두고
  dp[n_idx] = node_vals[n_idx];

  for (const int& c_idx: tree[n_idx]) {
    if (c_idx == p_idx) {
      continue;
    }

    // 자식의 값을 우선 갱신함
    tree_dfs(c_idx, n_idx);

    dp[n_idx] += max(0ll, dp[c_idx]);
  }
}

int main() {
  cin >> n;
  node_vals.resize(n);
  tree.resize(n);
  dp.resize(n); fill(dp.begin(), dp.end(), LLONG_MIN);

  for (int i = 0; i < n - 1; ++i) {
    int p, c; cin >> p >> c;

    tree[p].push_back(c);
    tree[c].push_back(p);
  }

  for (int i = 0; i < n; ++i) {
    cin >> node_vals[i];
  }

  tree_dfs(0, NO_PARENT);
  cout << dp[0];
}