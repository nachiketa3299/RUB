---
title: "수식 표기법"

categories: ["알고리즘"]

date: 2025-05-06
lastmod: 2025-05-07
toc: true
mathjax: true
---

# 정의

{{<admo title="수식 표기법이란?">}}

수식 표기법은 피연산자가 둘인 이항 연산(Binary Operation)을 표현하는 방식이다. 

연산자와 피연산자가 어느 위치에 있냐에 따라서 전위, 중위, 후위 표기법으로 나눈다.

{{</admo>}}

# 수식 표기법의 종류

## 중위 표기법(Infix, Polish Notation)

{{<admo title="중위 표기법">}}

$$
\verb|(A + B) * C - D / E|
$$

이항연산의 두 피연산자 *사이*에 연산자를 배치하는 방식으로, 우리가 가장 많이 사용하며 정상적이라고 느끼는 수식 표기법이다.

{{</admo>}}

* 컴퓨터에게는 전위 표기법이나 후위 표기법보다 파싱하기 어렵지만, 인간이 읽기 가장 편하다는 이유로 프로그래밍 언어에서 많이 채택한다.
* 전위 표기법이나 후위 표기법과 다르게 연산이 수행되는 *의도된* 순서를 나타내기 위해서는 **괄호가 반드시 필요**하다. 만일 괄호를 사용하지 않으면, 연산자 사이의 우선순위 규칙이 연산의 순서를 결정하게 된다.

## 전위 표기법(Prefix)

{{<admo title="전위 표기법">}}

$$
\verb|(A + B) * C - D / E| \\\ = \verb|- * +ABC/DE|
$$

연산자를 두 피연산자 *앞*에 배치하는 방식이다.

{{</admo>}}

* 괄호가 없어도 연산 순서를 명확히 알 수 있다는 장점이 있다. 
* 리스프 계열 언어(Lisp, Clojure)등에서 함수형 프로그래밍을 위해 널리 사용된다.
  * Clojure 언어에서 전위 표기식을 사용하는 예
    ```clojure{lineNos=false}
    (def score (+ 75 10)) ; 변수 선언 및 연산
    (def grade            ; 조건문으로 등급 계산
      (cond
       (>= score 90) "A"
       (>= score 80) "B"
       (>= score 70) "C"
       :else         "F"))
    
    (println "Score: " score)
    (println "Grade: " grade)
    ```

## 후위 표기법(Postfix, Reverse Polish Notation)

{{<admo title="후위 표기법">}}

$$
\verb|(A + B) * C - D / E| \\\ = \verb|AB+C*DE/-|
$$

연산자를 두 피연산자 *뒤*에 배치하는 방법이다.

{{</admo>}}

* 스택 기반 계산기에 최적화된 표기법으로, 역시 우선순위나 괄호 없이도 연산 순서를 명확하게 알 수 있다.
* 수식을 직접 계산하는 알고리즘을 구현할 때 매우 유리하다.

스택 기반 머신에서 연산을 구현할때 논리의 흐름이 후위 표기식과 유사하다. JVM(Java Virtual Machine)은 연산에 스택 머신을 활용하는 대표적인 아키텍처이다. 다음의 Java 코드를 가정하자:

```java{lineNos=false}
public class Example
{
  public static void main(String[] args)
  {
    int x = (2 + 3) * 4;
  }
}
```

`javap -c Example`로 바이트코드를 확인하면 아래와 같다.

```text{lineNos=false}
0: iconst_2 ; push 2
1: iconst_3 ; push 3
2: iadd     ; add
3: iconst_4 ; push 4
4: imul     ; mul
5: istore_1 ; store to x
```

피연산자는 스택에 계속 푸시하고, 이항 연산자를 만나면 그만큼 스택에서 팝 한후 연산한다. 
그리고 그 연산의 결과를 다시 스택에 넣는다.

Java 코드였던 `(2 + 3) * 4`는 스택 머신에서 `(2 3 add) 4 mul`라는 후위 표기식으로 변경되었다.

{{<admo title="스택 머신?">}}

* 스택 머신의 연산은 대부분의 명령이 *"피연산자 2개를 스택에 넣고, 연산이 필요하면 스택의 최상단 2개를 빼서 연산후 다시 넣는다"* 로 진행된다.
* 레지스터 기반 연산과 달리 CPU 레지스터에 대한 참조가 필요하지 않다. CPU 레지스터는 하드웨어 의존적이고, 스택 머신의 경우 레지스터를 사용하지 않으므로 하드웨어 독립적인 시스템을 구성할 때(인터프리터, VM) 많이 사용한다.

