#include <iostream>
#include <string>
#include <stack>

using namespace std;

/// @brief '(' 를 마킹하기 위한 매크로
#define S_OPEN -2

/// @brief '[' 를 마킹하기 위한 매크로
#define B_OPEN -3

int main() {
  string ps; cin >> ps;
  stack<int> num;

  int answer = 0;

  for (int i = 0; i < ps.size(); ++i) {
    // 열리는 경우 우선 마킹해 둔다
    if (ps[i] == '(') {
      num.push(S_OPEN);
    } 
    // 닫히는 경우의 적절한 처리 로직
    else if (ps[i] == ')') {
      
      // ')' 이면 가장 최근의 스택 최상단을 확인해봐야 하는데,
      // 스택이 비어있는 경우 최상단을 확인하는 경우 UB가 발생할 수 있음.
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
        // 이제부터 `(`가 나올 때까지 스택을 훑을거임
        // 만일 스택 다 훑었는데 `(`가 안나오면 올바르지 않은 것임 
        int temp_sum = 0;
        bool is_invalid = true;
        while (!num.empty()) {
          if (num.top() == B_OPEN) {
            break;
          }

          if (num.top() != S_OPEN) {
            temp_sum += num.top();
            num.pop();
          // `(` 발견!
          // 임시로 더한 것들에 * 2 해서 다시 스택에 넣어줌
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
    // 열리는 경우 우선 마킹해 둔다
    else if (ps[i] == '[') {
      num.push(B_OPEN);
    }
    // 닫히는 경우 적절한 처리 로직
    else if (ps[i] == ']') {

      // ']' 이면 가장 최근의 스택 최상단을 확인해봐야 하는데,
      // 스택이 비어있는 경우 최상단을 확인하는 경우 UB가 발생할 수 있음.
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
        // 이제부터 `[`가 나올 때까지 스택을 훑을거임
        // 만일 스택 다 훑었는데 `[`가 안나오면 올바르지 않은 것임 
        int temp_sum = 0;
        bool is_invalid = true;
        // -3 까지 
        while (!num.empty()) {
          if (num.top() == S_OPEN) {
            break;
          }

          if (num.top() != B_OPEN) {
            temp_sum += num.top();
            num.pop();
          } else {
            // `]` 발견!
            // 임시로 더한 것들에 * 3 해서 다시 스택에 넣어줌
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

  // 괄호 훑기 끝!
  // 이제 스택에 남은 값들을 처리할 것임

  while (!num.empty()) {
    // 만일 마킹하려고 넣어둔 임시 값이 껴있다? 
    // 뭔가 잘못된 것이므로 0으로 종료
    if (num.top() == S_OPEN || num.top() == B_OPEN) {
      answer = 0;
      break;
    }
    answer += num.top();
    num.pop();
  }

  cout << answer;
}