#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

constexpr char ERROR[] = "SAD";

int main() {
  // 입력
  int N, X; cin >> N >> X;

  vector<int> visitors(N);
  for (auto& visitor: visitors) {
    cin >> visitor;
  }

  // 초기값
  int max_visitor = accumulate(visitors.cbegin(), next(visitors.cbegin(), X), 0);
  int current = max_visitor;
  int count = 1;

  for (int i = 1; i + X - 1 < N; ++i) {
    current = current - visitors[i - 1] + visitors[i + X - 1];

    if (current > max_visitor) {
      count = 1;
      max_visitor = current;
    } else if (current == max_visitor) {
      ++count;
    }
  }

  if (max_visitor == 0) {
    cout << ERROR;
  } else {
    cout << max_visitor << '\n' << count;
  }
}