// 07:33
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int N; cin >> N;
  vector<int> dp_max(4, 0), dp_min(4, 0);

  int pdp_max_1, pdp_max_2, pdp_max_3;
  int pdp_min_1, pdp_min_2, pdp_min_3;

  for (int n = 1; n <= N; ++n) {
    int s_1, s_2, s_3; cin >> s_1 >> s_2 >> s_3;

    if (n == 1) {
      dp_max[1] = s_1, dp_max[2] = s_2, dp_max[3] = s_3;
      dp_min[1] = s_1, dp_min[2] = s_2, dp_min[3] = s_3;
    } else {
      pdp_max_1 = dp_max[1], pdp_max_2 = dp_max[2], pdp_max_3 = dp_max[3];

      dp_max[1] = max({pdp_max_1, pdp_max_2           }) + s_1;
      dp_max[2] = max({pdp_max_1, pdp_max_2, pdp_max_3}) + s_2;
      dp_max[3] = max({           pdp_max_2, pdp_max_3}) + s_3;

      pdp_min_1 = dp_min[1], pdp_min_2 = dp_min[2], pdp_min_3 = dp_min[3];

      dp_min[1] = min({pdp_min_1, pdp_min_2           }) + s_1;
      dp_min[2] = min({pdp_min_1, pdp_min_2, pdp_min_3}) + s_2;
      dp_min[3] = min({           pdp_min_2, pdp_min_3}) + s_3;
    }
  }

  cout << *max_element(next(dp_max.cbegin()), dp_max.cend()) << ' ';
  cout << *min_element(next(dp_min.cbegin()), dp_min.cend());
}