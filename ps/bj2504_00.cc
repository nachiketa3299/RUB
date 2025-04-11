#include <iostream>
#include <string>
#include <stack>

#define S_OPEN -2
#define B_OPEN -3

using namespace std;

int main() {
  string ps; cin >> ps;
  stack<int> num;

  int answer = 0;

  for (int i = 0; i < ps.size(); ++i) {
    if (ps[i] == '(') {
      num.push(S_OPEN);
    } 
    else if (ps[i] == ')') {
      
      if (num.empty()) {
        break;
      }

      // 가장 최근에 넣은게 일단 [이면,
      // 짝이 맞지 않는 것이므로 빠른 종료
      if (num.top() == B_OPEN) {
        break;
        // () 인 상황
      } else if (num.top() == S_OPEN) {
        num.pop();
        num.push(2);
        // (X) 인 상황
      } else {
        int temp_sum = 0;
        bool is_invalid = true;
        while (!num.empty()) {
          if (num.top() == B_OPEN) {
            break;
          }

          if (num.top() != S_OPEN) {
            temp_sum += num.top();
            num.pop();
          } else {
            is_invalid = false;
            int temp = temp_sum * 2;
            num.pop();
            num.push(temp);
            break;
          }
        }

        if (is_invalid) {
          break;
        }
      }
    }
    else if (ps[i] == '[') {
      num.push(B_OPEN);
    }
    else if (ps[i] == ']') {

      if (num.empty()) {
        break;
      }

      // 가장 최근에 넣은게 일단 (이면,
      // 짝이 맞지 않는 것이므로 빠른 종료
      if (num.top() == S_OPEN) {
        break;
        // [] 인 상황
      } else if (num.top() == B_OPEN) {
        num.pop();
        num.push(3);
        // [X] 인 상황
      } else {
        int temp_sum = 0;
        bool is_invalid = true;
        while (!num.empty()) {
          if (num.top() == S_OPEN) {
            break;
          }

          if (num.top() != B_OPEN) {
            temp_sum += num.top();
            num.pop();
          } else {
            is_invalid = false;
            int temp = temp_sum * 3;
            num.pop();
            num.push(temp);
            break;
          }
        }

        if (is_invalid) {
          break;
        }
      }
    }
  }

  while (!num.empty()) {
    if (num.top() == S_OPEN || num.top() == B_OPEN) {
      answer = 0;
      break;
    }
    answer += num.top();
    num.pop();
  }

  cout << answer;
}