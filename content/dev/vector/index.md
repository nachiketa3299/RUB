---
title: "[수학] 게임 개발자가 알아야 할 벡터"
date: 2025-05-12
toc: true
---

본인은 정규 교육 과정에서 벡터에 대해 배웠고, 대학에서도 선형대수학 등의 과목에서 벡터를 수도 없이 다루었지만 마치 치매에 걸린 것 마냥 자꾸 까먹어서, 이를 악물고 마지막으로 정리해 본다.

벡터를 모르면 진짜 게임 개발에서 아무것도 할 수 없기 때문에, 이번 기회에 반드시 확실히 짚고 넘어가보자!

각 단계에서 벡터를 C++로 실제로 구현해 보면서 이해를 도울 것이다.

# 벡터의 정의

{{<admo title="벡터의 정의">}}

벡터(Vector)는 수학이나 물리학에서 사용되는 용어로, 

1. 하나의 숫자(스칼라)로 표현될 수 없는 양을 나타내고 싶을 때
2. 유한한 크기의 숫자 혹은 객체의 수열을 나타내고 싶을 때

사용한다.

{{</admo>}}

첫 번째 벡터의 정의는, 물리학이나 기하학에서 위치, 힘, 속도와 같이 크기와 방향을 동시에 가지는 바람에 시간이나 질량 처럼 하나의 숫자(스칼라)로 표현할 수 없는 물리량들을 표현하기 위해서 도입되었다. 이러한 관점에서 벡터는 **크기(Magnitude)**와 **방향(Direction)**이 강조되어 표현된다.

이러한 벡터를 보통 **기하 벡터(Geomtric Vector)**, 또는 **유클리드 벡터(Euclidean Vector)** 라고 부른다.

두 번째 정의는 더 보편적인 맥락에서의 벡터의 정의이며, 벡터가 그냥 **숫자(혹은 객체)의 나열**이라는 관점이다.

이러한 벡터는 **튜플(Tuple)**이라고 부를 때도 있다.

기하 벡터이건 튜플이건 이러한 벡터들이 나름의 연산과 공리를 가지고 이루게 되는 공간을 **벡터 공간(Vector Space)**이라고 부르며, 기하 벡터가 이루는 공간을 **유클리드 벡터 공간(Euclidean Vector Space)**, 튜플 벡터가 이루는 공간을 **좌표 벡터 공간(Coordinate Vector Space)** 이라고 부른다.

게임 개발에서 벡터는 보통 유클리드 벡터 공간에 속해 있는, 기하적 의미를 같는 기하 벡터이다.

```cpp{lineNos=false}
struct Vec3 {
  Vec3(float x, float y, float z): x(x), y(y), z(z) {}
  float x, y, z;
};
```

만일 3차원 공간에서 어떤 점의 위치나 방향을를 표현하기 위해 `Vec3{.1f, .0f, .3f}`같은 벡터를 만들면, 기하 벡터를 사용하려고 만든 것이다.

좌표 벡터 공간처럼 단순히 숫자의 나열인 벡터를 사용하려면 `std::tuple`을 쓰는 것이 낫다.

# 위치 벡터와 방향 벡터

위치 벡터는 벡터가 어떤 공간의 점을 나타낸다고 생각한다. 위치 벡터의 크기는 임의의 원점 $O$로부터의 거리라고 보고, 방향은 역시 임의의 원점 $O$에 대한 방향이라고 본다.

$$
\mathbf{r} = \vec{OP}
$$

보통 위와 같이 표현하며, 이는 점 $O$를 점 $P$에 매핑하는 위치 이동(Displacement, Translation)이라고도 볼 수 있다.

방향 벡터는 벡터가 어떤 공간에서 방향을 나타낸다고 생각한다. 위치이동을 적절히 수행하여 포갤 수 있는 두 방향 벡터는 같다고 생각한다. 

# 벡터의 연산

## 기본 연산

```cpp{lineNos=false}
Vec3 operator+(const Vec3& oth) const;
Vec3 operator-(const Vec3& oth) const;

Vec3& operator+=(const Vec3& oth);
Vec3& operator-=(const Vec3& oth);
```

```cpp{lineNos=false}
friend Vec3 operator*(float c, const Vec3& oth);
friend Vec3 operator*(const Vec3& oth, float c);

friend Vec3 operator/(const Vec3& oth, float c);

Vec3& operator*=(float c);
Vec3& operator/=(float c);
```

## 비교 

```cpp{lineNos=false}
bool operator==(const Vec3& oth);
bool operator!=(const Vec3& oth);
```

## 길이와 제곱 길이

```cpp{lineNos=false}
float Vec3::Length() const {
  return std::sqrt(x * x + y * y + z * z);
}
```

보통 `sqrt`가 비싼 연산이기 때문에, 길이의 정확한 값이 아니라 길이만 필요한 경우, 아래의 `LengthSquared`를 이용한다.

```cpp{lineNos=false}
float Vec3::LengthSquared() const {
  return x * x + y * y + z * z;
}
```

## 정규화

다음과 같이 두 방식으로 구현한다.

```cpp{lineNos=false}
Vec3 Vec3::Normalized() const {
  float length = Length();
  assert(length != .0f);
  return this / length;
}
```

```cpp{lineNos=false}
void Vec3::Normlize() {
  float length = Length();
  assert(length != .0f);
  this /= length;
}
```

## 내적(Dot Product)

두 벡터의 내적(Dot Product)는 다음과 같이 정의된다.

$$
\mathbf{a} \cdot \mathbf{b} = \left\|\mathbf{a}\right\|\left\|\mathbf{b}\right\|\cos{\theta}
$$

이 때, $\theta$는 두 벡터가 이루는 각도이다.

기하학적으로 이해하면, 시점을 공유하는 두 벡터 $\mathbf{a}$의 길이와, $\mathbf{b}$의 성분 중 $\mathbf{a}$와 방향이 같은 것의 길이를 곱한 값과 같다.

벡터의 내적의 결과는 스칼라임을 유의한다.

벡터의 내적은 다음처럼 각 벡터의 성분의 곱의 합으로 나타낼 수도 있다.

$$
\mathbf{a}\cdot\mathbf{b} = a_1b_1 + a_2b_2 + a_3b_3
$$

내적의 결과값을 이용해 두 벡터가 이루는 각($\theta$)을 구할 수도 있다.

다음과 같이 구현한다.

```cpp{lineNos=false}
float Vec3::Dot(const Vec3& oth) const {
  return x * oth.x + y * oth.y + z * oth.z;
}
```

### 내적의 의미

## 외적(Cross Product)

다음과 같이 구현한다.

```cpp{lineNos=false}
Vec3 Vec3::Cross(const Vec3& oth) const {
  return Vec3{
    y * oth.z - z * oth.y,
    z * oth.x - x * oth.z,
    x * oth.y - y * oth.x
  };
}
```

이차원 벡터의 경우 다음처럼 구현된다.

```cpp{lineNos=false}
float Vec2::Dot(const Vec2& oth) {
  return x * oth.y - y * oth.x;
}
```

스칼라를 반환함에 주의한다.

### 외적의 의미

# 참고 문헌

* [Position(geometry)/Wikipedia](https://en.wikipedia.org/wiki/Position_(geometry))
* [Direction(geometry)/Wikipedia](https://en.wikipedia.org/wiki/Direction_(geometry))


