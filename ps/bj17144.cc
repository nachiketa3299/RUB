#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define AC -1


int R, C, T;
vector<vector<int>> board;
pair<int, int> ac_poss[2];
int ac_idx = 0;

int main() {
  cin >> R >> C >> T;
  board = vector<vector<int>>(R, vector<int>(C));

  for (int r = 0; r < board.size(); ++r) {
    for (int c = 0; c < board[r].size(); ++c) {
      cin >> board[r][c];

      // 청정기 위치 기록
      if (board[r][c] == AC) {
        ac_poss[ac_idx++] = {r, c};
      }
    }
  }

  auto get_adj_spread_poss = [](const pair<int, int>& pos) {
    static int dx[]{0, 0, -1, 1}, dy[]{1, -1, 0, 0};
    vector<pair<int, int>> ret; 
    ret.reserve(4);
    for (int i = 0; i < 4; ++i) {
      int nx = pos.first + dx[i];
      int ny = pos.second + dy[i];

      if (nx < 0 || nx >= R || ny < 0 || ny >= C) {
        continue;
      }
      pair<int, int> pos{nx, ny};

      // 청정기 위치로는 확산하지 않음
      if (pos == ac_poss[0] || pos == ac_poss[1]) {
        continue;
      }

      ret.push_back(pos);
    }
    return ret;
  };

  for (int t = 0; t < T; ++t) {
    vector<vector<int>> offsets = vector<vector<int>>(R, vector<int>(C, 0));
    offsets[ac_poss[0].first][ac_poss[0].second] = AC;
    offsets[ac_poss[1].first][ac_poss[1].second] = AC;

    // spread
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        if (board[r][c] == 0 || board[r][c] == AC) {
          continue;
        }

        pair<int, int> c_spread_pos{r, c};

        vector<pair<int, int>> adj_spread_poss
          = get_adj_spread_poss(c_spread_pos);
        
        int per_spread_amount = board[r][c] / 5;
        for (const auto& [x, y]: adj_spread_poss) {
          offsets[x][y] += per_spread_amount;

          offsets[r][c] -= per_spread_amount;
          if (offsets[r][c] + board[r][c] < 0) {
            offsets[r][c] = -board[r][c];
          }
        }
      }
    }

    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        if (board[r][c] == AC) {
          continue;
        }
        board[r][c] += offsets[r][c];
      }
    }

    // vent

    // upper vent
    for (int i = ac_poss[0].first - 1; i >= 0; --i) {
      if (board[i + 1][0] != AC) {
        board[i + 1][0] = board[i][0];
      } 

      board[i][0] = 0;
    }

    for (int j = 1; j < C; ++j) {
      board[0][j - 1]  = board[0][j];
      board[0][j] = 0;
    }

    for (int i = 1; i <= ac_poss[0].first; ++i) {
      board[i - 1][C - 1] = board[i][C - 1];
      board[i][C - 1] = 0;
    }

    for (int j = C - 2; j >= 0; --j) {
      if (board[ac_poss[0].first][j - 1] != AC) {
        board[ac_poss[0].first][j - 1] = board[ac_poss[0].first][j];
      }
      board[ac_poss[0].first][j] = 0;
    }

    // lower vent
    for (int i = ac_poss[1].first + 1; i < R; ++i) {
      if (board[i - 1][0] != AC) {
        board[i - 1][0] = board[i][0];
      }
      board[i][0] = 0;
    }

    for (int j = 1; j < C; ++j) {
      board[0][j - 1] = board[0][j];
      board[0][j] = 0;
    }

    for (int i = R - 2; i >= ac_poss[1].first; --i) {
      board[i - 1][C - 1] = board[i][C - 1];
      board[i][C - 1] = 0;
    }

    for (int j = C - 2; j >= 0; --j) {
      if (board[ac_poss[1].first][j - 1] != AC) {
        board[ac_poss[1].first][j - 1] = board[ac_poss[1].first][j];
      }
      board[ac_poss[1].first][j] = 0;
    }
  }

  int count = 0;
  for (int r = 0; r < R; ++r) {
    for (int c = 0; c < C; ++c) {
      count += board[r][c];
    }
  }

  cout << count;
}