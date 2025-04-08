#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using mat_t = vector<vector<ll>>;

int N;
ll B;
mat_t mat;

mat_t mat_mul(const mat_t& l, const mat_t& r) {
  mat_t ret = mat_t(N, vector<ll>(N, 0));

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < N; ++k) {
        ret[i][j] += l[i][k] * r[k][j];
      }
      ret[i][j] %= 1000;
    }
  }

  return ret;
}

mat_t mat_pow(const mat_t& m, ll p) {
  mat_t ret = mat_t(N, vector<ll>(N, 0));
  for (int i = 0; i < N; ++i) {
    ret[i][i] = 1;
  }

  mat_t cpy = m;

  while (p > 0) {
    // 지수가 홀수일 때
    if (p % 2 == 1) {
      ret = mat_mul(ret, cpy);
    }
    // 지수가 짝수일 때
    cpy = mat_mul(cpy, cpy);
    p /= 2;
  }
  return ret;
}

int main() {
  cin >> N >> B;
  mat = mat_t(N, vector<ll>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> mat[i][j];
    }
  }

  mat_t ret = mat_pow(mat, B);

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << ret[i][j] << ' ';
    }
    cout << '\n';
  }
}