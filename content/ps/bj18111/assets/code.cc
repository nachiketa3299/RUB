#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int TIME_REMOVE = 2;
constexpr int TIME_PLACE = 1;

int main() {
  // N, M in [1, 500] - 세로 가로
  // B in [0, 6.4 * 10^7] - 인벤토리 내 블록 수
  int N, M, B; cin >> N >> M >> B;

  vector<vector<int>> land (
    N, vector<int>(M, 0)
  );

  int min_height{0}, max_height{256};

  for (auto& hl: land) {
    for (auto& e: hl) {
      cin >> e;
      // 최대 높이와 최소 높이 갱신
      min_height = min(min_height, e);
      max_height = max(max_height, e);
    }
  }

  int min_time{numeric_limits<int>::max()};
  int proper_height{0};

  for (
    int c_height{min_height}; 
    c_height <= max_height; 
    ++c_height
  ) {
    int cnt_to_remove{0}, cnt_to_place{0};

    // 지금 높이에서 빼거나 추가해야 할 값 갱신
    for (auto& hl: land) {
      for (auto& e: hl) {
        int diff{e - c_height}; 

        // diff > 0 이면, 빼야 함
        if (diff > 0) {
          cnt_to_remove += diff;
        } else if (diff < 0) {
        // diff < 0 이면, 추가 해야 함
          cnt_to_place += -diff;
        }
      }
    }

    if (cnt_to_remove + B >= cnt_to_place) {
      int c_time{
        cnt_to_remove * TIME_REMOVE + cnt_to_place * TIME_PLACE
      };

      if (
        c_time < min_time || 
        (c_time == min_time && c_height > proper_height)
      ) {
        min_time = c_time;
        proper_height = c_height;
      }
    }
  }

  cout << min_time << ' ' << proper_height << '\n';
}