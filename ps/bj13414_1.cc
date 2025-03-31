#include <iostream>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

int K, L;

vector<string> nums;
unordered_map<string, list<string>::iterator> umap;
list<string> seqs;

int main() {
  cin >> K >> L;
  nums.reserve(L);

  for (int i = 0; i < L; ++i) {
    string num; cin >> num;
    nums.push_back(num);
  } 

  for (const string& num: nums) {
    // 처음 보는 경우
    if (umap.find(num) == umap.end()) {
      seqs.push_back(num);
      umap[num] = --seqs.end();
    // 중복되어 보는 경우
    } else {
      // 위치를 알고 있으므로 지워준다
      seqs.erase(umap[num]);

      seqs.push_back(num);
      umap[num] = --seqs.end();
    }
  }

  int count = 0;
  for (const string& num: seqs) {
    cout << num << '\n';
    ++count;
    if (count == K) {
      break;
    }
  }
}