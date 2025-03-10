---
title: "[유니티] 유니티 핵심 클래스"
date: 2025-03-08
toc: true
---

# 개요

유니티에서 스크립팅 할 때 가장 많이 사용되는 빌트인 클래스와 그 상속 구조에 대한 개략을 정리할 필요가 있겠다 싶어서 정리함.

우선 중요 클래스의 클래스 상속 구조도는 아래와 같다.

{{< puml >}}
@startuml
hide empty members

Object <|-- Component
Component <|-- Behaviour
Behaviour <|-- MonoBehaviour
Object <|-- GameObject

@enduml
{{< /puml >}}

# Object

`UnityEngine` 이름 공간에 존재하는 클래스로, 유니티가 에디터에서 참조할 수 있는 모든 객체의 기본 클래스 역할을 한다.

`UnityEngine.Object`에서 상속되는 클래스는 인스펙터의 필드로 드래그 앤 드롭하거나, 오브젝트 필드 옆에 있는 오브젝트 피커를 사용하여 선택하도록 해주는 특수 기능을 지원한다.

스크립트를 통해 자체 오브젝트를 생성하는 경우 Object에서 직접 상속하면 안되고, 목표에 맞는 더 잘 설계된 클래스에서 상속해야 한다. 사용자가 직접 파생시키기 위한 용도로 만들어진 클래스는 아니다. 또한, 사용자가 스크립트에서 많이 사용할 것을 전제로 작성된 클래스 또한 아니다.

예를 들어 게임 오브젝트에 추가할 수 있는 커스텀 컴포넌트를 작성하고 게임 오브젝트가 수행하는 작업을 제어하거나, 관련한 일부 기능을 제공하려면 `MonoBehaviour`에서 상속한다.

참고로 유니티의 `Object` 클래스와 .NET의 기본 `Object` 클래스와는 다른 것이므로 유의한다. 이름만 같을 뿐이다. 인스펙터에서 할당할 필요가 없는 클래스를 스크립트에 생성하려는 경우 여전히 .NET의 `System.Object` 클래스를 상속할 수 있다.

`Object`는 `?.`(null-conditional operator)와 `??`(null-coalescing operator)를 연산을 지원하지 않는다.

`Object` 클래스는 게임오브젝트, 컴포넌트, 머터리얼, 텍스쳐, 메쉬, 스프라이트 등을 비롯한 대부분의 유니티 빌트인 클래스에 대한 기본 클래스 역할을 한다. 즉, 인스펙터에서 이러한 모든 타입을 이 레퍼런스 필드에 드래그 앤 드롭 할 수 있다.

## 클래스 다이어그램

{{< puml >}}
@startuml
class Object {
  + name
  + hideFlags

  + GetInstanceID()
  + ToString()

  + {static} Instantiate()

  + {static} Destroy()
  + {static} DestroyImmediate()
  + {static} DontDestroyOnLoad()

  + {static} FindAnyObjectByType()
  + {static} FindFirstObjectByType()
  + {static} FindObjectOfType()
  + {static} FindObjectsByType()
  + {static} FindObjectsOfType()

  + bool()
  + operator!=()
  + operator==()
}
@enduml
{{< /puml >}}

# ⭐ GameObject

씬에 배치될 수 있는 모든 객체들의 기초 클래스이다. 씬의 가장 기본적인 구성 단위라고 보면 된다.

==컴포넌트(`Component`)는 게임 오브젝트의 **모양**과 **기능**을 결정하고, 게임 오브젝트는 컴포넌트의 **컨테이너** 역할을 한다.==

스크립팅시 `GameObject` 클래스는 코드에서 게임 오브젝트 찾기, 연결, 메시지 전송, 컴포넌트 추가 또는 제거, 씬 상태와 관련된 값 설정 등의 작업을 수행할 수 있는 메서드 컬렉션을 제공한다.

## 클래스 다이어그램

{{< puml >}}
@startuml
hide empty members

