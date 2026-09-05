#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int T, n, m;
vector<int> A, B;
unordered_map<int, int> sumA, sumB;

int main() {
  cin >> T;

  // A 입력
  cin >> n; 
  A.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> A[i];
  }

  // B 입력
  cin >> m;
  B.resize(m);
  for (int i = 0; i < m; ++i) {
    cin >> B[i];
  }

  // A 부 배열 합과 갯수
  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int sum = 0;
      for (int c = i; c <= j; ++c) {
        sum += A[c];
      }
      ++sumA[sum];
    }
  }

  // B 부 배열 합과 갯수
  for (int i = 0; i < m; ++i) {
    for (int j = i; j < m; ++j) {
      int sum = 0;
      for (int c = i; c <= j; ++c)  {
        sum += B[c];
      }
      ++sumB[sum];
    }
  }

  // 주의: long long
  long long count = 0;

  // A 기준으로 B에 합이 존재하는지 확인
  for (const auto& [sum_a, count_a]: sumA) {
    int required = T - sum_a;

    if (sumB.find(required) == sumB.cend()) {
      continue;
    }

    count += (long long)count_a * sumB[required];
  }

  cout << count;
}
