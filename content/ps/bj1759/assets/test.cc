#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

int main() {
  std::vector<int> seq {2, 1, 3};
  std::vector<bool> mask(seq.size(), false);
  std::fill(mask.rbegin(), mask.rbegin() + 2, true);

  do {
    for (int i = 0; i < seq.size(); ++i) {
      cout << (mask[i] ? '1' : '0') << ' ';
    }
    cout << '\n';
  } while (std::next_permutation(mask.begin(), mask.end()));

  do {
    for (int i = 0; i < seq.size(); ++i) {
      if (!mask[i]) continue;
      cout << seq[i] << ' ';
    }
    cout << '\n';
  } while (std::next_permutation(mask.begin(), mask.end()));
}