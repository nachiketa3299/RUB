#include <iostream>
#include <queue>

using namespace std;

constexpr int NO_PATH = -1;

int A, B;

int bfs(int a, int depth) {
  queue<pair<long long, int>> to_visit;
  to_visit.push({a, depth});

  while (!to_visit.empty()) {
    auto [cv, cd] = to_visit.front();
    to_visit.pop();

    if (cv == B) {
      return cd;
    }

    long long p1 = cv * 2;
    long long p2 = cv * 10 + 1;

    if (p1 <= B) {
      to_visit.push({p1, cd + 1});
    }

    if (p2 <= B) {
      to_visit.push({p2, cd + 1});
    }
  }

  return NO_PATH;
}

int main() {
  cin >> A >> B;

  cout << bfs(A, 1);
}