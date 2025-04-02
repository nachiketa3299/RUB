#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, n, m;

vector<int> A, B;
vector<int> sum_a, sum_b;

int main() {
  cin >> T;

  // A 입력
  cin >> n;
  A.resize(n);
  for(int& e: A) {
    cin >> e;
  }

  // B 입력
  cin >> m;
  B.resize(m);
  for (int& e: B) {
    cin >> e;
  }

  // A 부 배열
  for (int i = 0; i < n; ++i) {
    int sum = 0;
    for (int j = i; j < n; ++j) {
      sum += A[j];
      sum_a.push_back(sum);
    }
  }

  // B 부 배열
  for (int i = 0; i < m; ++i) {
    int sum = 0;
    for (int j = i; j < m; ++j) {
      sum += B[j];
      sum_b.push_back(sum);
    }
  }

  // 정렬 
  sort(sum_b.begin(), sum_b.end());

  long long count = 0;

  // sum_a의 각 요소에 대해 반복:
  for (int& a: sum_a) {
    const int required = T - a;

    // 상한과 하한 찾기
    const auto& [begin, end] 
      = equal_range(
        sum_b.cbegin(), sum_b.cend(), 
        required
      );
    
    // 전체 개수 업데이트
    count += distance(begin, end);
  }

  cout << count;
}