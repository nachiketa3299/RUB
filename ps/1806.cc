#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
  int N; cin >> N; // N in [10, 10^5]
  int S; cin >> S; // S in (0, 10^8]

  vector<int> seq(N);
  for (int& e: seq) {
    cin >> e; // [1, 10^4]
  }

  int start = 0, end = 0;
  int sum = 0;
  int min_len = INT_MAX;

  while (true) {
    if (sum >= S) {
      min_len = min(min_len, end - start);
      sum -= seq[start];
      ++start;
    } else if (end == N) {
      break;
    } else {
      sum += seq[end];
      ++end;
    }
  }

  if (min_len == INT_MAX) {
    cout << 0 << '\n';
  } else {
    cout << min_len << '\n';
  }
}