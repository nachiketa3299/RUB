#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// A -> B 로 가는데 드는 버스 비용 최소화
// A -> B 로 가는데 드는 최소비용 출력하쇼
// 도시 번호는 1부터 N 까지

int N; // 도시 개수 [1, 10^3]
int M; // 버스 개수 [1, 10^5]
vector<vector<pair<int, int>>> adj_list;
int s, e;

int main() {
  cin >> N >> M;
  adj_list = vector<vector<pair<int, int>>>(N + 1);

  for (int i = 0; i < M; ++i) {
    int s_pos, e_pos, c;
    cin >> s_pos >> e_pos >> c;
    adj_list[s_pos].push_back({c, e_pos});
  }
  cin >> s >> e;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  vector<int> distances(N + 1, INT_MAX); distances[0] = 0;

  distances[s] = 0;
  pq.push({0, s});

  while (!pq.empty()) {
    const auto [c_cost, c_pos] = pq.top();
    pq.pop();

    if (c_cost > distances[c_pos]) {
      continue;
    }

    for (const auto& [a_cost, a_pos]: adj_list[c_pos]) {
      int via_dist = distances[c_pos] + a_cost;
      if (via_dist >= distances[a_pos]) {
        continue;
      }
      distances[a_pos] = via_dist;
      pq.push({via_dist, a_pos});
    }
  }

  cout << distances[e];
}