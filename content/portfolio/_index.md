---
title : "송재민: 포트폴리오"
toc: true

mathjax: true
plantuml: true
---

# 소개

{{<admo>}}

안녕하세요, **게임 프로그래머**를 지망하는 송재민입니다.  

저는 문화와 예술을 진심으로 사랑하는 사람으로서,  게임이라는 매체의 무한한 가능성에 매료되어 게임 클라이언트 개발자의 길을 걷고자 합니다. 

이 포트폴리오에 정리된 내용은 제가 게임 프로그래머를 준비하며 쌓아온 경험과 활동들입니다.  

제 꿈은 다른 사람들이 "인생 게임"이라고 부르는 게임을 만드는 것입니다.  

앞으로도 계속해서 배움과 도전을 멈추지 않으며, 그런 게임을 만들기 위해 노력하겠습니다.

감사합니다.

{{</admo>}}

# 기술 스택

{{<admo>}}

**Major**

* C#/Unity
* C++/Unreal Engine
* Git/GitHub

**Interested in...**

* Vim
* Cmake

{{</admo>}}

# 팀 프로젝트

{{<admo title="팀 프로젝트 소개">}}

저는 실제로 사람들이 즐겁게 플레이 하는 게임을 다양한 직군의 사람들과 함께 만들어 보고 싶었습니다.

이를 목표로 저는 직접 사람들을 모집해 팀을 만들거나, 이미 있는 팀에 들어가 협업하는 경험을 쌓았습니다.

* 총 3번의 팀 프로젝트를 진행하였고, 그 중 2번은 **팀장** 역할을 맡았습니다.
* 모든 프로젝트에서 메인 프로그래머로 작업하였고, 프로젝트의 주요 기술적 의사결정들을 주도하였습니다.

{{</admo>}}

## 👻그림 메모리즈 프로젝트  <sup class="rub-inline-date">[2024-10 ~ Now]</sup>

