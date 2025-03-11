---
title: "[백준] G5 암호 만들기"
date: 2025-03-11
toc: true

ps:
  link: https://www.acmicpc.net/problem/1759
  solved: 2025-03-11
---

"출력 초과"가 뜨는데, 이유를 도통 모르겠다.
누구 아는 분 있으면, 얘기 해주시길.

{{< hlc "assets/code.cc" "cpp" >}}

# 기타

## C++ STL 순열

`std::next_permutation`과 `std::prev_permutation`을 이용하면 편리하게 순열을 구할 수 있다.

### $_nP_n$ 구하기

예를 들어 어떤 수열 `{2, 1, 3}`의 **사전순 (오름차순) 순열**은 다음과 같다.

```
{1, 2, 3} (사전순으로 가장 작다)
{1, 3, 2}
{2, 1, 3} <-- 여기!
{2, 3, 1}
{3, 1, 2}
{3, 2, 1} (사전순으로 가장 크다)
```

`std::next_permutation`과 `std::prev_permutation`은 입력받은  범위의 수열을 사전순으로 다음 순열, 혹은 이전 순열로 변경하려고 하며 변경에 성공한 경우 `true`를 반환한다. 

만일 더 이상 다음/이전 순열이 존재하지 않는 경우 `false`를 반환한다.

[주의] `false`를 반환하더라도, 전달받은 범위를 변경한다:
* `{3, 2, 1}`에다 `std::next_permutation`을 호출하면 `false`를 반환하고 `{1, 2, 3}`이 된다.
* `{1, 2, 3}`에다 `std::prev_permutation`을 호출하면 `false`를 반환하고 `{3, 2, 1}`이 된다.

보통 다음처럼 Do-While 문과 함께 쓴다.

```cpp{lineNos=false}
std::vector<int> seq { 2, 1, 3 };

do {
  for (const auto& e: seq) cout << e << ' ';
  cout << '\n';
} while (std::next_permutation(seq.begin(), seq.end()));

// 이 시점에서 seq은 1, 2, 3

// 3, 2, 1로 만들어줌
std::prev_permutation(seq.begin(), seq.end());

do {
  for (const auto& e: seq) cout << e << ' ';
  cout << '\n';
} while (std::prev_permutation(seq.begin(), seq.end()));

// 이 시점에서 seq은 3, 2, 1
```

### $_nP_r$ 구하기

$n$개 중에 $r$개를 뽑고 싶은 경우 다음과 같이 하면 안된다!

다음은 수열 `{2, 1, 3}`에서 2개의 원소를 순서 있이 뽑는 예제이다.

```cpp{lineNos=false}
std::vector<int> seq { 2, 1, 3 };

do {
  for (int i = 0; i < 2; ++i) {
    cout << seq[i] << ' ';
  }
  cout << '\n';
} while(std::next_permutation(seq.begin(), seq.end())); 
```

결과는 아래와 같다.

```
{{2, 1}, 3} <-- 시작!
{{2, 3}, 1}
{{3, 1}, 2}
{{3, 2}, 1} <-- 끝!
---
{{1, 2}, 3} <-- 그러나, 사실 끝이 아니었다...
...
```

이렇게 정렬되지 않은 수열에서 뽑으려고 하면, `std::next_permutation`이 순열 끝에 도달했다고 판단해버리고 더이상 진행하지 않는다. 
그래서 정렬되지 않은 수열에서는 원하는 모든 쌍을 뽑을 수가 없다.

이걸 해결하는 법은 두 가지가 있는데,
1. 수열 자체를 오름차순으로 정렬한다.
2. 오름차순으로 정렬하기 싫으면, **인덱스를 기억하는 수열**을 새로 만든다.

1번이야 쉬우니 넘어가도, 2번의 예는 아래와 같다.

```cpp{lineNos=false}
std::vector<int> seq { 2, 1, 3 };
std::vector<int> indices(seq.size());
std::iota(indices.begin(), indices.end(), 0); // { 0, 1, 2 }

do {
  for (int i = 0; i < 2; ++i) {
    cout << seq[indices[i]] << ' ';
  }
  cout << '\n';
} while(std::next_permutation(indices.begin(), indices.end())); 
```

출력은 아래와 같다. (뒤는 인덱스의 순열이다)

```
{{2, 1}, 3} - {{0, 1}, 2} <-- 시작
{{2, 3}, 1} - {{0, 2}, 1}
{{1, 2}, 3} - {{1, 0}, 2}
{{1, 3}, 2} - {{1, 2}, 0}
{{3, 2}, 1} - {{2, 0}, 1}
{{3, 1}, 2} - {{2, 1}, 0} <-- 끝
```

