#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N; cin >> N;

  vector<int> A(N), B(N);
  for (auto& a: A) {
    cin >> a;
  }
  for (auto& b: B) {
    cin >> b;
  }

  vector<vector<int>> dp(A.size() + 1, vector<int>(B.size() + 1, 0));

  for (int a = 1; a <= A.size(); ++a) {
    for (int b = 1; b <= B.size(); ++b) {
      if (A[a - 1] == B[b - 1]) {
        dp[a][b] = dp[a - 1][b - 1] + 1;
      } else {
        dp[a][b] = max(dp[a - 1][b], dp[a][b - 1]);
      }
    }
  }

  cout << dp[A.size()][B.size()];
}