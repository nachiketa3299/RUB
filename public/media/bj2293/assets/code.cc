#include <iostream>
#include <vector>

using namespace std;

int n, k; // n in [1, 10^2] k in [1, 10^4]

vector<int> coins;
vector<int> dp;

int main() {
  cin >> n >> k;
  coins = vector<int>(n);
  for (int i = 0; i < n; ++i) {
    cin >> coins[i]; // [1, 10^5]
  }

  dp = vector<int>(k + 1, 0); // 모두 0으로 초기화
  dp[0] = 1;

  for (const int& coin_val : coins) { 
    for (int i = coin_val; i <= k; ++i) {
      dp[i] += dp[i - coin_val];
    }
  }

  cout << dp[k];

  return 0;
}