{{<admo title="👻그림 메모리즈 정보">}}
* **팀 규모 및 정보** 현직자와 준비생으로 이루어진 7-9명
* **작업 방식** 비대면
* **직책** 메인 프로그래머, 프로젝트 매니저
* **목표** 게임 데모 출시 및 공모전 제출(컴:온)
* **게임 개요** "장그림"이라는 주인공의 슬픈 과거사를 기반으로 한 서사 중심의 1인칭 호러 방탈출
* **Github** [WAHLE59/Project_BM](https://github.com/WHALE59/Project_BM)
* **주요 기여 내역**
  * [**프로젝트 매니저**] 
     * 팀장과 함께 전체 개발 스케줄 관리 및 업무 분배
     * 주간 회의 계획 및 주도
  * [**프로그래머**] 
     * 1인칭 캐릭터 컨트롤러 제작(절차적 발소리 + 카메라 쉐이킹)
     * 상호작용 시스템 구현
     * FMOD 활용한 전체 사운드 프로그래밍
     * 현지화 작업
     * 팀원들의 편의를 위한 에디터 도구 개발
* **성과**
  * 컴투스 공모전 컴:온 제출 ([제출 트레일러](https://www.youtube.com/watch?v=EZtdZAEcpg8))
* **프로젝트 상세 페이지** {{% mdlink "/portfolio/grim_memories" "🔗👻그림 메모리즈 프로젝트 상세 페이지" %}}
{{</admo>}}

### 본 프로젝트를 진행하면서 마주한 고민과 해결책

**컴포넌트 기반 구조로 개선한 1인칭 컨트롤러**

* **문제 인식** 
  * 초기 1인칭 컨트롤러는 빠른 프로토타이핑을 위해, 발소리 재생과 카메라 셰이킹이 이동 속도에 하드코딩되어 있었습니다. 이로 인해 기획자가 캐릭터의 속도를 조정할 때마다 관련 기능을 모두 수정하고, 사운드 애셋도 새로 만들어야 하는 유지보수 문제가 있었습니다.
* **해결 방향** 
  * 변경에 유연하게 대응하기 위해, 컴포넌트 기반 구조로 재설계했습니다. 캐릭터의 이동 속도에 따라 '발 딛는 이벤트'를 절차적으로 생성하고, 이 이벤트에 다양한 기능을 바인딩할 수 있게 하였습니다.
* **성과**
  * 발소리, 카메라 셰이킹 등의 기능이 서로 독립된 컴포넌트로 분리되어, 캐릭터의 속도 변경이 전체 구조에 영향을 주지 않게 되었습니다. 결과적으로 기능 확장성과 유지보수성 모두 향상되었습니다.
* **구현 코드**
  * [*LocomotiveAction.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Character/LocomotiveAction.cs) 
    * 캐릭터의 이동 행동입니다.
  * [*LocomotiveImpulseGenerator.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Character/LocomotiveImpulseGenerator.cs) 
    * 캐릭터의 이동 행동시 속력에 비례하여 발생하는 발딛음 사건입니다.
  * [*CameraNoiseHandler.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Character/CameraNoiseHandler.cs)
    * 발딛음 사건에 바인딩 되는 카메라 셰이킹 효과를 제어합니다.
  * [*FootstepAudio.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Character/FootstepAudio.cs)
    * 발딛음 사건에 바인딩 되는 발소리 재생 효과를 제어합니다.

**다형성을 활용한 상호작용 시스템 구현**

* **문제 인식**
  * 기획 초기에는 조준선에 올린 오브젝트에 상호작용 UI가 표시된다는 점 외에는 상호작용 시스템에 대한 구체적인 정의가 없었습니다. 상호작용 아이템 목록과 상호작용의 구체적인 내용이 거의 정해져 있지 않았습니다.
  * 예를 들어 상자는 열리고, 열쇠는 사라지며, 문은 잠금이 해제되는 등 상호작용 대상마다 수행되는 동작의 성격이 매우 달랐지만, 모두 동일한 경로로 상호작용을 시작했습니다. 
* **해결 방향**
  * 상호작용 가능한 오브젝트를 모두 공통의 기초 클래스에서 유도하였고, 이 클래스의 다형성을 통해 각 오브젝트가 고유의 상호작용 로직을 갖도록 설계했습니다.
  * 상호작용 로직은 `StartInteract()` 가상 함수를 통해 정의하였고, 개별 오브젝트는 이를 오버라이드하여 자신만의 행동을 구현하였습니다.
  * C#의 인터페이스(`IInteractable`)를 사용하는 방식도 고려했지만, 기본 구현이 필요한 상황이 많았기 때문에 추상 클래스 기반으로 설계했습니다.
* **성과**
  * 기획안에서 새로운 상호작용 대상이 확정될 때마다 새로운 오브젝트의 추가가 간결해 지는 등, 확장성과 유지보수성이 모두 개선되었습니다.
* **구현 코드**
  * [*InteractableBase.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Interactables/InteractableBase.cs)
    * 상호작용 오브젝트들의 공통 함수성을 정의한 기초 클래스입니다.
  * [*DarackKeyFar.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Interactables/Interactables/DarackKeyFar.cs)
    * 상호작용 예시 오브젝트 (1) - 열쇠
  * [*GirlsChest.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Interactables/Interactables/GirlsChest.cs)
  * [*DarackCurtain.cs*](https://github.com/WHALE59/Project_BM/blob/main/Assets/Scripts/Interactables/Interactables/DarackCurtain.cs)
    * 상호작용 예시 오브젝트 (2) - 상자
    * 상호작용 예시 오브젝트 (3) - 커튼

## 👽에일리언 프로젝트 <sup class="rub-inline-date">[2024-06 ~ 2024-09]</sup>

{{<admo title="👽에일리언 프로젝트 정보">}}
* **팀 정보 및 규모** 현직자와 준비생으로 이루어진 4명
* **작업 방식** 비대면
* **직책** 팀장, 기획자, 메인 프로그래머
* **목표** 게임 데모 출시 및 BIC 공모전 제출
* **게임 개요** 미소녀를 주인공으로 하고, 플레이어가 액션 콤보를 직접 설계할 수 수 있는 탑 다운 3D 로그라이트
* **Github** [nachiketa3299/Alien_Project](https://github.com/nachiketa3299/Alien_Project)
* **주요 기여 내역**
  * [**기획자**]
    * "액션 토큰"이라는 개성적인 시스템을 활용하는 게임 전체 기획
  * [**프로그래머**]
    * TPS 캐릭터 컨트롤러 제작
    * 캐릭터 - 에너미 프레임워크 제작 및 AI 설계
* **성과** BIC 공모전 MVP 빌드 제출
* **프로젝트 상세 페이지** {{% mdlink "/portfolio/alien" "👽에일리언 프로젝트 상세 페이지" %}}
{{</admo>}}

### 프로젝트를 진행하면서 겪었던 문제와 해결책

**AI용 시각 컴포넌트 개발**

* **문제 인식**
  * AI가 항상 플레이어 위치를 추적하는 것이 아니라, *인지 범위*와 *조건*에 따라 감지하도록 만들어야 액션 게임으로서 긴장감이 유지된다고 판단했습니다.
* **해결 방향**
  * AI가 시야각, 반경, 장애물 여부에 따라 플레이어 인지 여부가 결정되도록 설계했습니다.
  * 추상감각 클래스 `SensorBase`를 정의하여 인지 기능에 대한 공통 구조(레이어 필터, 이벤트 등)을 제공하고, 이를 기반으로 *시각* 감각 전용 구현체 `CVision`을 작성하였습니다.
* **성과**
  * AI가 장애물 유무, 레이어 필터 종류에 따라 다양한 방식으로 플레이어를 인지할 수 있게 되었습니다.
  * `SensorBase`를 기반으로 공통 인터페이스와 기능을 분리했기 때문에, 유지보수와 확장이 용이한 감각 프레임워크가 되었습니다.
* **구현 코드**
  * [*SensorBase.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/Sensors/SensorBase.cs)
    * 감각 기능의 기초 클래스입니다.
  * [*CVision.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/Sensors/CVision.cs)
    * 감각 기능의 시각 구현입니다.
  * [*CEnemy.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/CEnemy.cs)
    * 감각 기능으로 플레이어를 탐지하는 적 오브젝트입니다.

**캐릭터/에너미 공통 프레임워크 및 AI 설계**

* **문제 인식**
  * 액션 로그라이트 장르의 게임을 개발하고 있었고, 플레이어가 적의 행동을 예측하고, 그에 맞춰 전략을 수립하는 플레이 경험이 중요하다고 생각하였습니다.
  * 이를 위해서 플레이어와 적이 동일한 규칙 하에 움직이고, 유사한 행동 체계를 공유하면 좋겠다고 생각했습니다.
* **해결 방향**
  * Unreal Engine의 게임플레이 프레임워크를 참고하여, 컨트롤러-폰(Pawn)구조를 Unity 방식으로 구현하였습니다.
  * 컨트롤러는 폰의 행동을 제어하는 책임이 있고, `PlayerController`와 `AIController`로 파생합니다. `Pawn`은 컨트롤러에 의헤 제어되는 개체로, `Character`와 `Enemy`로 파생됩니다. `Pawn`의 행동은 "행동 모듈"로 구현되며, 각 모듈이 존재하는 경우 수행하고, 없을 경우 무시됩니다.
* **성과**
  * 플레이어 캐릭터와 AI Enemy가 동일한 인터페이스를 통해 제어 가능해졌고, 다양한 상황에 따라 Pawn을 동적으로 교체하거나 재활용할 수 있는 구조를 만들었습니다.
  * 새 행동을 추가할 때에는 행동 모듈을 제작하여 `Pawn`에 부착하면 되어 확장성과 유지보수성이 개선되었습니다.
  * 플레이어 캐릭터와 AI Enemy가 필요한 경우 동일한 행동 모듈을 공유할 수 있어, 개발의 용이성이 증가하고, 초기에 고민했던 예측 가능한 플레이 경험을 구현할 수 있었습니다.
* **구현 코드**
* [*PawnControllerBase.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/Controllers/PawnControllerBase.cs)
  * 컨트롤러들의 기초 클래스입니다.
  * [*CAIController.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/Controllers/CAIController.cs)
  * [*CCharacterController.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/Controllers/CCharacterController.cs)
* [*PawnBase.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/PawnBase.cs)
  * Pawn들의 기초 클래스입니다.
  * [*CCharacter.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/CCharacter.cs)
  * [*CEnemy.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/CEnemy.cs)
* [*MovementActionBase.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/Actions/MovementActions/MovementActionBase.cs)
  * 행동 모듈 중 이동 행동의 기초 클래스입니다.
  * [*CAccelerationMovement.cs*](https://github.com/nachiketa3299/Alien_Project/blob/master/Assets/01_Scripts/Pawns/Actions/MovementActions/CAccelerationMovement.cs)

## 🐔먼치킨 프로젝트 <sup class="rub-inline-date">[2024-09 ~ 2024-12]</sup>

{{<admo title="`🐔먼치킨` 프로젝트 정보">}}
* **팀 정보 및 규모** 현직자와 준비생으로 이루어진 4명
* **작업 방식** 비대면
* **직책** 팀장, 기획자, 메인 프로그래머
* **목표** 게임 데모 출시 및 공모전 제출
* **게임 개요** 독특한 생애주기를 갖는 사망전대 캐릭터 "닭"을 주인공으로 내세운 고난이도 2.5D 플랫포머
* **Github** [nachiketa3299/Munchkin](https://github.com/nachiketa3299/Munchkin)
* **주요 기여 내역**
  * [**기획자**]
    * 독특한 생애주기를 가진 캐릭터를 내세운 게임 전체 기획
  * [**프로그래머**]
    * 2.5D 플랫포밍 캐릭터 컨트롤러 제작
    * 캐릭터-알 생애주기 관리 시스템 제작
    * 동적 3D 타일맵 로딩 시스템 제작
* **프로젝트 상세 페이지** {{% mdlink "/portfolio/munchkin" "🐔먼치킨 프로젝트 상세 페이지" %}}
{{</admo>}}

### 프로젝트를 진행하면서 겪었던 문제와 해결책

**동적 씬 로딩 시스템 구현**

* **문제 인식**
  * <항아리 게임>처럼 하나의 커다란 월드를 배경으로 캐릭터가 끊임없이 점프와 이동을 반복하여 상승하는 대규모 플랫포머 게임을 목표로 개발중이었습니다. 플레이어가 로딩 없이 자연스럽게 큰 세계에서 플레이하고 있다는 감각을 느끼게 하고 싶었기에, 끊기 없는 넓은 맵을 구현하는 것이 핵심 과제였습니다.
* **해결 방향**
  * 전체 월드를 스테이지 단위로 씬을 분할한 후, 해당 씬들의 인접 관계를 Scriptable Object에 기록하였습니다. 그리고, 플레이어의 월드 위치를 기준으로 인접한 씬들을 동적으로 로드하거나 언로드하는 시스템을 구현하였습니다.
  * 추가적으로, 특정 중요 오브젝트(알)가 존재하는 경우에도 씬을 로드하거나, 언로드를 지연하는 요소도 도입하였습니다.
* **성과**
  * 메모리에는 최소한의 씬만 로드하면서, 플레이어가 넓은 공간에서 플레이하고 있다는 감각을 전달하는 시스템을 구현하는데 성공하였습니다.
* **구현 코드**
  * [*SceneLoadTrigger.cs*](https://github.com/nachiketa3299/Munchkin/blob/master/Assets/Scripts/Cores/SceneLoading/SceneLoadTrigger.cs)
    * 월드 위치에 따라 씬 로드 요청을 송신하고, 언로드를 지연시킬 오브젝트에 부착합니다.
  * [*SceneLoadManager.cs*](https://github.com/nachiketa3299/Munchkin/blob/master/Assets/Scripts/Cores/SceneLoading/SceneLoadManager.cs)
    * `SceneLoadTrigger`의 요청을 수신하여 실제로 씬 로드와 언로드를 처리합니다.
  * [*SceneDependencyData.cs*](https://github.com/nachiketa3299/Munchkin/blob/master/Assets/Scripts/Cores/Data/SceneDependencyData.cs)
    * 씬들의 인접 관계를 그래프로 저장하는 ScriptableObject 입니다.

# 개인 프로젝트

## 🧙특급 주술 대전 모작 프로젝트

> [**🧙특급 주술 대전 모작 프로젝트**]
> 
> * **목표** 핵심 게임 로직 구현
> * **GitHub** [nachiketa3299/Jusul](https://github.com/nachiketa3299/Jusul)
> * **프로젝트 상세 페이지** [README.md](https://github.com/nachiketa3299/Jusul/blob/master/README.md)

### 본 프로젝트를 진행하면서 마주한 고민과 해결책

**명시적 초기화 시점 통제**

* **문제 인식**
  * 프로젝트 전반에 걸쳐 여러 매니저성 오브젝트가 싱글턴 패턴으로 구성되어 있었고, 대부분 `Awake()`에서 인스턴스를 할당하는 방식이었습니다.
  * 유니티 엔진은 스크립트간 호출 순서가 보장되지 않기 때문에 매니저 스크립트의 `Awake()`가 호출되기 이전에 다른 스크립트의 `Start()`가 호출되고, 거기서 싱글턴을 참조하는 경우 `null` 참조 문제가 자주 발생하였습니다.
* **해결 방향**
  * 싱글턴을 `Awake`에서 초기화하지 않고, 중앙 초기화자 역할을 하는 `GameBootstrapManager`를 만들어 초기화 순서를 명시적으로 관리하였습니다.
* **성과**
  *  초기에 약간의 엔지니어링 비용이 소요되었지만, 추후 다양한 매니저 스크립트가 `Awake()`나 `Start()`의 순서에 의존하지 않고, 명시적으로 의존성으로 통제하는 구조를 확보하였습니다.
* **구현 코드**
  * [*GameBootstrabManager.cs*](https://github.com/nachiketa3299/Jusul/blob/master/Assets/Scripts/Manager/GameBootstrabManager.cs)

**ScriptableObject 기반 스킬 시스템 설계**

* **문제 인식**
  * 약 30종 이상의 상이한 스킬들을 구현해야 하는 게임에서 각 스킬은 고유한 동작과 이펙트를 가지고 있어 하드코딩으로 처리할 경우 유지보수가 어려웠습니다.
* **해결 방향**
  * 각 스킬을 `ScriptableObject`로 정의하고, 공통 추상 클래스 `SkillBase`의 `Fire()` 가상 메서드를 오버라이드 하는 방식으로 로직을 캡슐화 했습니다.
  * 실제 스킬의 실행은 `MonoBehaviour` 기반의 `SkillModule`이 담당하며, 런타임 시점에 스킬 오브젝트를 주입받아 `Fire()`를 호출하는 구조로 구현하였습니다.
* **성과**
  * 새로운 스킬을 추가할 때 `Fire`만 구현하면 되므로 확장성과 유지보수성이 크게 향상되었습니다.
* **구현 코드**
  * [*SkillBase.cs*](https://github.com/nachiketa3299/Jusul/blob/master/Assets/Scripts/Skill/SkillBase.cs)
  * [*SkillModule.cs*](https://github.com/nachiketa3299/Jusul/blob/master/Assets/Scripts/Module/SkillModule.cs)
  * [*Skill_F1_Burn.cs*](https://github.com/nachiketa3299/Jusul/blob/master/Assets/Scripts/Skill/ConcreteSkills/Fire/Skill_F1_Burn.cs)

**UI 와 게임 로직 사이의 강한 결합 문제 해결**

* **문제 인식**
  * UI가 매우 많이 등장하는 게임으로, 처음에는 UI가 직접 게임 상태를 변경하거나 게임 로직이 UI의 상태에 의존하는 등, UI과 게임 로직이 강하게 결합되어 개발에 차질을 빚었습니다.
* **해결 방향**
  * MVC 아키텍쳐를 응용하여 뷰, 컨트롤러, 모델의 책임을 명확히 분리하였습니다. 모델과 컨트롤러는 UI의 로직을 알 필요 없게 만들었습니다.
* **성과**
  * UI가 게임 상태를 직접 수정하지 않게 되어 테스트와 유지보수 효율이 향상되었습니다.
* **구현 코드**
  * [*SkillPurchaseButton.cs*](https://github.com/nachiketa3299/Jusul/blob/master/Assets/Scripts/UI/MainUI/4_MainButtons/SkillPurchaseButton.cs)
  * [*BountySpawnButton.cs*](https://github.com/nachiketa3299/Jusul/blob/master/Assets/Scripts/UI/MainUI/3_PopupMenus/Bounty/BountySpawnButton.cs)

## ✍️AI 활용 개인 블로그 제작 및 운영

> [**개인 블로그 제작 및 운영**]
>
> * **블로그 링크** [Even idiots can make game](https://nachiketa3299.github.io/RUB/)
> * **블로그 소개** 게임 개발을 하며 마주하는 고민과 해결 과정, 배운 것들을 기록하는 자체 제작 블로그
> * **사용 도구** Cursor AI, Hugo, Github Pages/Actions
> * **GitHub** [nachiketa3299/RUB](https://github.com/nachiketa3299/RUB)

* 원본 테마 [hanwenguo/hugo-theme-nostyleplease](https://github.com/hanwenguo/hugo-theme-nostyleplease)를 기반으로 하여 Cursor AI로 블로그 구조와 각 컴포넌트들을 프로토타이핑하고, 추후 수정하였습니다.
* Github Action을 이용해 Hugo로 빌드하여 배포하고 있습니다.

## 기타 진행 중인 토이 프로젝트

* [nachiketa3299/Soda](https://github.com/nachiketa3299/Soda)
  * CMake, D3D를 이용한 자체 제작 게임 엔진 
  * 추후 멀티플랫폼 + 멀티 그래픽스 API로 확장 예정
* [DSAG](https://github.com/nachiketa3299/DSAG) 
  * C++ STL를 이용해 직접 유명 알고리즘과 자료구조를 구현
  * Google Test를 이용해 검증

# 기타 활동

## 언리얼 랩스 활동

{{<admo title="언리얼 랩스 활동">}}

* **규모** 15명
* **개요** 학원 수강 후 열의과 능력을 인정받은 학생들을 대상으로 언리얼 엔진 소스 코드 분석 프로젝트 진행
* **직책** Actor Component팀 팀장
* **주요 기여 내역**
  * 언리얼 엔진 4의 `UActorComponent` 컴포넌트 소스 코드 분석 주도
    * [Actor Component 팀 발표 자료](https://docs.google.com/presentation/d/19-R6U1GwiAnyQH91bM8MlbIXAxXcxeDGW7L3T93jJ6w/edit?usp=sharing)
  * 팀 전체 작업 가이드라인 작성
* **언리얼 랩스 활동 기록 페이지** {{% mdlink "portfolio/unreal_labs" "🔗 Unreal Labs 활동 기록 페이지"%}}

{{</admo>}}