#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int lis_length(const vector<int>& A) {
  if (A.empty()) {
    return 0;
  }

  vector<int> tails;

  tails.push_back(A.front());

  for (int i = 1; i < A.size(); ++i) {
    if (A[i] > tails.back()) {
      tails.push_back(A[i]);
    } else {
      *lower_bound(tails.begin(), tails.end(), A[i]) = A[i];
    }
  }

  return tails.size();
}

int main() {
  int N; cin >> N;
  vector<int> A(N);
  for (auto& e: A) {
    cin >> e;
  }

  cout << lis_length(A);
}