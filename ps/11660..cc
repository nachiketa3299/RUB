#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
  // 입력
  int N, M; cin >> N >> M;
  vector<vector<int>> board(N + 1, vector<int>(N + 1));

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      cin >> board[i][j];
    }
  }

  vector<pair<pair<int, int>, pair<int, int>>> ranges(M + 1);
  for (int i = 1; i <= M; ++i) {
    auto& [start, end] = ranges[i];
    cin >> start.first >> start.second;
    cin >> end.first >> end.second;
  }

  for (int i = 1; i <= M; ++i) {
    const auto& [start, end] = ranges[i];

    const auto& [x1, y1] = start;
    const auto& [x2, y2] = end;

    int sum = 0;

    for (int v = x1; v <= x2; ++v) {
      int sub_sum 
        = accumulate(board[v].cbegin() + 1, board[v].cbegin() + y2 - y1 + 2, 0);

      for (int h = 2; h <= y1; ++h) {
        int to_sub = board[v][h - 1];
        int to_add = board[v][h + y2 - y1];
        sub_sum = sub_sum - to_sub + to_add;
      }

      sum += sub_sum;
    }

    cout << sum << '\n';
  }
}