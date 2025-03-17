#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N;

// queen[i] = j 면,  i행 j 열에 퀸이 배치되어 있다는 것
vector<int> queen; 

int cnt = 0;

bool is_safe(int i, int j) {

  for (int pi = 0; pi < i; ++pi) {
    int pj = queen[pi];

    // pi, pj 에 이전에 놨고, 지금 i, j

    // 같은 열에 놨는지 검사
    if (pj == j) return false;

    // 대각선이 겹치는지?
    if (abs(pj - j) == abs(pi - i)) return false;
  }
  return true;
}

void bt(int i) {
  if (i == N) {
    ++cnt;
    return;
  }

  for (int j = 0; j < N; ++j) {
    if (!is_safe(i, j)) {
      continue;
    }
    queen[i] = j;
    bt(i + 1);
  }
}

int main() {
  cin >> N;
  queen.resize(N);
  fill(queen.begin(), queen.end(), -1);

  bt(0);

  cout << cnt;
}