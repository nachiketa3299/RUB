#include <iostream>
#include <unordered_map>

using namespace std;

long long N;
int P, Q;
unordered_map<long long, long long> cache{{0, 1}};

long long seq(const long long& n) {
  if (cache.find(n) != cache.cend()) {
    return cache[n];
  }

  return cache[n] = seq(n / P) + seq(n / Q);
}

int main() {
  cin >> N >> P >> Q;
  cout << seq(N);
}