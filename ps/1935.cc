#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>
#include <iomanip>

using namespace std;

int main() {
  int N; cin >> N;
  string postfix; cin >> postfix;

  unordered_map<char, double> dict;
  for (int i = 0; i < N; ++i) {
    double val; cin >> val;
    dict[char(i + 'A')] = val;
  }

  stack<double> op_stack;

  for (char ch: postfix) {
    if (isalpha(ch)) {
      op_stack.push(dict[ch]);
    } else {
      double op_r = op_stack.top(); op_stack.pop();
      double op_l = op_stack.top(); op_stack.pop();

      switch (ch) {
        case '+':
          op_stack.push(op_l + op_r);
          break;
        case '-':
          op_stack.push(op_l - op_r);
          break;
        case '*':
          op_stack.push(op_l * op_r);
          break;
        case '/':
          op_stack.push(op_l / op_r);
          break;
      }
    }
  }

  cout << fixed << setprecision(2) << op_stack.top();
}