#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

#define ERROR -1

int main() {
  int N, T; // N [1, 50], T [1, 10^6]
  cin >> N >> T;

  int total_bus_count = 0;

  vector<tuple<int, int, int>> b_data(N);
  for (tuple<int, int, int>& e: b_data) {
    // S [1, 10^6] I [1, 10^4] C [1, 10^2]
    cin >> get<0>(e) >> get<1>(e) >> get<2>(e);
    total_bus_count += get<2>(e);
  }

  vector<int> schedules; 
  schedules.reserve(total_bus_count);

  // 스케줄 정리
  // O(NC)
  for (auto& [start, gap, num]: b_data) { // N: 10
    for (int i = 0; i < num; ++i) { // C: 10^2
      schedules.push_back(start + i * gap);
    }
  }

  // 탐색 할거면 정렬을 해야함
  sort(schedules.begin(), schedules.end()); // O(NC log (NC))

  // 여기서 선형 탐색 하면 최악의 경우 O(NC) - 
  // 근데 NC 자체가 작은 값이라 그래도 통과함 (근데 배열 범위 관련해서 코드 지저분해짐)
  auto low = lower_bound(schedules.begin(), schedules.end(), T); // O(log(NC))

  // 출력
  if (low != schedules.cend()) {
    cout << *low - T;
  } else {
    cout << ERROR;
  }
}