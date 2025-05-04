#include <iostream>

using namespace std;
using ull = unsigned long long;

int main() {
  ull N; cin >> N;

  ull sum = 0;
  ull base = 0;

  auto pow = [](ull a, ull n) {
    ull ret = 1;
    for (ull i = 1; i <= n; ++i) {
      ret *= a;
    }
    return ret;
  };

  while (N != 0) {
    ull mod = N % 2;
    N /= 2;

    sum += mod * pow(3ull, base);
    ++base;
  }
  cout << sum;
}