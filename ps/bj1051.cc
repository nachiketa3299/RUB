#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;
  cin.ignore();

  vector<vector<int>> rec(N, vector<int>(M));

  for (int i = 0; i < N; ++i) {
    string line;
    getline(cin, line);

    for (int j = 0; j < M; ++j) {
      rec[i][j] = line[j] - '0';
    }
  }

  int max_size = INT_MIN;

  for (int s = 1; s <= min(N, M); ++s) {

    for (int i = 0; i < N - s + 1; ++i) {
      for (int j = 0; j < M - s + 1; ++j) {
        if (
          rec[i][j] == rec[i + s - 1][j] &&
          rec[i][j] == rec[i][j + s - 1] &&
          rec[i][j] == rec[i + s - 1][j + s - 1]
        ) {
          max_size = max(max_size, s);
        }
      }
    }

  }

  cout << max_size * max_size;
}