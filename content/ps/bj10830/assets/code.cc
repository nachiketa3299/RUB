#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using mat_t = vector<vector<ll>>;

int N;
ll B;
mat_t mat;

/// @brief 행렬 l과 r의 곱연산 수행
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

/// @brief 행렬 제곱 연산 최적화
mat_t mat_pow(const mat_t& m, ll p) {
  // 반환값을 단위 행렬로 초기화 시켜둠
  mat_t ret = mat_t(N, vector<ll>(N, 0));
  for (int i = 0; i < N; ++i) {
    ret[i][i] = 1;
  }

  mat_t cpy = m;

  while (p > 0) {
    // 지수가 홀수일 때 
    // (마지막에 지수가 1이 되므로 한번은 무조건 거쳐감)
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
  // 입력
  cin >> N >> B;
  mat = mat_t(N, vector<ll>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> mat[i][j];
    }
  }

  // 처리
  mat_t ret = mat_pow(mat, B);

  // 출력
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << ret[i][j] << ' ';
    }
    cout << '\n';
  }
}