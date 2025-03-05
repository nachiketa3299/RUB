#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define NO_OCS -1

using namespace std;

int main() {
  int N; cin >> N; // N in [1, 10^6]
  vector<int> seq(N); // e in [1, 10^6]

  for (int &e: seq) cin >> e;
  vector<int> ocs(N, NO_OCS);

  stack<int> st; // 오큰수를 "아직 못 찾은" 수열 요소의 인덱스

  for (int i = 0; i < seq.size(); ++i) {

    // "오큰수를 모르는" 수를 최근 것부터 꺼내서 갱신
    while (!st.empty() && seq[st.top()] < seq[i]) {
      ocs[st.top()] = seq[i];
      st.pop();
    }

    st.push(i);
  }

  for (int const &e: ocs) cout << e << ' ';
}