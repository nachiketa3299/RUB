---
title: "[C++] 비트 마스크"
date: 2025-05-01
lastmod: 2025-05-05
toc: true
---

# C++에서 비트 마스킹

비트 마스킹 문제를 풀면 보통 `int` 나 `long long` 처럼 기본 자료형을 사용한다.

하지만 C++에는 이미 비트 단위 연산에 최적화된 `std::bitset` 클래스 템플릿을 제공하고, 사용법을 조금만 알면 훨씬 편리하고 안전하고, 효율적으로 비트 단위 연산을 수행할 수 있다.

# `std::bitset`이란?

{{<admo title="`std::bitset`이란?">}}

`std::bitset<N>`은, `N`의 고정된 크기를 갖는 비트의 연속을 표현할 수 있는 클래스 템플릿이다.

{{</admo>}}

`int` 나 `long long` 등을 비트 마스킹 용도로 사용했을 때에는 해당 자료형의 비트 길이를 모두 써야 했는데, `bitset`을 사용하면 임의의 `N` 크기를 빌려올 수 있으니 매우 편리하다.

또한, 마치 그 자체가 비트 스트림인 것처럼 기본 논리 연산자와 함께 사용할 수 있으며, 이러한 비트의 나열을 문자열이나 다른 정수형으로 쉽게 변환할 수도 있다.

[^1]: 문자열이나 정수로 표현할 때에는 가장 낮은 인덱스의 요소가 우측에 있는 것으로 표현된다.

# `std::bitset`의 기본적 사용법

## 초기화

```cpp{lineNos=false}
// 0b 000'0000
bitset<7> b1;

// 0b 1010
bitset<4> b2{0xA};

// 0b 001
bitset<3> b3{33};

// 0b 0011
bitset<4> b4{"0011"};

// 0b 0000'0110
bitset<8> b5{"ABBA", size_t(4), /*0:*/'A', /*1:*/'B'};
```

## 멤버 접근 및 변경

```cpp{lineNos=false}

// 예외 처리를 하지 않는 인덱스 접근
b[1] = 1;

// 예외 처리를 하는 인덱스 접근으로, 비트를 1로
b.set(2);

// 전체 비트를 1로
b.set();

// 예외 처리를 하는 인덱스 접근으로, 비트를 0으로
b.reset(2);

// 전체 비트를 0으로
b.reset();

// 전체 비트를 역전시킴
b.flip();
```

## 멤버 갯수

```cpp{lineNos=false}
// 비트의 크기
b.size();

// true인 것들의 개수
b.count();
```

## 멤버십 테스트

```cpp{lineNos=false}
// 특정 인덱스의 비트가 1인지 확인
b.test(3);   // true

// 하나라도 1이면 true
b.any();     // true

// 전부 0이면 true
b.none();    // false

// 전부 1이면 true
b.all();     // true
```

## 다른 자료형으로 변환

```cpp{lineNos=false}
// 숫자 값으로 변환
unsigned long x = b.to_ulong();
unsigned long long y = b.to_ullong();
string z = b.to_string();

// 출력
cout << b << '\n';
```

# 비트 연산자와 `std::bitset`

아래 연산자와 아래 연산자를 이용한 복합 비트 연산자는 모두 `std::bitset`과 함께 쓸 수 있다.

| 연산자 | 의미 |
| :-: | :-: |
| `~` | NOT |
| `&`, `&=` | AND |
| `\|`, `\|=` | OR |
| `^`, `^=` | XOR |
| `<<`, `<<=` | Left Shift |
| `>>`, `>>=` | Right Shift |

{{<admo type="NOTE">}}

길이가 *다른* `bitset` 끼리 직접 비트 연산을 할 수 없고, 컴파일 오류를 발생시킨다.

```cpp{lineNos=false}
bitset<3> b1;
bitset<4> b2;
b1 |= b2; // Error!
```

{{</admo>}}

# 연습 문제