인덱스처럼 추가적인 정보를 순열에 돌리는 테크닉이 꽤 괜찮다. 조합을 구현할 때에도 사용된다.

## 조합은 어떻게?

$_nP_r$에서 `indices` 배열을 추가 관리했듯이, 이번에는 `mask`라는 정보를 관리해 본다.

코드로 이해하는 것이 더 빠르다: 수열 `{2, 1, 3}`에서 2개를 뽑아 조합하는 예제이다.

```cpp{lineNos=false}
std::vector<int> seq {2, 1, 3};
std::vector<bool> mask(seq.size(), false);
std::fill(mask.rbegin(), mask.rbegin() + 2, true);

do {
  for (int i = 0; i < seq.size(); ++i) {
    if (!mask[i]) continue;

    cout << seq[i] << ' ';
  }
  cout << '\n';
} while (std::next_permutation(mask.begin(), mask.end()));
```

`mask`로 조합에서 뽑을 갯수만큼 `true`로 마킹해주자.
핵심은 뒤에서부터 마킹하여 오름차순을 유지하는 것. (앞에서부터 마킹한 후 `std::reverse`로 뒤집어 주어도 좋다.)

`mask` 배열을 순열로 돌린 후, `mask`가 있는 부분만 출력하면 조합이 완성된다. 

구체적으로 출력은 다음처럼 작동한다:
```
{ 2,  [1], [3]} - {0, 1, 1}
{[2],  1,  [3]} - {1, 0, 1}
{[2], [1],  3 } - {1, 1, 0}
```

## 백 트래킹

모든 경우의 수를 탐색하면서도, 불필요한 경로를 가지치기(프루닝)하여 효율적으로 탐색하는 기법이다.

보통 재귀를 사용하여 해집합을 구성하고, 적합하지 않은 경우를 배제한다.

백트래킹은 보통 **깊이 우선 탐색**을 기반으로 한다.

기본 단계는 다음과 같다.
* 탐색 시작
* 현재 상태가 유망한지 확인.
  * 유망하지 않다면 (애초에 불가능한 경로라면) 더 깊이 탐색하지 않고 **가지치기**
* 목표한 상태에 도달하면 해를 저장하거나 출력
* 가능한 모든 선택지를 시도한 후, 이전 상태로 되돌아가기 (**백트랙**)
  * 되돌아가면서 다른 선택지를 탐색한다.

즉, 한 경로를 따라 탐색하다가 유효하지 않으면 바로 되돌아가는 것이 백트래킹이다.

DFS는 단순히 모든 경로를 탐색하나, 백트래킹은 유망하지 않은 경로에 대한 탐색을 빠르게 포기하여 탐색량을 줄이는 데에 그 의의가 있다.

## 예제 - 순열 구현

백 트래킹을 이용해 순열을 직접 구현하면 아래와 같다.

```cpp
#include <iostream>
#include <vector>

using namespace std;

void _perm_dfs(const vector<int>& seq, int size, vector<int>& path, vector<bool>& used) {
  if (path.size() == size) {
    for (const auto& e: path) {
      cout << e << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = 0; i < used.size(); ++i) {
    if (used[i]) continue;

    path.push_back(seq[i]);
    used[i] = true;

    _perm_dfs(seq, size, path, used);

    path.pop_back();
    used[i] = false;
  }
}

void perm(const vector<int>& seq, int size) {
  vector<int> path; path.reserve(size);
  vector<bool> used(seq.size(), false);

  _perm_dfs(seq, size, path, used);
}

int main() {
  perm({1, 2, 3}, 2);
}
```

## 예제 - 조합 구현

조합도 아래처럼 구현할 수 있다.

```cpp
void _comb_dfs(const vector<int>& seq, int size, vector<int>& path, int start) {
  if (path.size() == size) {
    for (const auto& e: path) {
      cout << e << ' ';
    }
    cout << '\n';
    return;
  }

  for (int i = start; i < seq.size(); ++i) {
    path.push_back(seq[i]);
    _comb_dfs(seq, size, path, i + 1);
    path.pop_back();
  }
}

void comb(const vector<int>& seq, int size) {
  vector<int> path; path.reserve(size);

  _comb_dfs(seq, size, path, 0);
}

int main() {
  comb({ 1, 2, 3, 4, 5 }, 3);
}
```