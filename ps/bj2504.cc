#include <iostream>
#include <string>
#include <stack>

using namespace std;


int main() {
  string str;
  stack<char> s;
  stack<int> nums;

  int result = 0;

  cin >> str;

  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      if (s.empty() || s.top() == ')' || s.top() == ']') {
        nums.push(2);
      }
    }
    else if (str[i] == ')') {
    }
    else if (str[i] == '[') {
    }
    else if (str[i] == ']') {
    }
  }

  cout << result;
}