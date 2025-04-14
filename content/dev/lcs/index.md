---
title: "[알고리즘] LCS: 가장 긴 공통 부분 수열"
date: 2025-04-03
toc: true
draft: true
---

# 개요

백준 문제를 풀이하다 LCS라는 문제를 마주했는데, 이를 조사하다가 상당히 괜찮은 주제임을 발견하고 제대로 아카이빙 한다.

# 용어의 정의

## 부분 수열(Subsequence)

> **부분 수열(Subsequence)** 이란, 어떤 주어진 수열(문자열, 리스트)에서 0개 이상의 요소를 제거하고 남은 요소들을 **원래의 순서대로 유지**하여 만든 새로운 수열을 말한다.

![](./assets/00.png)

* `str1`의 부분 수열은 `str2`, `str3`, `str4`, `str1`이다.  
* 빈 문자열과 자기 자신도 부분 수열이 될 수 있음에 주의한다.
* 순서가 섞인 `str5`는 `str1`의 부분 수열이 될 수 없다.

## 공통 부분 수열(Common Subsequence)

> **공통 부분 수열(Common Subsequence)** 은 두 개 이상의 수열이 주어졌을 때, 모든 수열에 대해 부분 수열이 되는 수열을 의미한다.

![](./assets/01.png)

* `"ADE"`는 `str1`, `str2`의 공통 부분 수열이지만, `str3`의 부분 수열은 아니다.
* `"BG"`는 모두의 공통 부분 수열이다.
* `"CF"`는 `str1`과 `str3`의 공통 부분 수열이다.
* `"HI"`는 `str2`와 `str3`의 공통 부분 수열이다.

## 가장 긴 공통 부분 수열(Longest Common Subsequence)
> **가장 긴 공통 부분 수열(LCS, Longest Common Subsequence)** 은 두 개 이상의 수열이 주어졌을 때, 그들의 공통 부분 수열 중에서, **길이가 가장 긴** 수열을 의미한다.
> LCS는 유일하지 않을 수도 있어서, 길이가 같은 여러 개의 LCS가 존재할 수 있다. 

![](./assets/02.png)

* `"ACD"`와 `"BEG"`는 `str1`과 `str2`의 LCS이며, 그 길이는 3이다.

# 이걸 대체 어디에 쓰나

이 LCS라는 것이 정말 아무짝에도 쓸모없어 보이고 알고리즘을 위한 알고리즘 처럼 보이지만 사실 현실 세계의 정말 많은 곳에서 쓰이는 고전적인 알고리즘이다.

예를 들어, `diff` 도구 같은 것이 데이터 비교를 할 때 LCS 알고리즘을 사용한다.

![](./assets/03.png)

공통 부분 수열이 아닌 것이 변경된 데이터이다.

# LCS 구하기 알고리즘

## 상향식 접근

```cpp
int LCS(int i, int j) {
  if (A[i] == '\0' || B[i] == '\0') {
    return 0;
  } 
  else if (A[i] == B[j]) {
    return 1 + LCS(i + 1, j + 1);
  } 
  else {
    return max(LCS(i + 1, j), LCS(i, j + 1));
  }
}
```

## 하향식 접근

# 참고 자료

* [4.9 Longest Common Subsequence (LCS) - Recursion and Dynamic Programming/Abdul Bari](https://www.youtube.com/watch?v=sSno9rV8Rhg&t=1255s)
  * 모든 자료들 중 유일하게 나를 이해시킴
* [Longest common subsequence/wikipedia](https://en.wikipedia.org/wiki/Longest_common_subsequence)