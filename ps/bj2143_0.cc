// @date 2025-04-02 08:39

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// A의 부 배열의 합에 B의 부 배열의 합을 더해 T가 되는 모든 부 배열 쌍의 개수를 구하는 프로그램

// T [-10^9, 10^9]
// n [1, 10^3]
// m [1, 10^3]

// n의 부배열 합 모두 더하는데 소요 -> n^2
// m의 부배열 합 모두 더하는데 소요 -> m^2
// 그리고 한쪽에서 하나를 뽑아서, 다른쪽에서 걸맞는거 탐색 -> n^2 (해시테이블 이용시)
// 그러니까 대략 O(m^2 + n^2)

int T, n, m;
vector<int> A, B;
unordered_map<int, int> sumA, sumB; // sum, count

int main() {
  cin >> T;

  cin >> n; 
  A.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
  }

  cin >> m;
  B.resize(m);
  for (int i = 0; i < m; ++i) {
    cin >> B[i];
  }

  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int sum = 0;
      for (int c = i; c <= j; ++c) {
        sum += A[c];
      }
      ++sumA[sum];
    }
  }

  for (int i = 0; i < m; ++i) {
    for (int j = i; j < m; ++j) {
      int sum = 0;
      for (int c = i; c <= j; ++c)  {
        sum += B[c];
      }
      ++sumB[sum];
    }
  }

  long long count = 0;

  for (const auto& [sum_a, count_a]: sumA) {
    int required = T - sum_a;

    if (sumB.find(required) == sumB.cend()) {
      continue;
    }

    count += static_cast<long long>(count_a) * sumB[required];
  }

  cout << count;
}