class GameObject {
  + transform
  ..생성..
  + GameObject()
  + {static} InstantiateGameObjects()
  ..씬 상태 - 기타..
  + CompareTag()
  + {static} GetScene()
  + tag
  + layer
  + scene
  + sceneCullingMask
  + isStatic
  ..씬 상태 - 활성화..
  + {static} SetGameObjectsActive()
  + SetActive()
  + activeHierarchy
  + activeSelf
  ..메시지 전송..
  + BroadcastMessage()
  + SendMessage()
  + SendMessageUpwards()
  ..컴포넌트 찾기/추가..
  + AddComponent()
  + TryGetComponent()
  + GetComponents()
  + GetComponentInChildren()
  + GetComponentInParent()
  ..게임 오브젝트 찾기..
  + {static} Find()
  + {static} FindObjectsWithTag()
  + {static} FindWithTag()
  ..기타..
  + {static} CreatePrimitive()
}

Object <|-- GameObject
@enduml
{{< /puml >}}

## 게임 오브젝트의 씬 내에서의 상태

에디터의 GUI를 이용하거나 스크립트를 이용하여 씬 내에서의 게임 오브젝트의 상태와 관련된 많은 프로퍼티를 수정할 수 있다.

게임 오브젝트의 씬 내에서의 상태는 다음과 같은 것들이 있다.
* 활성 상태
* 정적 상태
* 태그와 레이어

### 활성 상태

게임 오브젝트는 기본적으로 모두 활성 상태이지만, 비활성화하여 부착된 컴포넌트의 작동을 해제할 수 있다.

비활성화된 게임 오브젝트는 일반적으로 눈에 보이지 않으며, `Update`나 `FixedUpdate` 같은 정상적인 콜백이나 이벤트를 수신하지 않는다.

에디터에서는 인스펙터 상단의 체크박스로 활성 상태가 표현되며, 스크립트로는 `GameObject.SetActive`로 제어할 수 있다.

`GameObject.activeSelf`를 사용하여 게임 오브젝트가 현재 활성 상태인지의 여부를 읽을 수 있다.

`GameObject.activeInHierarchy`를 사용하여 게임 오브젝트가 실제로 씬에서 활성 상태인지 판단한다. 게임 오브젝트가 실제로 씬 내에서 활성 상태인지 아닌지의 여부는 자신의 활성 여부에 더해, 부모 오브젝트의 활성 여부까지 고려해야 하기 때문이다. 부모 오브젝트가 활성화 되어 있지 않은 경우, 게임 오브젝트가 활성화되어 있다 하더라도 실제로 활성화 되지 않는다.

### 정적 상태

전역 조명, 오클루전, 배칭, 내비게이션, 반사, 프로브와 같은 일부 Unity 시스템은 게임 오브젝트의 정적 상태에 의존한다. `GameObject.SetStaticEditorFlags`를 사용하여 게임 오브젝트를 정적으로 간주하는 유니티 시스템을 제어할 수 있다.

### 태그와 레이어

태그는 씬에서 게임 오브젝트 타입을 표시하거나 식별하는 방식을 제공한다. 레이어는 렌더링 또는 물리 충돌과 같은 특정 빌트인 동작에 게임 오브젝트 그룹을 포함하거나 제외하는 유사하면서도 차별화되는 방식을 제공한다.

`GameObject.tag`및 `GameObject.layer` 프로퍼티를 사용하여 스크립트를 통해 태그와 레이어 값을 수정할 수 있다.

또한 태그의 존재 여부에 대한 검사를 포함하며, 메모리 할당을 유발하지 않은 `CompareTag` 메서드를 사용하여 게임 오브젝트의 태그를 효과적으로 확인할 수 있다.

## 컴포넌트 추가 및 찾기(접근)

스크립트를 이용해 런타임에 컴포넌트를 추가하거나 제거할 수 있고, 이는 게임 오브젝트를 절차적으로 생성하거나 동작 방식을 수정할 수 있게 해준다. 런타임에 컴포넌트를 게임 오브젝트에 추가하는 가장 좋은 방법은 `AddComponent<Type>`이며, 컴포넌트를 제거하려면 컴포넌트에 대해 `Object.Destroy` 메서드를 사용한다.

손상을 일으키지 않고 스크립트를 통해 컴포넌트와 일부 타입의 빌트인 컴포넌트를 `enable` 또는 `disable` 상태로 만들 수 있다.

