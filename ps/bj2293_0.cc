#include <iostream>
#include <vector>

using namespace std;

int n, k;
vector<int> coin_vals;
vector<int> dp;

int main() {
  cin >> n >> k; // 10^5

  coin_vals.reserve(n);

  for (int i = 0; i < n; ++i) {
    int coin_val; cin >> coin_val;
    coin_vals.push_back(coin_val);
  }

  dp = vector<int>(k + 1, 0);
  dp[0] = 1;

  for (const int& coin: coin_vals) {
    for (int c = coin; c <= k; ++c) {
      dp[c] += dp[c - coin];
    }
  }

  cout << dp[k];
}