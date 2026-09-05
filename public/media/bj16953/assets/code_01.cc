#include <iostream>
#include <algorithm>

using namespace std;

constexpr int NO_PATH = -1;

int A, B;

int bt(long long k, int depth) {
  // B를 일단 발견하였다.
  if (k == B) {
    return depth;
  } 

  if (k < B) {
    // 왼쪽과 오른쪽 자식에서 B 찾기를 시도
    int l = bt(2 * k, depth + 1);
    int r = bt(10 * k + 1, depth + 1);
    // 1. 왼쪽과 오른쪽 모두에서 B를 발견
    if (l != NO_PATH && r != NO_PATH) {
      return min(l, r);
    // 2. 왼쪽에서만 발견
    } else if (l == NO_PATH && r != NO_PATH) {
      return r;
    // 3. 오른쪽에서만 발견
    } else if (l != NO_PATH && r == NO_PATH) {
      return l;
    }
  } 

  // 트리를 다 뒤져봐도 B가 없습니다.
  return NO_PATH;
}

int main() {
  cin >> A >> B;
  cout << bt(A, 1);
}