/// @date 2025-04-21 약 30분

#include <iostream>
#include <algorithm>

using namespace std;

constexpr int NO_PATH = -1;

int A, B;

int bt(long long k, int depth) {
  // 도달한 경우
  if (k == B) {
    return depth;
  } 

  if (k < B) {
    int l = bt(2 * k, depth + 1);
    int r = bt(10 * k + 1, depth + 1);
    if (l != NO_PATH && r != NO_PATH) {
      return min(l, r);
    } else if (l == NO_PATH && r != NO_PATH) {
      return r;
    } else if (l != NO_PATH && r == NO_PATH) {
      return l;
    }
  } 

  return NO_PATH;
}

int main() {
  cin >> A >> B;
  cout << bt(A, 1);
}