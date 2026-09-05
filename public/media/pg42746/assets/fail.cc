#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string make_string(vector<int> const &v) {
  string  s = "";

  for (auto it = v.begin(); it != v.end(); ++it) {
    s += to_string(*it);
  }
  
  return s;
}

string solution(vector<int> nums) {
  sort(nums.begin(), nums.end());
  
  string max_s = "";
  
  do {
    max_s = max(make_string(nums), max_s);
  } while (next_permutation(nums.begin(), nums.end()));
    
  return max_s;
}