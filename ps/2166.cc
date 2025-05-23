// 12:35

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

using ll = long long;
using dd = double;

pair<ll, ll> operator-(const pair<ll, ll>& l, const pair<ll, ll>& r) {
  return {l.first - r.first, l.second - r.second};
}

ll cross2d(const pair<ll, ll>& l, const pair<ll, ll>& r) {
  return l.first * r.second - l.second * r.first;
}

int main() {
  // 2차원 평면 상에 N[3, 10^4]개의 점으로 이루어진 다각형
  // 다각형의 면적을 구한다

  ll N; cin >> N;

  vector<pair<ll, ll>> poss(N);
  for (auto& [x, y]: poss) {
    cin >> x >> y;
  }

  const pair<ll, ll>& pivot = poss.front();

  dd area = .0f;

  for (size_t i = 1; i < poss.size() - 1; ++i) {
    pair<ll, ll> v1 = poss[i] - pivot;
    pair<ll, ll> v2 = poss[i + 1] - pivot;
    area += .5f * (dd)cross2d(v1, v2);
  }

  cout << fixed << setprecision(1) << fabs(area) << '\n';
}