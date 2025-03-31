// @date 2025-03-31T14:44 - 
// 54분

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

int K; // 과목의 수강 가능 인원 [1, 10^5]
int L; // 클릭 순서 기록한 대기 목록 길이 [1, 5 * 10^5]

vector<string> nums;
unordered_map<string, int> map;

// 학번은 8자리 숫자로 이루어져 있음

int main() {
  cin >> K >> L;
  nums.reserve(L);

  for (int l = 0; l < L; ++l) {
    string num; cin >> num;
    nums.push_back(num);
  }

  int index = 0;

  for (const string& num: nums) {
    ++index;
    map[num] = index;
  }

  vector<pair<string, int>> vec(map.begin(), map.end());
  sort(vec.begin(), vec.end(), [](const auto& l, const auto& r) { return l.second < r.second; });

  for (int i = 0; i < min(K, (int)vec.size()); ++i) {
    cout << vec[i].first << '\n';
  }
  
}
