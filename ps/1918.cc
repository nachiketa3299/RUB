#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

int main() {
  string infix; cin >> infix; // [A-Z+-*/()], [1, 100]

  stack<char> op_stack;
  unordered_map<char, int> precedence {{')', 0}, {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

  for (char ch: infix) {
    if (isalpha(ch)) {
      cout << ch;
    } else if (ch == '(') {
      op_stack.push(ch);
    } else if (ch == ')') {
      while (!op_stack.empty() && op_stack.top() != '(') {
        cout << op_stack.top();
        op_stack.pop();
      }
      op_stack.pop();
    } else {
      while (!op_stack.empty() && precedence[op_stack.top()] >= precedence[ch]) {
        cout << op_stack.top();
        op_stack.pop();
      }

      op_stack.push(ch);
    }
  }
  while (!op_stack.empty()) {
    cout << op_stack.top();
    op_stack.pop();
  }

  cout << "\n";
}

