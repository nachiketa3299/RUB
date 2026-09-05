#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;

// queen[i] = j 면,  i열 j행에 배치되어 있다는 뜻
vector<int> queen; 

int cnt = 0;

bool is_safe(int v, int h) {
  for (int pv = 0; pv < v; ++pv) {
    int ph = queen[pv];

    // 이전 열에 배치된 퀸퀸 중 하나의 위치가 pv열 ph행이다.
    // 현재 v열 h행에 새 퀸을 배치할 수 있는지 확인한다.

    // 같은 행에 놨는지 검사
    if (ph == h) {
      return false;
    }    

    // 대각선이 겹치는지?
    if (abs(pv - v) == abs(ph - h)) {
      return false;
    }

  }
  return true;
}

void bt(int v) {
  // 마지막 열인가?
  if (v == N) {
    ++cnt;
    return;
  }

  for (int h = 0; h < N; ++h) {
    if (!is_safe(v, h)) {
      continue;
    }
    queen[v] = h;
    bt(v + 1);
  }
}

int main() {
  cin >> N;
  queen.resize(N);
  fill(queen.begin(), queen.end(), -1);

  bt(0);

  cout << cnt;
}