#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  int n; cin >> n; // n in [1, 100'000]

  vector<int> seq(n);
  for (int i = 0; i < seq.size(); ++i) {
    cin >> seq[i];
  }

  // cur 는 1,  2, ... ,n 수열에 의거하여, 
  // 다음에 스택에 넣을 수 있는 수
  // cur - 1 까지는 스택에 이미 push 되었다고 보면 됨
  int cur = 1;
  stack<int> st;
  vector<char> pr; pr.reserve(n); // '+', '-' 저장용
  bool is_possible = true;

  for (int const &seq_num: seq) {
    while (cur <= seq_num) {
      st.push(cur);
      pr.push_back('+');
      ++cur;
    }

    if (!st.empty() && st.top() == seq_num) {
      st.pop();
      pr.push_back('-');
    } else {
      is_possible = false;
      cout << "NO";
      break;
    }
  }

  if (is_possible) {
    for (char const &c: pr) cout << c << '\n';
  }
}