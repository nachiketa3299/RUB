#include <iostream>
#include <queue>

using namespace std;

constexpr int NO_PATH = -1;

int A, B;

int bfs(int a, int depth) {
  queue<pair<long long, int>> to_visit;
  to_visit.push({a, depth});

  while (!to_visit.empty()) {
    auto [cv, cd] = to_visit.front();
    to_visit.pop();

    // B 발견, 그리고 이것이 최단 경로이므로 빠른 종료.
    if (cv == B) {
      return cd;
    }

    // 왼쪽 자식
    long long p1 = cv * 2;
    // 오른쪽 자식
    long long p2 = cv * 10 + 1;

    // 왼쪽 자식이 B보다 작으면, 
    // 왼쪽 자식을 루트로 하는 서브트리를 탐색해 봐야함
    if (p1 <= B) {
      to_visit.push({p1, cd + 1});
    }

    // 오른쪽 자식이 B보다 작으면, 
    // 오른쪽 자식을 루트로 하는 서브트리를 탐색해 봐야함
    if (p2 <= B) {
      to_visit.push({p2, cd + 1});
    }
  }

  return NO_PATH;
}

int main() {
  cin >> A >> B;

  cout << bfs(A, 1);
}