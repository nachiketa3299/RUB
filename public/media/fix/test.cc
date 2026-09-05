#include <string>
#include <iostream>
#include <stack>

using namespace std;

int main() {
  string postfix; cin >> postfix;
  auto precedence = [](char ch) {
    switch (ch) {
      case '+': case '-': return 0; 
      case '*': case '/': return 1;
    }
  };

  auto is_operator = [](char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
  };

  stack<string> op_stack;

  for (char ch: postfix) {
    if (isalpha(ch)) {
      op_stack.push(string{ch});
    } else if (is_operator(ch)) {
      string r_op = op_stack.top(); 
      op_stack.pop();

      string l_op = op_stack.top(); 
      op_stack.pop();

      string exp = "(" + l_op + ch + r_op + ")";
      op_stack.push(exp);
    }
  }

  while (!op_stack.empty()) {
    cout << op_stack.top();
    op_stack.pop();
  }

}