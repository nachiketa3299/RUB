#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<int> vertices(N);
  for (int& v: vertices) {
    cin >> v;
  }

  vector<pair<int, int>> ranges(M);
  for (auto& [start, end]: ranges) {
    cin >> start >> end;
    // 구간이 작은 것이 앞에 온다는 보장이 없음
    if (start > end) {
      swap(start, end);
    }
  }

  // O(N log N)
  sort(vertices.begin(), vertices.end());

  for (auto& [start, end]: ranges) {
    // start 이상의 첫 위치
    auto low =  lower_bound(vertices.begin(), vertices.end(), start);

    // end 초과의 첫 위치
    auto up = upper_bound(vertices.begin(), vertices.end(), end);

    // low 부터 up 까지 요소의 개수
    cout << distance(low, up) << '\n';
  }
}