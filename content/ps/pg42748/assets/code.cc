#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
  vector<int> answer;
  
  for (auto const& cmd: commands) {
      
    auto rb = next(array.cbegin(), cmd[0] - 1);
    auto re = next(array.cbegin(), cmd[1]);
    
    vector<int> carr(rb, re);
    
    sort(carr.begin(), carr.end());
    
    auto target = *next(carr.cbegin(), cmd[2] - 1);
    answer.push_back(target);
  }
    
    return answer;
}