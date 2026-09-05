// 08:21
#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

int main() {
  int N, M;
  cin >> N >> M;

  vector<int> vertices(N);
  for (int& e: vertices) cin >> e;

  vector<tuple<int, int, int>> ranges(M);
  for (tuple<int, int, int>& e: ranges) {
    cin >> get<0>(e) >> get<1>(e);
    get<2>(e) = 0;
  }

  for (const int& v: vertices) { // N (10^5)
    for (tuple <int, int, int>& r: ranges) { // M (10^5)

    // 여기서 이미 10^10 으로 10초임
      if (get<0>(r) <= v && v <= get<1>(r)) {
        get<2>(r) += 1;
      }
    }

  }

  for (tuple<int, int, int>& r: ranges) {
    cout << get<2>(r) << '\n';
  }
}