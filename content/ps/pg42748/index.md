---
title: "프로그래머스 42748 LV1 K번째 수"
date: 2025-02-25

mathjax: true
---

아주 쉬운 문제이지만 반복자 관련 복습을 위하여 리뷰 노트를 작성한다.

우선 입력되는 벡터 `array`가 변경되면 안 되므로 매 `command`를 적용하기 이전에 복사를 하던 해야한다.

* 범위를 반복자로 잡고
* 해당 범위를 복제한 후
* 해당 범위를 정렬

위와 같은 순서로 진행하였다.

{{< hls source="assets/code.cc" syntax="cpp" >}}

아래 함수들의 사용법을 잠깐 정리하려고 썼다.

* `std::distance(first, last)`
  * `first`와 `last` 반복자간 거리를 표현하는 데에 쓰인다. 
  * 컨테이너의 `begin`과 `end`를 전달하면 컨테이너의 크기가 나옴.
* `std::next(iterator, n)`
  * `iterator` 기준 `n`만큼 뒤로 이동한 반복자를 반환한다.
  * **인자로 전달된 반복자에는 변경이 없다.**
* `std::prev(iterator, n)`
  * `std::next` 와 동일하나 이동 방향이 반대이다.
  * **인자로 전달된 반복자에는 변경이 없다.**
* `std::advance(iterator, n)`
  * `iterator`를 `n`만큼 앞이나 뒤로 이동시킨다.
  * **아무 것도 반환하지 않으며, 인자로 전달된 반복자를 변경한다.**