#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

int K, L;
vector<string> nums;

list<string> wait_q;
unordered_map<string, list<string>::iterator> redundant;

int main() {
  cin >> K >> L;

  nums.resize(L);
  for (int i = 0; i < L; ++i) {
    cin >> nums[i];
  }

  for (const string& num: nums) {
    // 한번 봤던 거임
    if (redundant.find(num) != redundant.cend()) {
      wait_q.erase(redundant[num]);

      wait_q.push_back(num);
      redundant[num] = prev(wait_q.end());
    // 첨 보는거임
    } else {
      wait_q.push_back(num);
      redundant[num] = prev(wait_q.end());
    }
  }

  int count = 0;

  for (const string& num: wait_q) {
    cout << num << '\n';
    ++count;
    if (count == K) {
      break;
    }
  }
}