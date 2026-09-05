#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

using namespace std;

string make_string(vector<int> const &nums) {
    string str = "";
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        str += to_string(*it);
    }
    return str;
}

string solution(vector<int> nums) {
    auto cmp = [](auto l, auto r) {
        auto lr = to_string(l) + to_string(r);
        auto rl = to_string(r) + to_string(l);

        return lr > rl;
    };

    sort(nums.begin(), nums.end(), cmp);
    
    auto answer = make_string(nums);

    // 0 l-trim
    auto it = find_if(
        answer.begin(), answer.end(), 
        [](auto c) {return c != '0';}
    );
    answer.erase(answer.begin(), it);

    if (answer.empty()) 
        answer = "0";
    
    return answer;
}