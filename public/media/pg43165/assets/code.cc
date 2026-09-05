#include <string>
#include <vector>

using namespace std;

void dfs(vector<int> const &numbers, size_t idx, int csum, int tsum, int &out_count) {
    
    // 더이상 더하거나 뺄 숫자가 남아있지 않음
    if (idx == numbers.size()) {
        if (csum == tsum) ++out_count;
        return;
    }
    
    // 다음 수를 더하는 경우
    dfs(numbers, idx + 1, csum + numbers[idx], tsum, out_count);
    
    // 다음 수를 빼는 경우
    dfs(numbers, idx + 1, csum - numbers[idx], tsum, out_count);
}

int solution(vector<int> numbers, int target) {
    int answer = 0;
    
    dfs(numbers, 0, 0, target, answer);
    
    return answer;
}