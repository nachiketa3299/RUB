#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int main() {
  int N; cin >> N; // [10^6]

  vector<ll> dp(N + 1);

  dp[0] = 1; 
  dp[1] = 0;

  for (int n = 2; n <= N; ++n) {
    dp[n] = (n - 1) * (dp[n - 1] + dp[n - 2]) % 1'000'000'000ll;
  }

  cout << dp[N];
}