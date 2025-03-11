---
title: "[C++] 가상 메서드와 가상 소멸자"
date: 2025-03-11
toc: true
---

# 가상 메서드

끔찍한 예제들을 통해 C++와 객체 지향의 이상한 기믹의 세계를 정리해 보자.

## 이름 하이딩

```cpp{lineNos=false}
class Super {
public:
  void foo() {};
};

class Derived: public Super {
public:
  void foo() {};
};
```

위는 오버라이딩이 아니라 이름 하이딩(Name Hiding)이다.  
사용하면 아래처럼 된다.

```cpp{lineNos=false}
Super s{}; s.foo();   // Super::foo()
Derived d{}; d.foo(); // Derived::foo()
```

다형성은 당연히 지원하지 않는다.

```cpp{lineNos=false}
Super *p = new Derived{};
p->foo();  // Super::foo()
```

그늘에 가려져 빛을 볼 수 없는 함수들을 직접 호명하려면 다음처럼 하자.

```cpp{lineNos=false}
Derived d;
d.Super::foo();   // Super::foo()
d.Derived::foo(); // Derived::foo()
```

`using` 선언을 해도 별 의미는 없다.

```cpp{lineNos=false}
class Derived: public Super {
public:
  using Super::foo;
  void foo() {}
}
```

여전히 `Derived::foo`가 `Super::foo`를 가리고 있다.

```cpp{lineNos=false}
Derived d; 
d.foo(); // Derived::foo();
```

스스로 고통에 몰아넣고 싶지 않다면 이런 식으로 코드를 작성할 이유가 전혀 없다.

## 이름 하이딩...?

```cpp
class Super {
public:
  void foo(int) {};
};

class Derived: public Super {
public:
  void foo(short) {};
}
```

우선, 이건 함수 오버로딩이 아니다.  함수 오버로딩은 **같은 범위**(클래스 혹은 이름공간)내에서만 유효한 개념이다.

`Derived`의 인스턴스로 `foo`를 호출하면 인자가 암시적으로 `short`로 형변환되면서 `Derived::foo(short)`가 실행된다.

이 또한 *이름 하이딩*이다.

```cpp{lineNos=false}
Derived d;
d.foo(10);        // Derived::foo(short);
d.Super::foo(10); // Super::foo(int);

Super& sr = &d;
sr.foo(10);       // Super::foo(int);
```

역시 정신건강을 온전히 보전하고 싶다면 이런 짓은 의도하지 않는 것이 좋다.

## 메서드 오버라이딩

```cpp{lineNos=false}
class Super {
public:
  virtual void foo() {};
};

class Derived: public Super {
public:
  void foo() override {};
};
```

위는 메서드 `foo`를 유도 클래스에서 **오버라이드**한 예이다.

메서드 오버라이드는 부모 클래스의 메서드를 자식 클래스에서 **재정의** 하는 것이다.  

==C++에서 오버라이딩은 부모 메서드가 반드시 `virtual` 해야 하며, 함수 시그니처가 완전히 동일해야 한다.==

가상함수를 오버라이드하면 다음과 같이 다형성을 구현할 수 있다.

 ```cpp{lineNos=false}
 Super* p = new Derived{};
 Super& r = *p;

 p->foo(); // Derived::foo()
 r.foo();  // Derived::foo()
 ```

**가상함수 테이블**이라는 것이 이 동작을 가능하게 한다.

가상 함수가 있는 객체가 메모리에 적재될 때, 가상 함수 테이블도 함께 [^1] 적재된다. 가상 함수 테이블에는 가상 함수 호출 요청시 구체적으로 어떤 객체의 오버라이드된 메서드를 호출해야 하는지 적혀 있다.

 [^1]: 정확히는 테이블을 가리키는 포인터

부모 함수의 포인터로 가상 함수 호출 명령을 내리면, 해당 객체가 상속 구조도에서 정확히 어디쯤에 있는 무엇인지 모르더라도, 가상 함수 테이블을 뒤져서 실제로 호출할 함수가 무엇인지 찾아내고, 호출한다.

그러나, 가상 함수 호출은 가상 함수 테이블을 찾는 과정이 포함되므로 일반 함수를 호출하는 것 보다는 느리다.

### 공변 반환형

오버라이딩하는 경우, 메서드의 시그니처가 완전히 동일해야 한다는 전제조건이 있으나 한 가지 예외가 있다.  

오버라이드한 메서드의 반환 타입은 상위 클래스의 메서드가 반환하는 타입의 하위 타입(IS-A)이 될 수 있다.  

결과적으로 오버라이딩시 *"약간 다른 반환값"* 을 허용하는 것이라고 볼 수 있다.

보통 다음처럼 자기 자신의 참조를 반환하는 메서드를 만들 때 쓴다.

```cpp{lineNos=false}
class S {
  virtual S* foo() { return this; }
};

class D {
  D* foo() override { return this; }
};
```

위 예시에서 `D` 는 `S`이므로 (IS-A) 공변 반환형이며, 따라서 오버라이딩이 허용된다.

