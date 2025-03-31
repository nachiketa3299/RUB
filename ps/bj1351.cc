#include <iostream>
#include <unordered_map>

using namespace std;
using ll = long long;

ll N;
int P, Q;

unordered_map<ll, ll> umap;

// N [0, 10^12]
// P, Q [2, 10^9]

ll solve(const ll& N) {
  if (umap.find(N) != umap.end()) {
    return umap[N];
  }

  return umap[N] = solve(N / P) + solve(N / Q);
}

int main() {
  cin >> N >> P >> Q;
  umap[0] = 1;
  cout << solve(N);
}