게임 오브젝트의 스크립트(컴포넌트)가 동일한 게임 오브젝트나 다른 게임 오브젝트에 연결된 컴포넌트에 접근해야 하는 경우가 많다. 이 때에는 `GetComponent<Type>` 메서드가 가장 많이 사용된다. 만일 `GetComponent<Type>`로 지정한 `Type` 컴포넌트를 게임 오브젝트에서 찾을 수 없으면, `null`을 반환하므로 주의한다.

## 계층 구조의 오브젝트 찾기

어떤 게임 오브젝트의 계층 구조에서의 자식 오브젝트는, `Transform` 컴포넌트를 사용하여 검색할 수 있다. 참고로, 모든 게임 오브젝트는 암시적으로 `Transform` 컴포넌트를 보유하고 있다.

```csharp
public WayPoints : MonoBehaviour 
{
  public Transform[] _waypoints;
  void Start()
  {
    _waypoints = new Transform[transform.childCount];
    int i = 0;
    
    foreach (Transform tr in transform) 
      waypoints[i++] = t;
  }
}
```

추가로, `Transform.Find` 메서드를 이용하면 특정 이름을 가진 자식 오브젝트를 찾을 수도 있다.

## 메시지 전송 및 브로드캐스트

게임에서 캐릭터와 가장 가까운 아이템을 찾거나, 씬이 로드된 후 인스턴스화된 게임 오브젝트를 참조하는 등, 어떤 게임 오브젝트에 대한 참조는 런타임 이전에 설정하는 것이 불가능 할 때도 있다.

이러한 경우 런타임에서 게임 오브젝트 간에 레퍼런스를 찾고 메시지를 보낼 수 있다.

`BroadcastMessage`를 사용하면 해당 메서드를 구현해야 하는 위치를 구체적으로 지정하지 않고도 명명된 메서드를 호출할 수 있다.

특정 게임 오브젝트 또는 그 자식 게임 오브젝트의 모든 `MonoBehaviour`에 대헤 명명된 메서드를 호출할 수도 있다. 원하는 경우 최소 하나의 리시버가 존재하고, 그렇지 않으면 오류가 생성되도록 지정할 수도 있다.

`SendMessage`는 좀 더 특정적이며, 게임 오브젝트 자체(자식 제외)에 대한 명명된 메서드만 호출한다.

`SendMessageUpward`는 다소 유사하지만, 게임 오브젝트와 모든 해당 부모에 대한 명명된 메서드를 호출한다.

## 이름이나 태그로 게임 오브젝트 찾기

게임 오브젝트 식별정보만 있으면 씬 계층구조의 어디에서든 게임오브젝트를 찾을 수 있다.
개별 오브젝트를 `GameObject.Find` 함수를 통해 이름으로 검색할 수 있다.
`GameObject.FindWithTag`나 `GameObject.FindGameObjectsWithTag` 메서드를 사용하여 태그로도 찾을 수 있다.

## 게임 오브젝트 생성 및 제거

`Instantiate` 메서드를 사용하면 게임 오브젝트를 생성할 수 있다. 이 때 메서드는 기존 오브젝트의 새 복사본을 만든다.

"프리팹 인스턴스화"에 대해 알아보라.

`Destroy` 메서드는 프레임 업데이트가 완료된 후 또는 선택적으로 짧은 시간 지연 후 오브젝트를 삭제한다. (`Destroy(gameObject, 0.5f)`)

`Destroy` 함수는 개별 컴포넌트도 파괴할 수 있으므로, `Destroy(this)`는 게임 오브젝트를 파괴한 것이 아니라, 이것이 호출된 컴포넌트를 파괴한 것이다.

# Component

`GameObject`에 부착될 수 있는 모든 것들의 기초 클래스이다.

코드에서 직접 `Component`를 생성하면 안 된다. 대신에, 스크립트를 만들고 그 스크립트를 `GameObject`에 붙인다.

컴포넌트에서 파생되어 `Behaviour`까지 내려가야  활성화와 비활성화라는 개념이 생긴다. 즉, 컴포넌트 상태에서는 활성화/비활성화가 존재하지 않는다.

활성화/비활성화가 존재하지 않는 컴포넌트의 예로 `Rigidbody`가 있다. `Rigidbody`는 `Behaviour` 대신에 `Component`에서 파생된다. `Collider` 또한 `Component`에서 파생된다.

