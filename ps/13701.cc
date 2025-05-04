#include <iostream>
#include <bitset>

using namespace std;

constexpr int MAX_VALUE = 1 << 25; // 2^25

int main() {
   ios::sync_with_stdio(false);
  cin.tie(NULL);

  bitset<MAX_VALUE> seen;

  int x;
  while (cin >> x) {
    if (!seen[x]) {
      seen[x] = true;
      cout << x << ' ';
    }
  }
}