{{</admo>}}

# 수식 표기법 전환

덧셈, 뺄셈, 곱셈, 나눗셈의 네 가지 이항 연산에 대해서 수식 표기법 전환을 생각해본다.  
이항 연산자의 우선 순위는 곱셉과 나눗셈이 같고, 덧셈과 뺄셈이 같다. 
그리고 곱셈과 나눗셈이 덧셈과 뺄셈보다 우선 순위가 높다.

## 중위 표기법 → 후위 표기법

### 언제 필요한가?

컴퓨터는 후위 표기법을 가장 선호하는데, 스택 기반으로 처리하기가 쉽기 때문이다. 하지만 사람은 중위 표기가 제일 익숙하기 때문에, 사람이 작성한 중위 표기법을 컴퓨터가 이해할 수 있도록 후위 표기법으로 바꾸는 알고리즘은 자주 사용된다.

컴파일러, 계산기, 수식 해석기 등에서 중위 표기법을 후위 표기법으로 변환하는 로직은 필수적으로 구현된다.

### 차량 기지(Shunting Yard) 알고리즘

중위 표기법 후위 표기법으로 전환하는 여러 방법 중에서 스택이 가장 간편하고, [^1] 다익스트라가 만든 **차량 기지(Shunting Yard) 알고리즘**이 유명하다.

[^1]: 이진 트리를 이용하는 방법도 있으나 구현이 복잡하다.

차량기지 알고리즘은, 스택을 이용하여 연산자를 저장하는데, 이것이 마치 차량기지에 차를 주차하는 것과 비슷하다고 하여 차량기지 알고리즘이라는 이름이 붙었다.

알고리즘을 기술하면 다음과 같다.

{{<admo title="차량 기지(Shaunting Yard) 알고리즘">}}

1. 중위 표기식의 토큰 `ch`를 하나 하나 읽는다.
  * `ch`가 *피연산자*라면, 출력한다.
  * `ch`가 *연산자*라면:
    * 현재 스택의 탑에 무언가 존재하고, 그게 `(`가 아닌 연산자일 때, ==그 연산자의 우선순위가 `ch`의 우선순위 **이상**인 경우, 계속해서== 스택의 탑을 출력하고 팝 한 뒤, `ch`를 푸시한다.
  * `ch`가 *여는 괄호(`(`)* 라면, 스택에 푸시한다.
  * `ch`가 *닫는 괄호(`)`)* 라면:
    * 스택에서 `(`를 만날 때 까지 모든 탑을 출력하고 팝 한다. 
    * `(`와 `)`는 출력하지 않고, 스택에서 비운다.
2. 만일 중위 표기식의 토큰을 모두 순회했다면, 스택을 검사하여 빌 때까지 탑을 출력하고 팝 한다.

{{</admo>}}

글로 읽으면 왜 차량 기지인지 잘 감이 안오는데, 그림으로 보면 쉽게 이해할 수 있다.

예를 들어 `A * (B + C)` 라는 중위 표현식을 차량기지 알고리즘을 통해 후위 표현식으로 나타내는 과정은 아래와 같다.

![](./assets/SY/00.png "0) 시작 단계")
![](./assets/SY/01.png "1) A는 피연산자이므로 바로 출력")
![](./assets/SY/02.png "2) *는 연산자 이므로 스택에 저장")
![](./assets/SY/03.png "3) (는 여는 괄호로, 스택에 저장")
![](./assets/SY/04.png "4) B는 피연산자이므로 바로 출력")
![](./assets/SY/05.png "5) +는 연산자 이므로 스택에 저장")
![](./assets/SY/06.png "6) C는 피연산자이므로 바로 출력")
![](./assets/SY/07.png "7) )를 만났으므로, 스택에서 (가 나올때까지 모두 출력")
![](./assets/SY/08.png "7) 더이상 탐색할 문자열이 없으면, 스택을 비움")


C++ 코드로 표현하면 아래와 같다. 피연산자는 `'A'` 부터 `'Z'`까지의 문자라고 가정한다.

