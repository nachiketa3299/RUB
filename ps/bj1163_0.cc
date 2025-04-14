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
    if (start > end) {
      swap(start, end);
    }
  }

  sort(vertices.begin(), vertices.end());

  for (auto& [start, end]: ranges) {
    auto low =  lower_bound(vertices.begin(), vertices.end(), start);
    auto up = upper_bound(vertices.begin(), vertices.end(), end);

    cout << distance(low, up) << '\n';
  }
}