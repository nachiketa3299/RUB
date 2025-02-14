# Unreal Labs 가이드 라인

> 주석은 *선언으로 이동* 기능을 사용하거나 *정의 피킹* 기능을 두 번 사용하여 선언부를 찾아 작성합니다.
> 내부 주석이 아닌, 선언과 정의에 존재하는 모든 기존 주석은 삭제합니다.
> 사용할 태그는 아래와 같으며, 불필요 태그는 생략 가능하지만 아래의 태그 순서는 유지하여야 합니다.

@short  
@deprecated  
@tparam  
@param  
@return  
@qualifier  
@details  
@note  
@warning  
@bug  
@see  
@relatesalso  
@author  

---

> Unreal Labs에서 사용되는 Doxygen 주석 태그는 아래와 같습니다.

- ### `@ref 대상`
  - `대상`의 문서를 링크합니다.
  - 지칭은 `범위::이름(인자 형식 목록) const` 형태를 준수합니다.
  - 지칭을 위한 '정의로 이동' 메뉴 또는 '정의 피킹' 메뉴의 사용을 권장합니다.
  - 인자 목록의 인자 이름은 제거합니다. 
      - 따라서 매크로는 이름만으로 지칭이 가능합니다.
  - `UPARAM` 등의 리플렉션 매크로는 제거합니다.
  - 인자의 기본 인수는 제거합니다.
  - 분석 대상이 포함한 단어는 자동 링크 대상이므로 링크가 불필요합니다.
  - `deprecated` 태그와 `see` 태그에만 사용합니다.
- ### `@todo 작성자 작업`
  - `작성자`가 수행할 `작업`에 대한 기록을 남깁니다.
- ### `@todo relatesalso`
  - `relatesalso` 태그의 후보 대상에 사용합니다.
- `@short 설명`
  - 단순히 함수의 수행 결과만을 기재하는 등, 대상을 최대한 간략하게 설명합니다.
- ### `@deprecated @ref 대상` (또는 `@ref 대상`) 사용을 권장합니다.
  - `deprecated` 사용을 권장하지 않습니다.
    - `UE_DEPRECATED(_MACRO)` 매크로 지정 대상 및 기존 주석의 Deprecated 대상에 대해서만 사용합니다.
- ### `@tparam 인자명 설명`
  - 템플릿의 형식 인자를 설명합니다.
  - 각각의 형식 인자에 대해 다중 사용합니다.
  - 인자의 이름을 틀리지 않도록 주의합니다.
- ### `@param[용도] 인자명 설명`
  - 함수 또는 함수형 매크로의 인자를 설명합니다.
  - 각각의 인자에 대해 다중 사용합니다.
  - 인자의 용도와 이름을 틀리지 않도록 주의합니다.
  - 인자의 용도는 아래와 같습니다.
  - `[in]` -  값을 전달하기 위한 용도
  - `[out]` - 값을 반환하기 위한 용도
  - `[in, out]` - 값을 주고받기 위한 용도
- ### `@return 설명`
  - 함수의 반환을 설명합니다.
  - `void`가 아닌, 명시적인 반환이 존재할 경우에만 사용합니다.
- ### `@qualifier pure`
  - 명시적으로 `PURE_VIRTUAL`이 지정된 가상 함수에 대해서만 사용합니다.
- ### `@details 설명`
  - `short` 태그의 내용과 중복되지 않도록 하며, 대상의 정보에 대해서만 서술합니다.
  - 개행 문자(`\n`)는 각각의 경우에 대한 설명 또는 문장 단위로만 사용합니다.
- ### `@note 주의사항`
  - 엔진에 중단을 일으키지는 않지만, 주의가 필요한 사항에만 사용합니다.
  - 각각의 주의 사항에 대해 다중 사용합니다.
- ### `@warning 경고 사항`
  - 엔진에 중단을 일으키는 사항이나, 기존 주석의 경고 사항에 대해서만 사용합니다.
  - 각각의 경고 사항에 대해 다중 사용합니다.
- ### `@bug 버그`
  - 대상에 존재하는 버그를 설명합니다.
  - 각각의 버그에 대해 다중 사용합니다.
- ### `@see @ref 대상`
  - 참고할 대상을 소개합니다.
  - 각각의 참고 대상에 대해 다중 사용합니다.
- ### `@author 작성자명`
  - 주석 작성자의 이름을 기재합니다.

 ---

> 한 줄 주석은 다음 두 가지 경우에만 가능하며, `short`, `deprecated`, `note`, `warning`, `bug`, `see`, `ref` 태그만 허용합니다.
> - (1) 매크로 정의 함수
> - (2) 열거자
>   
> (참고) 매크로 정의 함수에 주석을 작성하는 경우, 경우 주석 이후 `\`가 필요합니다.

```cpp
#define ENUM_CLASS_FLAGS(Enum) \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline           Enum& operator|=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs); } \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline           Enum& operator&=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs); } \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline           Enum& operator^=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs); } \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline constexpr Enum  operator| (Enum  Lhs, Enum Rhs) { return (Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs); } \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline constexpr Enum  operator& (Enum  Lhs, Enum Rhs) { return (Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs); } \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline constexpr Enum  operator^ (Enum  Lhs, Enum Rhs) { return (Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs); } \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline constexpr bool  operator! (Enum  E)             { return !(__underlying_type(Enum))E; } \
	/*! @short ENUM_CLASS_FLAGS 매크로가 정의합니다. @see @ref ENUM_CLASS_FLAGS */ \
	inline constexpr Enum  operator~ (Enum  E)             { return (Enum)~(__underlying_type(Enum))E; }
