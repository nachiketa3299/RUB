#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void lis(const vector<int>& A, vector<int>& out_tails) {
  if (A.empty()) {
    return;
  }

  out_tails.push_back(A.front());

  for (int i = 1; i < A.size(); ++i) {
    if (A[i] > out_tails.back()) {
      out_tails.push_back(A[i]);
    } else {
      *lower_bound(out_tails.begin(), out_tails.end(), A[i]) = A[i];
    }
  }
}

int main() {
  int N; cin >> N;
  vector<int> A(N);
  for (auto& a: A) {
    cin >> a;
  }

  vector<int> tails;
  lis(A, tails);

  cout << tails.size() << '\n';
  for (auto& e: tails) {
    cout << e << ' ';
  }

}