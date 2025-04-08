#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int T;

int main() {
  cin >> T;

  for (int t = 0; t < T; ++t) {
    // 입력
    // 좌표는 모두 [-10^3, 10^3]
    // 반지금 1000, 행성수 50

    pair<int, int> sp, ep;
    cin >> sp.first >> sp.second;
    cin >> ep.first >> ep.second;

    int n; cin >> n;
    vector<tuple<int, int, int>> planets(n);
    for (int i = 0; i < planets.size(); ++i) {
      int x, y, r;
      cin >> x >> y >> r;
      planets[i] = {x, y, r};
    }

    static auto is_in = [](const auto& pos, const auto& planet) {
      int s_dist 
        = (get<0>(planet) - pos.first) * (get<0>(planet) - pos.first) 
        + (get<1>(planet) - pos.second) * (get<1>(planet) - pos.second);
      return s_dist < get<2>(planet) * get<2>(planet);
    };

    int count = 0;

    for (const auto& planet: planets) {
      bool is_s_in = is_in(sp, planet);
      bool is_e_in = is_in(ep, planet);

      if (is_s_in && is_e_in) {
        // do nothing
      } else if (is_s_in && !is_e_in || !is_s_in && is_e_in) {
        ++count;
      } else if (!is_s_in && !is_e_in) {
        // do nothing
      }
    }

    cout << count << '\n';
  }
}