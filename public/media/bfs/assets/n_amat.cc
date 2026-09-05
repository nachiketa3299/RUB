#include <vector>
#include <queue>

using namespace std;

#define NO_EDGE 1

int const dx[4] = { +1,  0,  0, -1};
int const dy[4] = {  0, +1, -1,  0};

/*!
 * @param graph_amat 인접 행렬 방식으로 구현된 그래프
 * @param sx, sy 시작 정점의 좌표
 * @param tx, ty 종료 정점의 좌표
 */
void bfs_amat(
  vector<vector<int>> const &graph_amat, 
  int sx, int sy, 
  int tx, int ty) {

  int const size_x = graph_amat.front().size();
  int const size_y = graph_amat.size();

  // BFS 초기화 단계
  queue<pair<int, int>> to_visit;
  vector<vector<bool>> visited(
    size_y,
    vector<bool>(size_x, false)
  );

  to_visit.push({sx, sy});
  visited[sy][sx] = true;

  // BFS 실행 단계
  while (!to_visit.empty()) {
    // 현재 정점 처리 단계
    auto const [cx, cy] = to_visit.front();
    to_visit.pop();

    if (cx == tx && cy == ty) return;

    // 인접 정점 탐색 단계
    for (int i = 0; i < 4; ++i) {
      int ax = cx + dx[i];
      int ay = cy + dy[i];

      if (ax < 0 || ax >= size_x) continue;
      if (ay < 0 || ay >= size_y) continue;

      if (graph_amat[ay][ax] == NO_EDGE) continue;

      if (!visited[ay][ax]) {
        visited[ay][ax] = true;
        to_visit.push({ax, ay});
      }
    }
  }
}