[주의] `Behaviour`와 `Component`는 유니티 내부적으로 사용되기 위한 클래스이므로 여기서 사용자가 직접 클래스를 파생시키지 않는 것이 좋다.

{{< puml >}}
@startuml
hide empty members

class Component {
  + gameObject
  + tag
  + transform

  + BroadcastMessage()
  + SendMessage()
  + SendMessageUpwards()

  + CompareTag()

  + TryGetComponent()
  + GetComponent()
  + GetComponents()
  + GetComponentInParent()
  + GetComponentsInParent
  + GetComponentInChildren()
  + GetComponentsInChildren()
}

Object <|-- Component
Object <|-- GameObject

@enduml
{{< /puml >}}

# Behaviour

활성화되거나 비활성화될 수 있는 `Component`를 비헤이비어라고 한다.
이 개념이 중요한 이유는, **활성화와 비활성화라는 개념이 없는 컴포넌트도 존재**하기 때문이다.

{{< puml >}}
@startuml
hide empty members

class Behaviour {
  + enabled
  + isActiveAndEnabled
}

Object <|-- GameObject
Object <|-- Component
Component <|-- Behaviour

@enduml
{{< /puml >}}

# ⭐ MonoBehaviour

## 개요

거의 대부분의 유니티 스크립트가 모노비헤이비어에서 파생된다. 사실상 유니티 스크립트와 동치이며, 유니티 에디터에서 C# 스크립트를 생성하면 자동으로 모노비헤이비어에서 상속된 템플릿 스크립트가 생성된다.

모노비헤이비어 클래스는 유니티 엔진에서 개발의 편의를 돕는 많은 기능들을 제공한다.

모노비헤이비어는 대규모 이벤트 메시지 컬렉션에 대한 액세스를 제공하며, 이를 통해 현재 프로젝트에서 발생하는 상황에 따라 코드를 유연하게 실행할 수 있다.

모노비헤이비어는 항상 게임오브젝트의 컴포넌트로 존재하며, `GameObject.AddComponent` 메서드를 사용하여 인스턴스화 해야 한다. 게임 오브젝트의 컴포넌트로 부착되어 있지 않고 독립적으로 존재해야 하는 게임 객체들은 `ScriptableObject` 클래스에서 파생해야 한다.

모노비헤이비어는 게임오브젝트와 마찬가지로 `UnityEngine.Object`에서 파생되기 때문에, `Object.Destroy`나 `Object.DestroyImmediate`를 통해 삭제될 수 있다.

주의할 점은 `Destroy(this)`는 호출한 모노비헤이비어 컴포넌트를 삭제하라는 요청이지, 컴포넌트가 부착된 게임 오브젝트까지 삭제하라는 요청이 아니다.

* 부모 게임 오브젝트가 파괴되면, 모노비헤이비어를 포함한 모든 컴포넌트가 자동으로 삭제된다.

컴포넌트가 파괴된 후에도 모노비헤이비어에 대한 C# 오브젝트는 가비지 컬렉터가 수거하기 전까지 메모리에 잔류해 있다. 이 상태의 모노비헤이비어는 마치 `null`인 것처럼 행동해서 `obj == null`은 참을 반환한다. 하지만, `?.`나 `??`연산을 사용해서는 안된다.

모노비헤이비어가 직렬화 되었을 때 C# 필드의 값 또한 유니티의 직렬화 규칙에 의해 포함된다. 스크립트 직렬화라는 주제로 공부를 좀 해 보시오. 직렬화된 데이터는 오브젝트의 구현 클래스를 추적하는 MonoScript에 대한 참조와 같은 내부 프로퍼티를 포함하기도 한다.

유니티 에디터에 모노비헤이비어를 활성화하거나 비활성화 할 수 있는 체크박스가 있다. 스크립트에 다음의 함수가 존재하지 않으면, 유니티 에디터는 체크박스를 아예 표시하지 않는다.
* `Start`, `OnEnable`, `OnDisable`
* `Update`, `FixedUpdate`, `LateUpdate`
* `OnGUI`

또한 모노비헤이비어를 사용하면 코루틴을 관리할 수도 있다.

