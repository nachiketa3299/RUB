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
  // 일단 자기 자신의 값으로 초기화 해 두고 (dpi = v0)
  dp[n_idx] = node_vals[n_idx];

  // 자손이 있다면 있는 대로 순회
  // 만일 자손이 없으면(리프 노드), dpi = v0
  for (const int& c_idx: tree[n_idx]) {
    // 부모는 필요 없음
    if (c_idx == p_idx) {
      continue;
    }

    // 자식의 값을 갱신할 수 있을 때까지 타고 내려가서 갱신
    tree_dfs(c_idx, n_idx);

    dp[n_idx] += max(0ll, dp[c_idx]); // (dpi = v0 + dpc0 + dpc1 ...)
  }
}

int main() {
  cin >> n;

  node_vals.resize(n);
  tree.resize(n);
  dp.resize(n);

  // 간선 입력
  for (int i = 0; i < n - 1; ++i) {
    int p, c; cin >> p >> c;

    tree[p].push_back(c);
    tree[c].push_back(p);
  }

  // 노드 값 입력
  for (int i = 0; i < n; ++i) {
    cin >> node_vals[i];
  }

  // dp 배열 채우기
  tree_dfs(0, NO_PARENT);

  // 출력
  cout << dp[0];
}