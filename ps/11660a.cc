#include <iostream>
#include <vector>

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

  vector<vector<int>> sum(N + 1, vector<int>(N + 1, 0));

  for (int v = 1; v <= N; ++v) {
    for (int h = 1; h <= N; ++h) {
      sum[v][h] = board[v][h] + sum[v - 1][h] + sum[v][h - 1] - sum[v - 1][h - 1];
    }
  }

  for (int i = 1; i <= M; ++i) {
    const auto& [start, end] = ranges[i];
    const auto& [x1, y1] = start;
    const auto& [x2, y2] = end;

    int total = sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
    cout << total << '\n';
  }
}