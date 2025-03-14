#include <vector>
#include <queue>

using namespace std;

#define NO_PARENT -1

/*!
 * @param graph_alist 인접 리스트로 구현된 그래프의 인접 리스트
 * @param sv 시작 정점
 * @param tv 종료 정점
 */
vector<int> bfs_alist(vector<vector<int>> const &graph_alist, int sv, int tv) {
  // BFS 초기화 단계
  queue<int> to_visit;
  vector<int> pnode(graph_alist.size(), NO_PARENT);
  to_visit.push(sv);
  pnode[sv] = sv;

  // BFS 실행 단계
  while (!to_visit.empty()) {
    // 현재 정점 처리 단계
    auto const cv = to_visit.front();
    to_visit.pop();

    if (cv == tv) return pnode;

    // 인접 정점 탐색 단계
    for (auto const &av: graph_alist[cv]) {
      if (pnode[av] == NO_PARENT) {
        pnode[av] = pnode[cv];
        to_visit.push(av);
      }
    }
  }
}