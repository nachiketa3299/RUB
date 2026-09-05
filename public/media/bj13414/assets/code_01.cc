#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

int K, L;

vector<string> nums;
unordered_map<string, int> umap;

int main() {
  cin >> K >> L;
  nums.reserve(L);

  for (int l = 0; l < L; ++l) {
    string num; cin >> num;
    nums.push_back(num);
  }

  int index = 0;

  for (const string& num: nums) {
    // umap의 상대 순서 업데이트
    ++index;
    umap[num] = index;
  }

  // 최종 대기 순번
  vector<pair<string, int>> vec(umap.begin(), umap.end());

  sort(vec.begin(), vec.end(), 
    [](const auto& l, const auto& r) { 
      return l.second < r.second; // 값의 오름차순으로 정렬
    }
  );

  // 최대값 주의 
  for (int i = 0; i < min(K, (int)vec.size()); ++i) {
    cout << vec[i].first << '\n';
  }
}
