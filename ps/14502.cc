#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

enum bstate {NONE = 0, WALL = 1, VIRUS = 2};
int N, M;  // N, M in [3, 8]
vector<vector<bstate>> board;
vector<pair<size_t, size_t>> none_poss;

struct bt_comb {
  bt_comb(const vector<pair<size_t, size_t>>& seq): _seq(seq) {}
  vector<array<pair<size_t, size_t>, 3>> operator()() {
    array<pair<size_t, size_t>, 3> path;
    _bt_comb(path, 0, 0);
    return ret;
  }

  void _bt_comb(array<pair<size_t, size_t>, 3>& path, int start, int a_idx) {
    if (a_idx == 3) {
      ret.push_back(path);
      return;
    }

    for (int i = start; i < _seq.size(); ++i) {
      path[a_idx] = _seq[i];
      _bt_comb(path, i + 1, a_idx + 1);
    }
  }
private:
  const vector<pair<size_t, size_t>>& _seq;
  vector<array<pair<size_t, size_t>, 3>> ret;
};

bool is_valid_pos(const pair<size_t, size_t>& pos) {
  return  (0 <= pos.first && pos.first < N) && (0 <= pos.second && pos.second < M);
}

vector<pair<size_t, size_t>> get_adj_none_poss(const vector<vector<bstate>>& cboard, const pair<size_t, size_t>& pivot) {
  static const vector<pair<size_t, size_t>> offsets {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  vector<pair<size_t, size_t>> ret;

  for (const auto& [dv, dh]: offsets) {
    pair<size_t, size_t> npos{pivot.first + dv, pivot.second + dh};

    if (!is_valid_pos(npos) || cboard[npos.first][npos.second] != NONE) {
      continue;
    }

    ret.push_back(npos);
  }

  return ret;
}

int main() {
  cin >> N >> M;
  board = vector<vector<bstate>>(N, vector<bstate>(M));
  for (int n = 0; n < N; ++n) {
    for (int m = 0; m < M; ++m) {
      int val; cin >> val;
      board[n][m] = static_cast<bstate>(val);
      if (board[n][m] == NONE)  {
        none_poss.push_back({n, m});
      }
    }
  }

  vector<array<pair<size_t, size_t>, 3>> combs = bt_comb{none_poss}();

  int max_safe_area_size = 0;

  for (array<pair<size_t, size_t>, 3> comb: combs) {
    vector<vector<bstate>> cboard(board);
    vector<vector<bool>> vvisited(N, vector<bool>(M, false));

    // 벽 세우기
    const auto& [v0, h0] = comb[0];
    const auto& [v1, h1] = comb[1];
    const auto& [v2, h2] = comb[2];

    cboard[v0][h0] = WALL;
    cboard[v1][h1] = WALL;
    cboard[v2][h2] = WALL;

    // 바이러스 전파 시키기
    for (int n = 0; n < N; ++n) {
      for (int m = 0; m < M; ++m) {
        if (cboard[n][m] == VIRUS && !vvisited[n][m]) {
          queue<pair<size_t, size_t>> to_visit;

          to_visit.push({n, m});
          vvisited[n][m] = true;

          while (!to_visit.empty()) {
            pair<size_t, size_t> cpos = to_visit.front();
            to_visit.pop();
            cboard[cpos.first][cpos.second] = VIRUS;

            for (const auto& [av, ah]: get_adj_none_poss(cboard, cpos)) {
              if (vvisited[av][ah]) {
                continue;
              }
              vvisited[av][ah] = true;
              to_visit.push({av, ah});
            }
          }
        }
      }
    }

    // 최대 NONE 개수 세기
    int safe_area_size = 0;

    for (int n = 0; n < N; ++n) {
      for (int m = 0; m < M; ++m) {
          if (cboard[n][m] == NONE) {
            ++safe_area_size;
            max_safe_area_size = max(safe_area_size, max_safe_area_size);
          }
        }
    }

  }
  cout << max_safe_area_size;
}