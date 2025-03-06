#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define IMPOSSIBLE "I'm Sorry Hansoo"

int main() {
  string name; cin >> name; // [A-Z], len <= 50

  // 사전순 출력을 원하므로 키가 정렬되어 있어야 해서 map 선택
  map<char, int> freq;

  // 빈도 초기화
  for (char c = 'A'; c <= 'Z'; ++c) freq[c] = 0;

  // 빈도 기록
  for (char const &c: name) ++freq[c];

  pair<char, int> odd_data {'\0', 0};
  bool already_found_odd = false;

  for (auto &[k, v]: freq) {
    if (v == 0) continue;

    if (v % 2 != 0) {
      if (!already_found_odd) {
        // 홀수 빈도 문자를 처음 발견한 상황
        already_found_odd = true;

        odd_data.first = k;
        odd_data.second += 1;

        --v;
      } else {
        // 이미 홀수 빈도 문자가 있었는데 또 발견한 상황
        cout << IMPOSSIBLE;
        return 0;
      }
    }
  }

  string h_palin = "", ret = "";

  // 팰린드롬의 전반부 구성
  for (auto const &[c, c_count]: freq) {
    h_palin.append(c_count / 2, c);
  }

  ret += h_palin;

  // 홀수 문자 하나가 존재한다면 붙여둠
  if (already_found_odd)
    ret += odd_data.first;
  
  // 팰린드롬의 후반부 구성
  reverse(h_palin.begin(), h_palin.end());

  ret += h_palin;

  cout << ret;
}
