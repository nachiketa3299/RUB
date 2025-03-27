// 2025-03-27 @ 18:12
// 0.5초! 4MB

#include <iostream>
#include <vector>

using namespace std;

int n, k; // n in [1, 10^2] k in [1, 10^4]
// n 가지 종류의 동전, 동전 적당히 사용해서, 가치 합이 k원 이 되도록 한다.
// 경우의 수를 구하라. 각 동전은 몇개라도 쓸 수 있다.
// 구성은 갖고 순서만 다른 것은 같은 경우이다.

vector<int> coins;

int main() {

  cin >> n >> k;
  coins = vector<int>(n);
  for (int i = 0; i < n; ++i) {
    cin >> coins[i]; // [1, 10^5]
  }

  return 0;
}
