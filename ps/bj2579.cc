// @date 2025-03-26 09:50

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// 계단은 한 번에 한 계단 또는 두 계단씩
// 1. 한 계단 혹은 두 계단씩 오르기
//    * 한 계단을 밟으면 이어서 다음 계단이나 다음 다음 계단으로 오를 수 있음
// 2. 연속된 세 개의 계단을 모두 밟아서는 안되는데, 시작점은 포함 X
// 3. 마지막 도착 계단은 반드시 밟아야 함

int N; // 계단의 개수 [1, 300]
vector<int> steps;


int main() {
  cin >> N;
  steps = vector<int>(N);
  for (int i = 0; i < N; ++i) {
    cin >> steps[i]; // [1, 10^4]
  }

  vector<int> dp(N, INT_MIN); // dp[i] 는 i번 계단까지 최대 점수

  dp[0] = steps[0]; // 첫 번째 계단 밟았을 때 점수

  if (N <= 1) {
    cout << dp.back();
    return 0;
  }

  dp[1] = max({
    dp[0] + steps[1], // 한칸씩 올라옴
    steps[1], // 그냥 바로 두번째 계단으로 짬프
    dp[1] // 로직 일관성을 위한 더미
  });

  // 세번째부터 가봅시다
  for (int i = 2; i < N; ++i) {
    // one 은 한칸 한칸 올라온 것
    // two 는 두칸 짬프한 것
    int one, two;

    // 연속해서 올라온 경우
    int seq_one = dp[i - 2] + steps[i - 1] + steps[i];
    // 한 칸 이전에서 한칸 올라온 경우
    one = dp[i - 1]  + steps[i];

    // 이전에서 한칸 올라온 경우가 연속해서 올라온 경우인지 판단
    one = one == seq_one ? INT_MIN : dp[i - 1] + steps[i];

    // 두 칸 이전에서 두 칸 올라온 경우
    two = dp[i - 2] + steps[i];

    dp[i] = max({one, two, dp[i]});
  }
  cout << dp[N - 1];
}