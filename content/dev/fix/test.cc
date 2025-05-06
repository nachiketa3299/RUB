#include <string>
#include <iostream>
#include <stack>

using namespace std;

int main() {
  string infix; cin >> infix;
  auto precedence = [](char ch) {
    switch (ch) {
      case '+': case '-': return 0; 
      case '*': case '/': return 1;
    }
  };

  auto is_operator = [](char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
  };

  stack<char> op_stack;

  for (char ch: infix) {
    if (isalpha(ch)) {
      cout << ch;
    } else if (is_operator(ch)) {
      while (!op_stack.empty() && op_stack.top() != '(' && precedence(op_stack.top()) >= precedence(ch)) {
        cout << op_stack.top();
        op_stack.pop();
      }
      op_stack.push(ch);
    } else if (ch == '(') {
      op_stack.push(ch);
    } else if (ch == ')') {
      while (op_stack.top() != '(') {
        cout << op_stack.top();
        op_stack.pop();
      }
      op_stack.pop();
    }
  }

  while (!op_stack.empty()) {
    cout << op_stack.top();
    op_stack.pop();
  }
}