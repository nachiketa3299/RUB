#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, n, m;

vector<int> A, B;
vector<int> sum_a, sum_b;

int main() {
  cin >> T;

  cin >> n;
  A.resize(n);
  for(int& e: A) {
    cin >> e;
  }

  cin >> m;
  B.resize(m);
  for (int& e: B) {
    cin >> e;
  }

  for (int i = 0; i < n; ++i) {
    int sum = 0;
    for (int j = i; j < n; ++j) {
      sum += A[j];
      sum_a.push_back(sum);
    }
  }

  for (int i = 0; i < m; ++i) {
    int sum = 0;
    for (int j = i; j < m; ++j) {
      sum += B[j];
      sum_b.push_back(sum);
    }
  }

  sort(sum_a.begin(), sum_a.end());
  sort(sum_b.begin(), sum_b.end());

  long long count = 0;

  for (int& a: sum_a) {
    const int required = T - a;
    const auto& [begin, end] 
      = equal_range(
        sum_b.cbegin(), sum_b.cend(), 
        required
      );
    
    count += distance(begin, end);
  }

  cout << count;
}