```

```cpp
#define UE_NONCOPYABLE(TypeName) \
	/*! @short UE_NONCOPYABLE 매크로가 삭제합니다. @see @ref UE_NONCOPYABLE */ \
	TypeName(TypeName&&) = delete; \
	/*! @short UE_NONCOPYABLE 매크로가 삭제합니다. @see @ref UE_NONCOPYABLE */ \
	TypeName(const TypeName&) = delete; \
	/*! @short UE_NONCOPYABLE 매크로가 삭제합니다. @see @ref UE_NONCOPYABLE */ \
	TypeName& operator=(const TypeName&) = delete; \
	/*! @short UE_NONCOPYABLE 매크로가 삭제합니다. @see @ref UE_NONCOPYABLE */ \
	TypeName& operator=(TypeName&&) = delete;
```

```cpp
UENUM()
enum ExampleEnum
{
	/*! @short 폐기되었습니다. @deprecated 사용을 권장하지 않습니다. */
	Enum0 UE_DEPRECATED(4.27, "Enum0 is no longer used."),
	/*! @short 열거자 주석 예제입니다. */
	Enum1 UMETA(DisplayName = "Enum"),
};

ENUM_CLASS_FLAGS(ExampleEnum);
```

---

> 네임 스페이스 및 형식 재정의는 분석 대상이 아닙니다.

```cpp
namespace Example
{
	typedef int int32;

	using int64 = __int64;
}

using namespace Example;
```

---

> 주석은 `UCLASS`, `USTRUCT`, `UENUM` 등 리플렉션 매크로 아래, 대상의 바로 위에 작성합니다.
> 폐기된 대상에 대해서는 `short`, `deprecated`, `author` 태그만을 사용합니다.
> 폐기된 형식의 멤버는 분석 대상이 아닙니다.

```cpp
struct UE_DEPRECATED(4.27, "Please use ExampleClass instead.") ExampleStruct;
```

```cpp
USTRUCT()
/*!
	@short 폐기되었습니다.
	@deprecated @ref ExampleClass 또는 @ref ExampleEnum 사용을 권장합니다.
	@author 박종현
*/
struct ExampleStruct
{
	GENERATED_BODY()

	UE_NONCOPYABLE(ExampleStruct)

	int32 Data;
};
```

```cpp
UCLASS()
/*!
	@short 예제 클래스입니다.
	@note 반드시 대상 바로 위에 주석을 작성합니다.
	@author 박종현
*/
class ExampleClass
{
	GENERATED_BODY()

public:
	using DataType = int64;

	UFUNCTION()
	/*!
		@short 데이터와 비교 대상의 동일 여부를 반환합니다.
		@tparam T 비교 대상의 형식입니다.
		@param[in] InData 비교 대상입니다.
		@return 비교 결과입니다.
		@warning InData가 음수일 경우 엔진을 중단합니다.
		@see @ref ExampleClass::Data
		@author 박종현
	*/
	template<typename T>
	bool DoesDataEqualTo(UPARAM(DisplayName = "Data") T const InData = T()) const;

	/*!
		@short 데이터를 반환합니다.
		@return 데이터입니다.
		@author 박종현
	*/
	FORCEINLINE DataType GetData() const
	{
		return Data;
	}

private:
	UPROPERTY()
	/*!
		@short 데이터입니다.
		@author 박종현
	*/
	DataType Data;
};

template<typename T>
bool ExampleClass::DoesDataEqualTo(T const InData) const
{
	assert(0 <= InData);

	return Data == InData;
}

/*!
	@short 처음 DEFINE 매크로 정의입니다.
	@author 박종현
*/
#define DEFINE 1
#undef DEFINE

/*!
	@short 다음 DEFINE 매크로 정의입니다.
	@author 박종현
*/
#define DEFINE 2
#undef DEFINE

using EC = ExampleClass;

/*!
	@short 두 개체의, 데이터의 동일 여부를 반환합니다.
	@param[in] A 좌항 피연산자입니다.
	@param[in] B 우항 피연산자입니다.
	@return A와 B의 Data 일치 여부입니다.
	@details 내부에서 A의 DoesDataEqualTo를 호출합니다.\n
			 이후 A와 B의 Data를 비교한 결과를 반환합니다.
	@see @ref EC::Data
	@see @ref ExampleClass::DoesDataEqualTo(T const) const
	@author 박종현
*/
bool DoTwoDataEqual(ExampleClass const A, ExampleClass const B)
{
	return A.DoesDataEqualTo(B.GetData());
}
```
