// 03-27 07:26
#include <iostream>
#include <algorithm>

using namespace std;

// 계단
// 10 20 16 25 10 
// X  X  X  X  X
// 10 
// -> i 번째 계단을 밟았을 때 최대의 점수

#define MAX_STEPS 300

int N;
int steps[MAX_STEPS];
int scores[MAX_STEPS];

int main() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> steps[i]; // [1, 10^4]
  }

  scores[0] = steps[0];

  if (N < 1) goto print;

  scores[1] = max(steps[0] + steps[1], steps[1]);

  if (N < 2) goto print;

  scores[2] = max(steps[0] + steps[2], steps[1] + steps[2]);

  for (int i = 3; i < N; ++i) {
    scores[i] = max(
      scores[i - 3] + steps[i - 1] + steps[i],
      scores[i - 2] + steps[i]
    );
  }

print:
  cout << scores[N - 1];
}