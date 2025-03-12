---
title: "[C++] 중괄호 초기화의 모든 것"
toc: true
description: "C++의 중괄호 초기화의 등장 배경과 장점, 사용법을 설명합니다."
keywords: ["C++", "중괄호 초기화", "Braced Initialization", "모던 C++", "균일 초기화", "유니폼 초기화"]
date: 2025-03-12
---

# 개요

중괄호 초기화는 **중괄호 `{}`를 사용하는 모든 초기화 방식을 포괄하는 용어**이며, 표준에서는 이를 **목록 초기화(List Initialization)**라고 부른다.

```cpp{lineNos=false}
int x{10};
int y = {10};
std::vector<int> v{1, 2, 3};
```

이처럼 ==다양한 타입의 객체들을 **일관성 있게** 초기화 할 수 있다는 것이 큰 장점==이다.

그러나, 같은 `{}`를 사용한 초기화여도 작동 방식이 조금씩 다를 수 있으므로 주의가 필요하다. 

# 왜 써야할까? - Most Vexing Parse 해결

```cpp{lineNos=false}
int main() {
  Foo foo(); // ??
  Foo ffoo(Bar()); // ????
}
```

`Foo foo()`는 `Foo`의 기본 생성자를 호출할 의도로 작성하였겠으나, 컴파일러는 이를 **반환값이 `Foo`이고 매개변수가 없는 함수 원형 선언**으로 해석한다.

`Foo ffo(Bar())`는 더 기묘한 예인데, `Bar`형 임시 객체를 전달하여 걸맞는 `Foo`의 생성자를 호출할 의도로 작성되었겠지만, 컴파일러는 이를 **반환 형식이 `Foo`이고, 매개 변수로는 반환값이 `Bar`이고 매개 변수로 아무것도 받지 않는 익명 함수 포인터를 받는 함수 선언**과 구별할 수 없다고 판단한다.

이를 C++의 [Most Vexing Parse](https://en.wikipedia.org/wiki/Most_vexing_parse) 문제라고 하며, 이 문제의 해결책 중 하나가 중괄호 초기화이다.

다음처럼 중괄호 초기화를 사용하면 명확한 의도를 전달할 수 있다.

```cpp{lineNos=false}
int main() {
  Foo foo{}; // 명확해!
  Foo ffo{Bar{}}; // 너무 명확해!!
}
```

# 종류

## 직접 목록 초기화 (Direct List Initialization)

```cpp{lineNos=false}
int a{10};
std::vector<int> v{1, 2, 3};
Foo foo{10, 10};
```

직접 목록 초기화에서는 명시적으로 `{}`와 인자를 전달하여 개체를 초기화한다.  

전달된 인자에 맞는 가장 적절한 생성자를 찾아 호출하려고 한다:
* `std::initializer_list`를 받는 생성자가 존재한다면, 가장 먼저 선택된다.
* 없는 경우, 가장 적절한 생성자를 선택한다.

이 방식으로 `explicit` 생성자도 호출이 가능하다.

### `std::initializer_list` 우선순위

`std::initializer_list`를 받는 생성자를 가장 먼저 우선한다는 것을 주의해야 한다.

```cpp{lineNos=false}
std::vector<int> vec_0(5, 10); // 크기 5, 모든 요소 10
std::vector<int> vec_1{5, 10}; // 요소가 5, 10
```

`std::vector`에는 `std::initializer_list`를 받는 생성자가 있으므로 중괄호로 인자를 전달하면 해당 생성자가 최우선적으로 호출되어, 크기와 기본값이 아닌 **요소들의 목록으로 해석**된다.

## 복사 리스트 초기화 (Copy List Initialization)

```cpp{lineNos=false}
int b = {20};
std::vector<int> v = {1, 2, 3};
Foo foo = {10, 10};
```

`=` 연산자를 이용한 중괄호 초기화이다.  
`explicit` 생성자는 호출되지 않으며, 암시적 변환이 허용된다.  

실제로는 임시 객체를 생성한 후 복사/이동하는 과정으로 설계되었으나, C++17 이후 이런 상황에서 복사 생략이 의무화된 관계로 복사가 일어나지는 않는다.

## 값 초기화 (Value Initialization)

```cpp{lineNos=false}
int c{};
std::string s{}; // 빈 문자열
Foo foo{}; // 기본 생성자
```

내장형(Primitive) 타입이면 0으로 초기화된다.  
클래스 타입이면 기본 생성자를 호출한다.  

## 집계 초기화 (Aggergate Initialization)

```cpp{lineNos=false}
struct Foo { int x, y; };
Foo foo{10, 20};
int arr[] {1, 2, 3};
std::array<int, 3> s_arr {1, 2, 3}; // 주의!
```

**집계체(Aggergate)**에 대해 각 멤버들을 중괄호 `{}`로 직접 초기화 할 수 있다.  
배열 또한 집계체이므로, 같은 방식으로 초기화 할 수 있다.

### 집계체?

C++ 표준에서 **집계체**는 다음 조건을 만족하는 클래스, 구조체, 배열이다.
* 모든 멤버 변수가 `public`이다.
* 사용자 정의 생성자가 아예 존재하지 않는다.
* 가상 함수가 없다.
* (가상) 상속 구조에 속해 있지 않다.

POD와 비슷한 개념이지만, POD는 집계체보다 조금 더 엄격한 개념이다.  
POD는 모든 멤버가 POD여야 하고, 멤버 함수 또한 없어야 한다.  
모든 POD는 집계체이나, 집계체라고 POD는 아니다.  

### `std::array` vs `std::vector`

`std::array`의 구현을 단순화해보면 아래와 같다. (MSVC 기준)

```cpp{lineNos=false}
template <class T, std::size_t N>
class array {
  T elems[N];
};
```

`std::array`는 C 스타일 배열을 안전하게 감싸는 역할만 수행하는 집계체이다. 즉, C 스타일 배열과 동일하게 초기화될 수 있도록 설계되었다.

`std::array`에는 사용자 정의 생성자가 존재하지 않으며 당연히 `std::vector`처럼 `std::initializer_list`를 받는 생성자도 존재하지 않는다.

```cpp{lineNos=false}
int arr[] {1, 2, 3};                // 집계 초기화
std::array<int, 3> s_arr {1, 2, 3}; // 집계 초기화
std::vector<int> vec {1, 2, 3};     // 직접 목록 초기화
```

때문에 위 두 초기화는 비슷해 보이지만, 내부적으로는 꽤 다르게 작동한다고 볼 수 있다.

# 특징 

## 축소 변환 방지

중괄호 초기화의 중요한 특징으로, 축소 변환을 방지한다.

```cpp{lineNos=false}
double d = 3.14;
int x1 = d;
int x2 {d}; // 컴파일 오류: double -> int 금지
```

그러나, 작은 형식으로 변환하는 **축소 변환만 방지**함을 유의한다.

```cpp{lineNos=false}
char c{65}; // int -> char 허용 안됨
int i{'c'}; // char -> int 허용됨
```

## 중괄호 생략 가능

중첩 배열을 초기화할 때 내부 중괄호를 생략할 수 있다.

```cpp{lineNos=false}
int mat[2][2] { 1, 2, 3, 4 }; // {{1, 2}, {3, 4}} 와 같다
```

이런게 가능한 줄은 꿈에도 몰랐다.
