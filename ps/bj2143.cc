#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int T, n, m;
vector<int> A, B;
unordered_map<int, int> sum_a, sum_b;

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
    int sum = 0;
    for (int j = i; j < n; ++j) {
      sum += A[j];
      ++sum_a[sum];
    }
  }

  for (int i = 0; i < m; ++i) {
    int sum = 0;
    for (int j = i; j < m; ++j) {
      sum += B[j];
      ++sum_b[sum];
    }
  }

  long long answer = 0;
  for (const auto& [sum, count]: sum_a) {
    int required = T - sum;
    if (sum_b.find(required) != sum_b.cend()) {
      answer += static_cast<long long>(count) * sum_b[required];
    }
  }

  cout << answer;
}