[\[백준\] 13701 G4 중복 제거](https://www.acmicpc.net/problem/13701)을 `bitset`을 활용하여 풀이하면 아래와 같다.

* 최대 $2^{25}$개의 정수를 입력받는데, 이 중에 중복된 수가 있을 수 있다고 한다.
* 입력받은 순으로 출력하되, 중복된 것은 출력하지 않아야 한다. 
* 입력되는 정수는 $0$ 이상, $2^{25}$ 미만이라고 한다.

`std::bitset`을 이용하여, $0$부터 $2^{25}$까지 모든 정수에 대해서 각 정수의 중복 여부를 표시하는 1 비트를 빌려오자.  
쉽게 말해, $\verb|bitset<|2^{25}\verb|>|$로 범위 내의 모든 정수에 대응하는 1 비트를 빌려오자는 뜻이다.

$2^{25}$ 비트는 대략 4 MB 을 차지하며, 이는 문제 조건을 넉넉히 통과한다.

코드는 아래와 같다.

```cpp
#include <iostream>
#include <bitset>

using namespace std;

constexpr int MAX_VALUE = 1 << 25; // 2^25

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  bitset<MAX_VALUE> seen;

  int x;
  while (cin >> x) {
    if (!seen[x]) {
      seen[x] = true;
      cout << x << ' ';
    }
  }
}
```

# `bitset`을 쓸 때 주의할 점들 

## 1비트에 대한 "진짜 참조"는 없다.

`bitset`은 내부적으로 보통 `unsigned long`이나 `unsigned long long`의 배열로 비트를 관리한다.

```cpp{lineNos=false}
bitset<32>{}[31] = true;
```

위 예제처럼 개별 비트에 대입하는 문법은, 실제로 31번째 비트에 대한 lvalue에 접근하는 것 처럼 보이지만, ==하드웨어 메모리는 최소 1바이트 단위로만 주소 접근이 가능하므로, 단일 비트 자체에 대한 포인터나 진짜 참조는 존재할 수 없다.==

그래서 `std::bitset`은 내부적으로 `bitset<N>::reference`라는 프록시 객체를 사용하여 개별 비트에 대한 읽기/쓰기를 흉내낸다. 이 객체는 실제 참조는 아니며, 해당 비트가 소속된 바이트를 읽고 쓰는 방식으로 작동한다. 이 과정에서 동일한 바이트에 포함된 다른 비트들 함께 읽거나 쓰게 될 가능성이 있다.

즉, `b[i] = true`는 `i`번째 비트만 영향을 주는 것 처럼 보이지만, 실제로는 `i / 8` 번째 바이트 전체가 연산 대상인 것이다.

## 실제 `bitset`이 점유하는 공간은 메모리 정렬을 따져 봐야 안다.

```cpp{lineNos=false}
sizeof(bitset<25>{}); // 25가 아님!
```

또한, `bitset`의 실제 메모리 배치는 내부에서 사용하는 타입(보통 `unsigned long`)의 정렬 규칙을 따르므로, 예를 들어 `bitset<25>`는 논리적으로 25비트만 필요하지만, 실제로는 `unsigned long` 단위로 할당되어 32비트, 혹은 그 이상의 공간을 점유하게 된다.


## 컴파일 타임에 크기가 고정된 비트 시퀀스에만 쓰자.

`bitset`은 크기가 **컴파일 타임에 고정된 비트 시퀀스**를 표현할 때 쓴다.

크기가 런타임에 결정되는 비트 시퀀스의 경우, 다른 구조를 고려하는 것이 더 적절하다.

{{<admo title="`vector<bool>`이라는 함정" type="NOTE">}}

크기가 런타임에 결정되는 비트 시퀀스를 위해 C++ 표준 라이브러리는 `vector<bool>`이라는 `vector<T>`의 특수화 클래스를 제공한다.

C++에서 `bool` 형식은 논리적으로는 1비트만 사용하지만, 실제로는 메모리 정렬 요구사항 때문에 최소 1바이트(8비트)를 차지한다.

`vector<bool>`은 일반적인 `vector<T>`와 달리 공간 효율성을 높이기 위한 **비트 단위 최적화(Packing)** 가 구현되어 있어, 각 `bool` 요소가 실제로 1비트만 차지한다. 이는 메모리 사용량을 8배까지 줄일 수 있다.

그러나 이러한 최적화로 인해 `vector<bool>`은 다른 `vecotor<T>`와 다른 특수한(이상한) 동작을 보인다.
* 요소에 대한 진짜 참조를 반환하지 않는다.
* 요소의 주소는 아예 받아올 수도 없다.
* 일부 다른 STL 알고리즘과 호환이 되지 않느다.
* 비트 단위 연산자를 지원한다.

이런 특징들로 `vecotr<bool>`은 다른 모든 `vector<T>` 컨테이너와 다르게 동작하고, C++ 표준 라이브러리에서 유일하게 컨테이너 요구사항을 완전히 만족시키지 않는다.

C++ 커뮤니티에서는 이런 `vector<bool>`의 설계가 *최소 놀라움의 원칙*을 위반하고, 예측 불가능한 동작을 초래한다는 비판이 많다. 대부분은 가능하면 사용하지 말 것을 권고한다는 입장을 취하고 있다.

따라서 런타임에 크기가 변할 수 있는 비트 시퀀스가 (정말로) 필요하다면, 다음과 같은 대안을 고려하는 것이 좋다.

* `vector<unsigned char>`나 `vector<unsigned long>` 처럼 정수 벡터를 사용하여 직접 구현
* `deque<bool>` 사용
* Boost 라이브러리의 `boost::dynamic_bitset` 활용

{{</admo>}}


# 참고 문헌

* [std::bitset/cppreference.com](https://en.cppreference.com/w/cpp/utility/bitset)
* [vector<bool>보기를 돌같이 해라/껍데기방](https://husk321.tistory.com/m/366)

