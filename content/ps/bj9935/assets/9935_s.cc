#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
    string str, boom;
    cin >> str >> boom;

    string result;
    int boomLen = boom.length();

    for (char ch : str) {
        result += ch;

        if (result.size() >= boomLen) {
            if (result.substr(result.size() - boomLen) == boom) {
                result.erase(result.size() - boomLen);
            }
        }
    }

    if (result.empty()) {
        cout << "FRULA";
    } else {
        cout << result;
    }

    return 0;
}
