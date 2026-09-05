#include <vector>
#include <queue>

using namespace std;

/*!
 * @param graph_alist 인접 리스트로 구현된 그래프의 인접 리스트
 * @param sv 시작 정점
 * @param tv 종료 정점
 */
void bfs_alist(vector<vector<int>> const &graph_alist, int sv, int tv) {
  // BFS 초기화 단계
  queue<int> to_visit;
  vector<bool> visited(graph_alist.size(), false);
  to_visit.push(sv);
  visited[sv] = true;

  // BFS 실행 단계
  while (!to_visit.empty()) {
    // 현재 정점 처리 단계
    auto const cv = to_visit.front();
    to_visit.pop();

    if (cv == tv) return;

    // 인접 정점 탐색 단계
    for (auto const &av: graph_alist[cv]) {
      if (!visited[av]) {
        visited[av] = true;
        to_visit.push(av);
      }
    }
  }
}