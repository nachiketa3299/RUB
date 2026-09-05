#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

#define IMPOSSIBLE "Impossible"s
#define B_SIZE 8
#define NO_PARENT pair<int, int>(-1, -1)

int main() {
  int T; cin >> T;
  for (int tc = 0; tc < T; ++tc) {
    char Xv, Yv;
    int Xh, Yh;
    cin >> Xv >> Xh >> Yv >> Yh;

    const pair<int, int> start{Xv - 'A', Xh - 1};
    const pair<int, int> end{Yv - 'A', Yh - 1};

    // 1. 시작점과 끝점이 같은 경우
    if (start == end) {
      cout << 0 << ' ' << static_cast<char>(start.first + 'A') << ' ' << start.second + 1 << '\n';
      continue;
    }

    // 2. 시작점과 끝점의 색깔이 다른 경우
    if ((start.first + start.second) % 2 != (end.first + end.second) % 2) {
        cout << IMPOSSIBLE << "\n";
        continue;
    }

    // 3. 탐색이 필요한 경우

    queue<pair<int, int>> to_visit;
    to_visit.push(start);
    vector<vector<pair<int, int>>> parent(B_SIZE, vector<pair<int, int>>(B_SIZE, NO_PARENT));
    vector<vector<int>> dists(B_SIZE, vector<int>(B_SIZE, INT_MAX));

    parent[start.first][start.second] = NO_PARENT;
    dists[start.first][start.second] = 0;

    auto get_adj_poss = [](const pair<int, int>& pos) {
      vector<pair<int, int>> ret;
      auto is_valid = [](int v, int h) {
        return v >= 0 && v < B_SIZE && h >= 0 && h < B_SIZE;
      };
      // 오른쪽 아래 대각선
      for (int off = 1; is_valid(pos.first + off, pos.second + off); ++off) {
        ret.push_back({pos.first + off, pos.second + off});
      }
      // 왼쪽 아래 대각선
      for (int off = 1; is_valid(pos.first - off, pos.second + off); ++off) {
        ret.push_back({pos.first - off, pos.second + off});
      }
      // 오른쪽 위 대각선
      for (int off = 1; is_valid(pos.first + off, pos.second - off); ++off) {
        ret.push_back({pos.first + off, pos.second - off});
      }
      // 왼쪽 위 대각선
      for (int off = 1; is_valid(pos.first - off, pos.second - off); ++off) {
        ret.push_back({pos.first - off, pos.second - off});
      }
      return ret;
    };

    // 4. BFS 시작
    bool found = false;
    while (!to_visit.empty()) {
      pair<int, int> cv = to_visit.front();
      to_visit.pop();

      if (cv == end) {
        found = true;
        break;
      }

      if (dists[cv.first][cv.second] >= 4) {
        continue;
      }

      // 인접 위치 탐색
      for (const pair<int, int>& av: get_adj_poss(cv)) {
        if (dists[av.first][av.second] != INT_MAX) {
          continue;
        }

        dists[av.first][av.second] = dists[cv.first][cv.second] + 1;
        parent[av.first][av.second] = cv;

        to_visit.push(av);
      }
    }

    // 5. 결과 출력
    if (found) {
      // 경로 뒤집기
      vector<pair<int, int>> path;
      pair<int, int> curr = end;
      while (curr != NO_PARENT) {
          path.push_back(curr);
          curr = parent[curr.first][curr.second];
      }
      reverse(path.begin(), path.end());

      cout << path.size() - 1 << ' ';
      for (int i = 0; i < path.size(); ++i) {
        const auto& [v, h] = path[i];
        cout << static_cast<char>(v + 'A') << ' ';
        cout << h + 1;
        if (i < path.size() - 1) { 
          cout << ' ';
        }
      }
      cout << '\n';
    } else {
      cout << IMPOSSIBLE << "\n";
    }
  }
  return 0;
}