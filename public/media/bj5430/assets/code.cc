#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define ERROR_STR "error"

int main() {
  int T; cin >> T; // T in [1, 100]

  for (int i = 0; i < T; ++i) {
    string p; cin >> p; // p.size in [1, 100'000]
    int n; cin >> n; // n in [o, 100'000]

    // 가공 안 된 문자열 
    string raw_seq; cin >> raw_seq; // [a,b,c,...]
    raw_seq = raw_seq.substr(1, raw_seq.size() - 2);

    // 가공 되어서 수로 변경된 문자열
    vector<int> seq; seq.reserve(n);

    stringstream ss(raw_seq);
    string token;

    while (getline(ss, token, ',')) {
      seq.push_back(stoi(token));
    }

    // 문자열의 상태 정보를 나타내는 구조체
    struct {
      int begin, end;
      bool flipped, error;
    } s_data { 0, n, false, false };

    for (auto const &cmd: p) {
      switch (cmd) {
      case 'R': // 뒤집는 경우
        s_data.flipped = !s_data.flipped;
        break;
      case 'D': // 양 끝 삭제 연산의 경우
        // 마치 반복자처럼 begin이 end와 같으면, 
        // 현재 더이상 삭제할 것이 남아있지 않음
        if (s_data.begin == s_data.end) {
          s_data.error = true;
          break;
        }

        // flipped 상태에 의존적임
        if (!s_data.flipped) ++s_data.begin;
        else --s_data.end;

        break;
      }
      if (s_data.error) break;
    }

    // 에러였으면 빠른 종료 
    if (s_data.error) {
      cout << ERROR_STR << '\n';
      continue;
    }

    // 상태에 맞게 최종 수열을 문자열로 변경하여 출력
    cout << '[';

    if (!s_data.flipped) {
      for (int i = s_data.begin; i < s_data.end; ++i) {
        cout << seq[i];
        if (i + 1 < s_data.end) cout << ',';
      }
    } else {
      for (int i = s_data.end - 1; i >= s_data.begin; --i) {
        cout << seq[i];
        if (i != s_data.begin) cout << ',';
      }
    }

    cout << ']';
    cout << '\n';
  }
}