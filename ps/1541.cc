#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  string exp; cin >> exp;

  vector<int> parts;

  stringstream ss0(exp); 
  string p_exp;
  while (getline(ss0, p_exp, '-')) {
    stringstream ss1(p_exp);
    string op_str;
    int local_sum = 0;
    while (getline(ss1, op_str, '+')) {
      local_sum += stoi(op_str);
    }
    parts.push_back(local_sum);
  }

  int min_sum = parts[0];

  for (size_t i = 1; i < parts.size(); ++i) {
    min_sum -= parts[i];
  }

  cout << min_sum;
}
