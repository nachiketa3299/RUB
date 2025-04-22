#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  string A, B, C; cin >> A >> B >> C;

  vector<vector<vector<int>>> dp(
    A.size() + 1, vector<vector<int>>(
      B.size() + 1, vector<int>(
        C.size() + 1, 0
      )
    )
  );

  for (int a = 1; a <= A.size(); ++a) {
    for (int b = 1; b <= B.size(); ++b) {
      for (int c = 1; c <= C.size(); ++c) {
        if (A[a - 1] == B[b - 1] && B[b - 1] == C[c - 1]) {
          dp[a][b][c] = dp[a - 1][b - 1][c - 1] + 1;
        } else {
          dp[a][b][c] = max({dp[a - 1][b][c], dp[a][b - 1][c], dp[a][b][c - 1]});
        }
      }
    }
  }

  cout << dp[A.size()][B.size()][C.size()];
}