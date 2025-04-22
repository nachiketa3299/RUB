#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void get_llcs(
  const vector<int>& A, int a_idx,
  const vector<int>& B, int b_idx,
  vector<int>& o_result
) {
  if (a_idx >= A.size() || b_idx >= B.size()) {
    return;
  }

  auto a_it = max_element(A.begin() + a_idx, A.end());
  auto b_it = max_element(B.begin() + b_idx, B.end());

  if (*a_it == *b_it) {
    o_result.push_back(*a_it);

    get_llcs(A, distance(A.begin(), a_it) + 1, B, distance(B.begin(), b_it) + 1, o_result);
    return;
  } else if (*a_it > *b_it) {
    get_llcs(A, distance(A.begin(), a_it) + 1, B, b_idx, o_result);
    return;
  } else {
    get_llcs(A, a_idx, B, distance(B.begin(), b_it) + 1, o_result);
    return;
  }
}

int main() {
  int N; cin >> N;
  vector<int> A(N);
  for (auto& a: A) {
    cin >> a;
  }

  int M; cin >> M;
  vector<int> B(M);
  for (auto& b: B) {
    cin >> b;
  }

  vector<int> llcs;
  get_llcs(A, 0, B, 0, llcs);

  cout << llcs.size();

  if (llcs.empty()) {
    return 0;
  }

  cout << '\n';
  for (const auto& e: llcs) {
    cout << e << ' ';
  }
}