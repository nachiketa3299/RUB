#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
  string A, B;
  cin >> A >> B;
  vector<vector<int>> dp(A.size() + 1, vector<int>(B.size() + 1, 0));

  for (int i = 1; i <= A.size(); ++i) {
    for (int j = 1; j <= B.size(); ++j) {
      if (A[i - 1] == B[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  string lcs;

  int i = A.size(), j = B.size();
  while (i > 0 && j > 0) {
    if (A[i - 1] == B[j - 1]) {
      lcs = A[i - 1] + lcs;
      --i; --j;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }

  cout << dp[A.size()][B.size()] << '\n' << lcs;
}