```cpp
// 전환할 중위 표현식
string infix; cin >> infix;

// 연산자인지 여부를 반환
auto is_operator = [](char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
};

// 이항 연산자의 우선순위를 반환
auto precedence = [](char ch) {
  switch (ch) {
    case '+': case '-': return 0; 
    case '*': case '/': return 1;
  }
};

// 연산자를 저장할 스택
stack<char> op_stack;

// 중위 표기식 문자열의 문자 ch를 하나 하나 읽는다:
for (char ch: infix) {
  // 피연산자라면, 
  if (isalpha(ch)) {
    cout << ch;
  
  // 연산자라면
  } else if (is_operator(ch)) {

    // 탑에 연산자가 존재하고, 우선순위가 ch 이상인 경우 계속해서 탑을 출력하고 팝한다.
    while (!op_stack.empty() && op_stack.top() != '(' && precedence(op_stack.top()) >= precedence(ch)) {
      cout << op_stack.top();
      op_stack.pop();
    }
    // 현재 연산자를 푸시한다.
    op_stack.push(ch);
  
  // 여는 괄호라면
  } else if (ch == '(') {
    op_stack.push(ch);

  // 닫는 괄호라면
  } else if (ch == ')') {
    // 여는 괄호 나올때 까지 연산자를 모두 출력
    while (op_stack.top() != '(') {
      cout << op_stack.top();
      op_stack.pop();
    }
    // 여는 괄호는 삭제해 줌
    op_stack.pop();
  }
}

// 스택에 남은 연산자가 있다면 출력
while (!op_stack.empty()) {
  cout << op_stack.top();
  op_stack.pop();
}
```

위 알고리즘을 이용하여 [\[백준\] 1918 G2 후위 표기식](https://www.acmicpc.net/problem/1918) 문제를 날먹할 수 있다.

## 후위 표기법 → 중위 표기법

{{<admo title="후위 표기법을 중위 표기법으로">}}
1. 후위 표기식의 토큰 `ch`를 하나 하나 읽는다.
  * `ch`가 피연산자라면, 스택에 넣는다.
  * `ch`가 연산자라면, 스택에서 우 피연산자와 좌 피연산자 두개를 꺼내 연산자와 결합한 후, 다시 스택에 넣는다.
2. 만일 후위 표기법으로 주어진 문자열을 모두 순회했다면, 스택을 검사하여 빌 때까지 탑을 출력하고 팝 한다.
{{</admo>}}

<br>  

```cpp
string postfix; cin >> postfix;
auto precedence = [](char ch) {
  switch (ch) {
    case '+': case '-': return 0; 
    case '*': case '/': return 1;
  }
};

auto is_operator = [](char ch) {
  return ch == '+' || ch == '-' || ch == '*' || ch == '/';
};

stack<string> op_stack;

for (char ch: postfix) {
  // 피연산자 일 때
  if (isalpha(ch)) {
    op_stack.push(string{ch});

  // 연산자일 때
  } else if (is_operator(ch)) {
    string r_op = op_stack.top(); op_stack.pop();
    string l_op = op_stack.top(); op_stack.pop();

    // 연산자로 결합
    string exp = "(" + l_op + ch + r_op + ")";
    op_stack.push(exp);
  }
}

while (!op_stack.empty()) {
  cout << op_stack.top();
  op_stack.pop();
}
```

[\[백준\] 1935 S3 후위 표기식2](https://www.acmicpc.net/problem/1935) 문제에서 위 알고리즘을 응용해 후위 표기식의 값을 직접 계산해 볼 수 있다.

### 언제 필요한가?

보통 디버깅 / 리버싱을 통해 내부적으로 (JVM처럼) 후위 구조로 된 수식을 인간이 읽기 편한 중위 수식으로 변경할 때 사용한다.

## 중위 표기법 → 전위 표기법

차량기지 알고리즘을 재활용한다. 중위 표기법 문자열을 거꾸로 뒤집어서, 차량기지 알고리즘을 적용하여 후위 표기법으로 만든다. 

그리고, 그 후위 표기식을 다시 뒤집으면 전위 표기식이 나온다.

# 참고 문헌

* [수식 표기법/나무위키](https://namu.wiki/w/%EC%88%98%EC%8B%9D%ED%91%9C%EA%B8%B0%EB%B2%95)
* [Infix notation/Wikipedia](https://en.wikipedia.org/wiki/Infix_notation)
* [차량기지 알고리즘/위키피디아](https://ko.wikipedia.org/wiki/%EC%B0%A8%EB%9F%89%EA%B8%B0%EC%A7%80_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)
* [\[백준\] 1918 G2 후위 표기식](https://www.acmicpc.net/problem/1918)
* [\[백준\] 1935 S3 후위 표기식2](https://www.acmicpc.net/problem/1935)