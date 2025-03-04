#include <iostream>
#include <string>
#include <list>

using namespace std;

#define CMD_I 0
#define ARG_I 2

int main() {
  string str; cin >> str; // [a-z], [100'000]
  int M; cin >> M; // [1, 500'000]

  cin.ignore(); 

  list<char> l_str(str.begin(), str.end());

  // 커서는 자기가 가리키는 문자 바로 앞의 위치에 있음
  auto cursor = l_str.end();

  for (int i = 0; i < M; ++i) {
    string  i_cmd; getline(cin, i_cmd);

    switch (i_cmd[CMD_I]) {
      case 'L': // 커서를 왼쪽으로 한 칸 옮기기
        if (cursor != l_str.begin()) {
          cursor = prev(cursor);
        }
        break;

      case 'D': // 커서를 오른쪽으로 한 칸 옮기기
        if (cursor != l_str.end()) {
          cursor = next(cursor);
        }
        break;

      case 'B': // 커서 왼쪽에 있는 문자 삭제
        if (cursor != l_str.begin()) {
          cursor = l_str.erase(prev(cursor));
        }
        break;

      case 'P': // 왼쪽에 인자로 전달된 문자 추가
          cursor = next(l_str.insert(cursor, i_cmd[ARG_I]));
        break;
    }
  }

  for (char c: l_str) cout << c;
}