---
title: "[C++] 비트 마스크"
date: 2025-05-01
toc: true
---

# C++에서 비트 마스킹

비트 마스킹 문제를 풀면 보통 `int` 나 `long long` 등을 사용한다. 

때로는 `std::vector<bool>`를 사용하기도 한다. `std::vector<bool>`은 `std::vector<T>`의 특수화된 버전으로, 비트 레벨로 최적화 되어 있어 다른 `std::vector`와는 조금 다르게 작동한다.

하지만, C++은 이미 비트 단위 연산에 최적화된 `std::bitset`을 클래스 템플릿을 제공하며, 이 글에서는 그 사용법에 대해서 알아보도록 한다.

# `std::bitset`

{{<admo title="`std::bitset`">}}

`std::bitset<N>`은, `N`의 고정된 크기를 갖는 비트의 연속을 표현할 수 있는 클래스 템플릿이다.

{{</admo>}}

`std::bitset`은 기본 논리 연산자들과 함께 사용될 수 있으며, 비트의 나열을 문자열이나 정수로 쉽게 변환할 수도 있다.[^1]

[^1]: 문자열이나 정수로 표현할 때에는 가장 낮은 인덱스의 요소가 우측에 있는 것으로 표현된다.

# `std::bitset`의 기본적 사용법

## 초기화

```cpp{lineNos=false}
// 0b 000'0000
bitset<7> b1;

// 0b 1010
bitset<4> b2{0xA};

// 0b 0011
bitset<4> b3{"0011"};

// 0b 0000'0110
bitset<8> b4{"ABBA", size_t(4), /*0:*/'A', /*1:*/'B'};
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

길이가 다른 `bitset`끼리는 직접 비트 연산을 할 수는 없다.

```cpp{lineNos=false}
bitset<4> b{"0011"};

b3 |= 0b0100;
b3 &= 0b0011;
```

{{<admo type="NOTE">}}

길이가 다른 비트마스크끼리의 연산은 컴파일 오류를 발생시킨다.

```cpp{lineNos=false}
bitset<3> b1;
bitset<4> b2;
b1 |= b2; // Error!
```

{{</admo>}}

```cpp
#include <iostream>

int main() {

}
```

# 참고 문헌

* [std::bitset/cppreference.com](https://en.cppreference.com/w/cpp/utility/bitset)

