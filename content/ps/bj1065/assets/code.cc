#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool is_hansu(int n) {
    string sn = to_string(n);

    // 숫자의 길이가 1, 2이면 그냥 한수 (비교할 것이 없음)
    if (sn.size() <= 2) 
      return true;

    // 초항을 이용해 공차를 계산해둠
    int a_0 = *sn.cbegin() - '0';
    int a_1 = *(++sn.cbegin()) - '0';
    int d = a_1 - a_0;

    // 두 번째 항 부터 공차를 계산 해봄
    for (auto it = sn.cbegin() + 1; it != sn.cend(); ++it) {
      // 마지막 항에 도달했으면 종료
      if (it + 1 == sn.cend()) 
        break;

      // 공차 계산해보고 `d`랑 다르면 한수 아니므로 빠른 종료
      int a_n_0 = *it - '0';
      int a_n_1 = *(it + 1) - '0';

      if (a_n_1 - a_n_0 != d) 
        return false;
    }

    // 여기까지 도달한 경우 모든 공차가 동일한 것이므로 한수
    return true;
}

int main() {
  int N; cin >> N; // [1, 1'000]

  int count = 0;

  for (int n = 1; n <= N; ++n) {
    if (is_hansu(n)) 
      ++count;
  }

  cout << count;
}

// TODO: 반복자 섞어 쓰기