### 코드 스타일 팁

[C++ 코어 가이드라인 C.128](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html#c128-virtual-functions-should-specify-exactly-one-of-virtual-override-or-final)에서는 다음을 권장한다:

* 가상성이 시작되는 메서드에는 `virtual`만 붙인다.
* 하위 클래스에서 오버라이딩 할 때에는 `virtual`을 생략하고 `override`/`final`중 하나만 붙인다.


```cpp{lineNos=false}
class S {
public:
  virtual void foo() {}
};

class D: public S {
public:
  void foo() {} // 오버라이딩이다.
}
```

가상성이 시작되는 메서드에 `virtual`만 붙이면, 오버라이딩 할 때에는 쭉 모든 관련 키워드를 생략할 수 있다.

하지만 아무 것도 안 적는 것은 매우 비추천한다. 클래스는 보통 다른 파일에 저장되어 있기 때문에 오버라이딩시 실수할 확률이 꽤 높다.

명시적으로 `override` 키워드를 사용하면 작성자의 의도를 동료와 컴파일러 모두에게 명시할 수 있다. 

```cpp{lineNos=false}
class S {
public:
  virtual void foo() const {}
};

class D: public S {
public:
  // 오버라이딩을 의도했으나
  // 키워드 생략하는 바람에 
  // 함수 시그니처가 달라서 "이름 하이딩"이 된 것을
  // 컴파일 타임에 잡지 못함
  void foo() {}
}
```

내가 `foo`를 오버라이딩 하는데, 함수 시그니처를 잘못 작성할 수 있다. <sup>그리고 이런 일은 꽤 흔하다.</sup> `override` 키워드를 사용하면 컴파일러가 이 실수를 잡아낼 수 있다. 사용하지 않으면, 이름 하이딩이 되어버린다.

## 메서드 오버오버오버라이딩

다음과 같은 상속 구조가 있다고 하자.

```cpp{lineNos=false}
class A {
public:
  virtual void foo() {}  // foo 는 A::foo()
}

class B {
public:
  void foo() override {} // foo 는 B::foo()
};

class C: public A {}     // foo 는 B::foo()
class D: public B {}     // foo 는 B::foo()

class E: public C {      // foo 는 E::foo()
public:
  void foo() final {}
}
```

다음을 보자.

```cpp{lineNos=false}
A* p = new D{};
p->foo();
```

`p->foo()`에서 무슨 `foo`가 호출될까?  
`A::foo()`가 호출된다.

가상함수 테이블의 내용은 상속시 복사되어 전달된다.  
만일 가상함수 테이블의 가상 메서드를 해당 클래스에서 오버라이딩 했다면, 가상함수 테이블은 업데이트된다.  
하지만 해당 클래스에서 오버라이딩 하지 않았다면, 가상함수 테이블은 직계 부모에서 상속받은 내용 그대로일 것이다.

때문에 해당 객체가 호출한 가상 메서드를 오버라이딩 하지 않은 경우 가장 가까운, 오버라이딩한 부모의 메서드가 호출된다.

# 가상 소멸자

여기까지 사실 가상 소멸자를 위한 빌드업이었다.

소멸자가 가상일 이유는 무엇일까?  
다음을 보자:

```cpp{lineNos=false}
class Super {
public:
  ~Super() = default;
private:
  int s_;
};

class Derived: public Super {
public:
  ~Derived() { delete[] d_; }
private:
  int *d_{new int[10'000]};
};
```

위와 같은 클래스들을 아래 처럼 사용한다고 가정한다.

```cpp{lineNos=false}
Super* p = new Derived{};
delete p;
```

여기서 아주 큰 문제가 발생하는데, 위에서 뚱뚱하게 설명한 것처럼 가상성이 없으면 부모에 대한 참조를 통해 자식의 실제 메서드에 접근할 수가 없다.

`delete`는 소멸자를 호출하는데, `p`는 `Super*` 형이므로 `~Super`가 호출된다.

하지만 `p`가 가리키는 객체는 실제로는 `Derived`객체고, 이 객체는 힙 메모리에 `10'000`길이의 `int`형 메모리를 차지하고 있으며, 본인의 소멸자에서 그것을 정리하고 있다.

허나 실제로 호출되는 소멸자는 `~Super`이므로, `Derived` 객체 내의 동적 메모리가 정리되지 않은 채로 남아있게 되며, 이는 당연히 메모리 누수의 원인이 된다.

다음처럼 다시 설계하자.

```cpp{lineNos=false}
class Super {
public:
  virtual ~Super() = default;
private:
  int s_;
};

class Derived: public Super {
public:
  ~Derived() override { delete[] d_; }
private:
  int *d_{new int[10'000]};
};
```

이러면 이제 가상 함수 테이블이 생성되므로, 부모의 포인터로 소멸자를 호출하여도, 그 포인터가 가리키는 실제 대상이 보유한 소멸자를 직접 호출할 수 있게 된다.