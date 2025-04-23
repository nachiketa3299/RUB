#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;
using ll = long long;

int main() {

  int T; cin >> T;
  for (int tc = 0; tc < T; ++tc) {

    // 입력
    int n; cin >> n;
    vector<long long> s1(n + 1, 0), s2(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      cin >> s1[i];
    }
    for (int i = 1; i <= n; ++i) {
      cin >> s2[i];
    }

    enum state {
      NO=0,  // 아무것도 뜯지 않았을 때
      UP,    // 위쪽만 뜯었을 때
      DO     // 아래쪽만 뜯었을 때
    };

    // i 열에서, NO/UP/DO 판단을 내렸을 때 만들어지는 상태에 대해, i열 까지 각 상태에 대한 최대값
    vector<tuple<ll, ll, ll>> dp(n + 1);

    get<NO>(dp[1]) = 0;
    get<UP>(dp[1]) = s1[1];
    get<DO>(dp[1]) = s2[1];

    for (int i = 2; i <= n; ++i) {
      get<NO>(dp[i]) = max({get<NO>(dp[i - 1]), get<UP>(dp[i - 1]), get<DO>(dp[i - 1])});
      get<UP>(dp[i]) = max({get<NO>(dp[i - 1]),                     get<DO>(dp[i - 1])}) + s1[i];
      get<DO>(dp[i]) = max({get<NO>(dp[i - 1]), get<UP>(dp[i - 1])                    }) + s2[i];
    }

    cout << max({get<NO>(dp[n]), get<UP>(dp[n]), get<DO>(dp[n])}) << '\n';
  }
}