// @date 2025-04-07
// 크기가 N*N인 행렬 A가 주어지는데, A의 B 제곱 구하는 프로그램 작성
// A^B의 각 원소를 1000으로 나눈 나머지를 출력

#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int N; ll B; // [2, 5], [1, 10^11]

vector<vector<int>> mat_mul(
  const vector<vector<int>>& a,
  const vector<vector<int>>& b
) {
  vector<vector<int>> ret(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < N; ++k) {
        ret[i][j] += a[i][k] + b[k][j];
      }
    }
  }
  return ret;
}

vector<vector<int>> mat_pow(
  const vector<vector<int>>& vec
) {

}

int main() {
  cin >> N >> B;
  vector<vector<int>> mat(N, vector<int>(N));

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> mat[i][j];
    }
  }
}