---
title: "[백준] 9935 G4 문자열 폭발"
date: 2025-05-05
toc: true
ps:
  site: 백준
  id: 9935
---

정답률이 26%인 문제이니 나만 어려웠던 문제가 아니다.

검색 당하는 문자열은 최대 $10^{6}$ 크기이고, 폭발 문자열은 끽해야 $10$ 크기이다.

# 나이브한 풀이

떠올릴 수 있는 가장 쉬운 풀이는 바로, **문자열에서 폭발 문자열이 더이상 검출되지 않을 때까지 검색하고 지우는 것** 이다.

```cpp{lineNos=false}
string str, boom_str; 
cin >> str >> boom_str;

size_t pos;

do {

  pos = str.find(boom_str); // NO!!!

  if (pos != string::npos) {
    str.erase(pos, boom_str.length());
  }

} while (pos != string::npos);
```

문제는 표준 라이브러리에서 `find`의 복잡도가 매우 비효율적이라는 것이다.

## `std::string::find`는 최악 시간 복잡도 보장이 없다.

==표준 라이브러리의 문자열 검색 함수 `find`에는 최악 시간 복잡도 보장이 존재하지 않는다.==

검색 당하는 문자열의 크기를 $N$, 검색 하는 문자열의 크기를 $M$이라고 하자.  
대부분의 구현체(GCC, Clang, MSCV)에서 *단순한 루프 기반 검색* 을 진행하므로, 복잡도는 $O(N \cdot M)$이다. KMP나 Boyer-Moore 같은 최적화된 문자열 검색 알고리즘을 사용하지 않고, 아주 단순한 비교 방식으로 구현되어 있다.

전체 문자열이 모두 폭발 문자열로 구성된 경우, 폭발 문자열은 총 $\frac{N}{M}$개 존재한다. 매 순회마다 전체 문자열의 길이가 줄어드므로 정확하다고 볼 수는 없겠지만, 복잡도는 $O(N \cdot M \cdot \frac{N}{M}) = O(N^2)$에 근사한다고 볼 수 있다.

$N = 10^6$이기 때문에 이러한 방식, 즉 폭발 문자열이 더 이상 탐색되지 않을 때까지 폭발 문자열을 찾아 없애는 방법으로는 이 문제를 시간 내에 풀 수가 없다. 실제로 위 방식으로 제출하면 시간 초과가 뜬다.

# `find`를 안 쓰고, 딱 한번만 순회하는 법

위 풀이의 가장 큰 문제점은 `std::string`의 `find`가 매우 비효율적이며, 이를 통제할 수 있는 방법이 사실상 없기 때문이다. 즉, `find`를 쓰면 안된다.

또한, $10^6$의 문자열을 다루고 있으므로, 제한 시간 2초 내로 통과하려면, **문자열을 단 한번만 순회** 하여 답을 도출하는 것이 핵심임을 알 수 있다.

문자열의 문자를 하나 하나 검사한다고 가정하자. ==검사하고 있는 *문자열의 현재 문자*가 *폭발 문자열의 마지막 문자*와 동일하다면, 문자열 내에서 현재 문자부터 폭발 문자열 이전까지 다시 읽어서 실제로 폭발 문자열이 문자열에 포함되어 있는지 확인할 수 있지 않을까?==

```cpp{lineNos=false}
string result;

for (char ch: str) {
  result += ch; // 하나씩 붙여 본다

  // 지금 붙여놓은 문자열 길이가 애초에 폭발 문자열보다 짧으면, 
  // 확실히 지금 폭발이 존재할수가 없는 상황이므로 빠르게 가지치기 한다.
  if (result.length() < boom_str.length()) {
    continue;
  }

  // 지금 붙인 문자가, 폭발 문자열 마지막 문자랑 같지 않으면,
  // 역시 지금 문자부터 거꾸로 읽어서 폭발 문자열을 완성시킬 가능성이 없다.
  if (result.back() != boom_str.back()) {
    continue;
  }

  // 실제로 현재 문자부터 폭발 문자열 길이만큼 거꾸로 읽어봤을 때
  // 폭발 문자열이랑 다른 경우 종료한다.
  size_t pos = result.length() - boom_str.length();
  if (result.substr(pos) != boom_str) { // 이 부분이 병목
    continue;
  }

  // 여기까지 도달했다면, 폭발 문자열이 실제로 존재한 것이다.

  result.erase(pos); // 항상 문자열의 끝 부분만 잘라냄
}
```

이 방식의 복잡도를 분석해 보자.

* 단 한번 문자열을 훑으면서, `result` 라는 결과 문자열을 만들어 나가므로, $O(N)$이다.
* 매 순회마다 다음이 일어난다:
  * 문자를 `result`에 추가: $O(1)$
  * 길이 체크: $O(1)$
  * 마지막 문자 비교: $O(1)$
  * 실제로 폭발 문자열인지 검사(`result.substr(pos)`): $O(M)$
  * 폭발 문자열 삭제(`result.erase(pos)`): $O(M)$
    * 항상 문자열의 마지막 부분을 $M$만큼 삭제하기 때문

따라서 각 문자당 최대 $O(M)$의 작업이 수행된다. 폭발이 일어나면서 문자열이 줄어드므로 실제로는 이것보다 빠르겠지만, 어쨋든 전체 시간 복잡도는 $O(N \cdot M)$에 근사한다. 최악의 경우 $O(10^7)$의 연산이 필요하다는 것인데, 이는 제한 시간 2초 내에 충분히 해결 가능한 작업량이다.

# 코드

{{<hlc "assets/9935_s.cc" "cpp">}}

# 참고 문헌

* [`std::basic_string<CharT, Traits, Allocator>::substr`/cppreference](https://en.cppreference.com/w/cpp/string/basic_string/substr)
* [`std::basic_string<CharT, Traits, Allocator>::find`/cppreference](https://en.cppreference.com/w/cpp/string/basic_string/find)