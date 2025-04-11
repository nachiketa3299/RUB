#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string S;

// 인덱스 기준으로 뒤집기
void rev_by_idx(string& str, int i_b, int i_e) {
  auto begin = next(str.begin(), i_b);
  auto end = next(str.begin(), i_e);
  reverse(begin, end);
}

int main() {
  // 입력
  getline(cin, S);

  int word_start_i = 0;
  bool is_in_tag = false;

  for (int i = 0; i < S.size(); ++i) {
    // 태그의 시작인가?
    if (S[i] == '<') {
      // 태그 시작 경계 이전으로 단어가 존재했는가?
      if (i != word_start_i) {
        rev_by_idx(S, word_start_i, i);
      }
      is_in_tag = true;
    }
    else if (S[i] == '>') {
      is_in_tag = false;
      word_start_i = i + 1;
    }
    // 태그 내부가 아닌 공백인가?
    else if (iswspace(S[i]) && !is_in_tag) {
      rev_by_idx(S, word_start_i, i);
      word_start_i = i + 1;
    }
  }

  // 순회 끝났는데, 혹시 단어 출력 하나 안했나?
  if (word_start_i != S.size()) {
    rev_by_idx(S, word_start_i, S.size());
  }

  // 출력
  cout << S;
}