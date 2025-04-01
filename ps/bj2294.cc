#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> coin_vals;
vector<int> dp;

// 그러면서, 동전의 갯수가 최소

int main() {
  cin >> n >> k;

  coin_vals.reserve(n);
  for (int i = 0; i < n; ++i) {
    int coin_val; cin >> coin_val;
    coin_vals.push_back(coin_val);
  }

  dp = vector<int>(k + 1, 0);
  dp[0] = 0;

  for (int c = 1; c <= k; ++c) {
    vector<int> candid;

    for (const int& coin_val: coin_vals) {
      if (coin_val > c) {
        continue;
      }

      candid.push_back(dp[c - coin_val]);
    }

    auto min_elem = min_element(candid.cbegin(), candid.cend());
    int min = min_elem == candid.cend() ? -1 : *min_elem + 1;

    dp[c] = min;
  }

  cout << dp[k];
}