## 클래스 다이어그램
{{< puml >}}
@startuml
hide empty members
class MonoBehaviour {
  + destroyCancellationToken
  + didAwake
  + didStart
  + runInEditMode
  + useGUILayout

  ..코루틴 관련..
  + CancelInvoke()
  + Invoke()
  + InvokeRepeating()
  + IsInvoking()
  + StartCoroutine()
  + StopCoroutine()
  + StopAllCoroutines()
  ..기본 생명주기..
  + Awake()
  + OnEnable()
  + Start()
  + FixedUpdate()
  + Update()
  + LateUpdate()
  + OnDisable()
  + OnDestroy()
  ..애니메이션 관련..
  + OnAnimatorIK()
  + OnAnimatorMove()
  ..애플리케이션 상태 관련..
  + OnApplicationFocus()
  + OnApplicationPause()
  + OnApplicationQuit()
  ..오디오 관련..
  + OnAudioFilterRead()
  ..렌더링 관련..
  + OnPreCull()
  + OnBecameVisible()
  + OnBecameInvisible()
  + OnRenderObject()
  + OnPostRender()
  + OnRenderImage()
  + OnWillRenderObject()
  ..물리 관련..
  + OnCollisionEnter()
  + OnCollisionStay()
  + OnCollisionExit()
  + OnCollisionEnter2D()
  + OnCollisionStay2D()
  + OnCollisionExit2D()
  + OnTriggerEnter()
  + OnTriggerStay()
  + OnTriggerExit()
  + OnTriggerEnter2D()
  + OnTriggerStay2D()
  + OnTriggerExit2D()
  + OnControllerColliderHit()
  ..조인트 관련..
  + OnJointBreak()
  + OnJointBreak2D()
  ..파티클 관련..
  + OnParticleCollision()
  + OnParticleSystemStopped()
  + OnParticleTrigger()
  + OnParticleUpdateJobScheduled()
  ..트랜스폼 변화 감지..
  + OnTransformChildrenChanged()
  + OnTransformParentChanged()
  ..멀티플레이어..
  + OnPlayerConnected()
  + OnPlayerDisconnected()
  + OnNetworkInstantiate()
  + OnConnectedToServer()
  + OnDisconnectedToServer()
  + OnFailedToConnect()
  + OnFailedToConnectToMasterServer()
  + OnMasterServerEvent()
  + OnSerializeNetworkView()
  + OnSeverInitialized()
  ..기타..
  + OnValidate()
  + Reset()
  + {static} print()
  + OnDrawGizmos()
  + OnDrawGizmosSelected()
  + OnGUI()
}

Object <|-- Component
Object <|-- GameObject
Component <|-- Behaviour
Behaviour <|-- MonoBehaviour

@enduml
{{< /puml >}}

아래는 위 이미지에서 짤린 함수들..
+ OnMouseDown()
+ OnMouseDrag()
+ OnMouseEnter()
+ OnMouseExit()
+ OnMouseOver()
+ OnMouseUp()
+ OnMouseUpAsButton()

# Transform

어떤 개체의 위치, 회전, 스케일을 의미한다. 씬에 존재하는 모든 오브젝트에는 트랜스폼이 존재한다.

트랜스폼은 오브젝트의 위치, 회전, 스케일을 저장하고 조작하는 데에 사용된다.

모든 트랜스폼은 부모를 가질 수 있어서, 계층적으로 위치와 회전, 스케일을 적용할 수 있게 해준다.

또한 반복자를 통해서 자식 오브젝트들을 순회할 수 있게도 만들어준다.

## 클래스 다이어그램

{{< puml >}}
@startuml
hide empty members

class Transform {
  childCount
  eulerAngles : Vector3
  forward : Vector3
  hasChanged
}

Object <|-- Component
Component <|-- Transform
@enduml
{{< /puml >}}

# 참고 문헌

- [What is the difference between Component, Behaviour and MonoBehaviour? And why these are separated?/StackOverflow](https://stackoverflow.com/questions/44540747/what-is-the-difference-between-component-behaviour-and-monobehaviour-and-why-t)
- [중요 클래스/Unity Documentation](https://docs.unity3d.com/kr/2023.2/Manual/ScriptingImportantClasses.html)