#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;

vector<int> seq;

vector<bool> used;
vector<int> path;

void dfs_print() {
  if (M == path.size()) {
    for (const auto& e: path) {
      cout << e << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = 0; i < seq.size(); ++i) {
    if (used[i]) {
      continue;
    }

    used[i] = true;
    path.push_back(seq[i]);
    dfs_print();
    path.pop_back();
    used[i] = false;
  }
}

int main() {
  cin >> N >> M;

  seq = vector<int>(N);
  used = vector<bool>(N, false);
  path.reserve(M);

  for (int& e: seq) {
    cin >> e; // [1, 10^4]
  }

  sort(seq.begin(), seq.end());
  dfs_print();
}