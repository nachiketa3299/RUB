---
layout: home
title: Event Idiots Can Make Games
---

# 소개

# Available Skills

* Unity 5(2D + 3D), Unreal Engine 4
* Git
* C/C++, C#, Python, Lua, Dart
* Visual Studio / Visual Studio Code
* Vim

# 참여 프로젝트



## "Grim Memories" 프로젝트 <sup><i>2024년 9월 ~ 현재</i></sup>

<iframe width="560" height="315" src="https://www.youtube.com/embed/EZtdZAEcpg8?si=08tsFxncRMNzdaYe" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

* 팀 규모: 7명
* 게임 개요:
	* 1인칭 시점의 공포 테마 방 탈출 게임
	* 선형적인 스토리와 영화같은 연출 부각
	* 동일한 공간을 두 가지 다른 시각적 테마로 체험할 수 있는 것이 특장점
* 직책: 메인 프로그래머, 프로젝트 매니저
* 목표: 공모전 제출, Itch.io와 Steam에 게임 데모 출시

### 주요 구현 사항

* 프로젝트 매니저로서 업무 배분 및 일정 관리
* 상주 씬과 월드 씬을 분리하여 협업 워크플로우 구축
* 캐릭터 컨트롤러 및 상호작용 시스템 구현
* 전체 사운드 프로그래밍

#### 1인칭 캐릭터 컨트롤러 전체 구현

1인칭 시점의 캐릭터 컨트롤러를 구현했습니다.

조용하고 정적인 공간에서 대부분의 플레이가 진행되는 기획이었기 때문에 캐릭터의 이동에 따른 시청각적 피드백(카메라 흔들림, 사운드)을 강조하는 방향으로 작업했습니다.

|![Locomotion System](./Images/LocomotionSystem.jpg)|
|:-:|
|*[이미지] Locomotion 시스템의 개괄*|

캐릭터 이동의 4가지 배타적 상태를 규정한 후, 메인 이동 컴포넌트(`LocomotiveAction`)에서 상태 변경을 관리하였습니다. 상태 구현에는 상태 패턴을 고려하였으나, 단순성을 위해 하드코딩된 조건문으로 구현했습니다.

관찰자 패턴을 활용하여 컴포넌트간 결합도를 낮출 수 있게 설계하였습니다.

예를 들어 이동 상태가 일반(`NormalJog`)에서 앉아 이동(`CrouchedJog`)으로 바뀌면, 캐릭터가 살금 살금 이동한다는 의미이므로 이동 충격(`LocomotionImpulse`)이 발생하는 주기가 길어집니다. 각 이동 충격에는 *발소리 재생*과 *카메라 떨림*이라는 사건이 발생합니다. 

|{::nomarkdown}<iframe width="560" height="315" src="https://www.youtube.com/embed/wIU7-DIbJHs?si=O6OLzsyhpoMB1-HY" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>{:/}|
|:-:|
|*[영상]각 상태별 이동 충격의 발생을 디버그 모드에서 시각화하는 영상*|


Unity에 구비되어 있는 `Cinemachine` 관련 컴포넌트들을 적극 활용하여 원하는 시각 효과를 편하게 적용/해제/수정 할 수 있도록 구현하였습니다. 

또한 자주 수정되는 데이터들을 Scriptable Object로 관리해, 기획자들이 플레이하며 의도에 부합한 움직임인지 테스트하고, 필요하다면 직접 수정할 수 있도록 만들었으며, 정기적인 플레이 테스트를 주도하였습니다.

#### 상호작용 시스템 구현

플레이어가 조준자로 검출한 오브젝트와 상호작용 하는 시스템을 구현했습니다.

상호작용 시스템 기획의 개괄은 아래와 같습니다. 

* `활성화`: 오브젝트가 가진 고유 기능을 작동시키기
* `수집`: 오브젝트를 캐릭터의 인벤토리에 넣기
* `사용`: 캐릭터의 인벤토리에 있는 오브젝트를 캐릭터의 손에 장착하고 다른 오브젝트에 사용하기

위 개념을 처음에는 그대로 게임의 구조에 적용하였으나, 기획의 잦은 수정과 의미 변경에 유연하게 대응하기 어려웠습니다. 
처음에는 `활성화`와 `수집`이 배타적인 속성으로 간주되었으나, 개발이 진척되면서 `활성화`와 `수집`의 요소를 동시에 갖는 오브젝트들이 등장했습니다.

예를 들어, '볏짚'은 처음에는 `수집` 가능한 오브젝트였습니다. 이 말은 월드에 '볏짚' 아이템이 존재하고, 이 아이템과 상호작용하면 '볏짚' 아이템은 월드에서 사라지면서, 인벤토리용 '볏짚' 아이템을 캐릭터의 인벤토리에 추가했습니다. 처음에 `수집`은 기획의 내용을 그대로 반영하여, `Collect`라는 한 번의 메서드 호출로 상호작용시 자기 자신을 씬에서 삭제하고, 캐릭터의 인벤토리에 지정한 아이템을 추가하도록 구현했습니다. 하지만 개발이 진척되면서 '볏짚' 아이템은 '볏짚통'에 들어있는 아이템으로 바뀌었고, 플레이어는 '볏짚통'과 상호작용하고, 그 결과로 '볏짚통'은 텅 비어있는 모델로 바뀌게 되고 캐릭터의 인벤토리에 '볏짚'을 추가하는 것으로 바뀌었습니다. 이러한 상호작용 아이템들의 목록이 상세한 기획서가 모두 구비된 것이 아니었어서, 기획자의 요구사항을 파악하고 유연하게 대응할 수 있도록 하는 것을 최우선으로 하여 상호작용 객체들의 기초 클래스를 설계하는 것에 집중하였습니다.

저는 상호작용의 기획적 개념들을 `Interact(활성화 + 수집)` 과 `Use` 라는 구체적인 2개의 개념으로 재정의한 후 구현하였습니다. 

또한 상호작용 가능한 오브젝트의 다음과 같은 문제를 해결해야 했습니다.

* 상호작용 오브젝트는 $$n(n \geq 1)$$개의 `MeshRenderer`가 계층 구조를 형성하고 있을 수 있다.
* 상호작용을 감지하는 콜라이더의 형태는 상호작용 오브젝트의 메쉬의 형태와 관련이 없을 수도 있다.
* 여러 상호작용 오브젝트들끼리 공유하는 상태가 존재하기는 하지만, 전이하는 상태와 행동이 기본적으로 매우 다르다.

|![Interactable Editor Example](./Images/InteractableExample.png)|
|:-:|
|*[이미지] 상호작용 오브젝트 `GirlsChest`의 예시*|

  

|{::nomarkdown}<iframe width="560" height="315" src="https://www.youtube.com/embed/jboTbFeA7Ys?si=RhgfaL5SJVG6ItEp" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>{:/}|
|:-:|
|*[영상] 상호작용 시스템*|

#### FMOD Unity를 활용한 사운드 시스템 구축

사운드 디자이너 분과 게임에서 더 질좋은 사운드 경험을 위해 FMOD Unity를 사용하기로 협의하였습니다.  FMOD Event 디자인의 일부에 참여하였고, 전체 게임의 사운드 프로그래밍을 담당하였습니다.

|![FMOD Example](./Images/FMOD%20Example.png)|
|:-:|
|*[이미지] 바닥의 재질과 이동 상태에 따라서 다른 발소리 세트를 재생하도록 디자인된 FMOD Event의 예시*|

FMOD Unity를 사용하는 것은 디자이너 분과 저 모두 처음이었지만, 서로 주도적으로 학습한 후 워크플로우를 구축하였습니다. 그래서 작업 영역이 서로 충돌하지 않으면서, 서로의 피드백이 빠르게 반영되어 멋진 작업물이 나올 수 있었습니다.


|{::nomarkdown}<iframe width="560" height="315" src="https://www.youtube.com/embed/b9WOPtTx5T4?si=K8wXhzubScijbV1x" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>{:/}|
|:-:|
|*[영상] 발소리 시스템*|

* 플레이어가 입력을 하면 즉각적으로 발소리가 재생됩니다.
	* 하지만, 현재 이동 상태(기본, 앉기, 걷기)가 허용하는 발소리 간격보다 짧게 발소리를 재생하지는 않습니다.
* 한 번의 이동 충격에 발소리는 랜덤한 세트 중에 하나가 재생됩니다. 그리고, 지정된 확률에 기반하여 발소리에 대한 반응 소리의 세트중 랜덤한 하나가 재생될지의 여부도 결정됩니다. (나무 바닥을 밟아 *끼이이익*하는 소리)
* 캐릭터의 이동 상태와 캐릭터가 이동하는 바닥에 재질에 따라 발소리는 다릅니다.
* 캐릭터의 기본 발소리의 이벤트 인스턴스는 게임을 시작하면 생성되고, 게임을 종료하면 파괴됩니다. 재질에 따른 발소리는 캐릭터가 재질을 나타내는 볼륨에 입장하면 생성되고, 탈출하면 파괴됩니다.

이에 더해, 단발성 오브젝트 3D 효과음, 앰비언스와 UI 2D 효과음들을 작업하였습니다.

#### Localization 협업 시스템 구축

Unity의 Localization 패키지를 이용하여 스트링 테이블로 최종 플레이어에게 전달되는 모든 문자열을 관리하였습니다. 그리고 해당 문자열 테이블을 Google SpreadSheet로 Push / Pull 할 수 있게 만들어 기획자분들이 쉽게 내용을 변경하고 게임에 적용할 수 있게 시스템을 구축하였습니다.

|![Localization](./Images/LocalizationExample.png)|
|:-:|
|*[이미지] Google Sheet 사용한 Localization String 워크플로우*|

다음처럼 중첩된 Smart String을 적용하여 Localized UI를 구현하였습니다.

|![Localization-In-Game](./Images/LocalizationIngame.png)|
|:-:|
|*[이미지] Localization이 최종적으로 인게임에 구현된 모습*|

#### 개발 편의를 위한 에디터 도구 개발

저희 게임은 카메라와 캐릭터 등, 씬 전환에 따라 언로드되면 안 되는 오브젝트들이 존재하는 *상주 씬(PersistentGameplay)* 에 월드 씬을 Additive로 로드하는 구조로 작동합니다. 

저희는 커밋을 하기 전에 빌드를 해서 문제없이 돌아가야 한다는 규칙이 있었는데요, 비개발 직군이 해당 테스트를 쉽게 진행하기 위해 에디터 ~ 빌드게임 간 스크립트를 작성했습니다.

|![CharacterStart](./Images/CharacterStart.png)|
|:-:|
|*[이미지] 모든 씬의 시작 지점을 테스트해 볼 수 있는 Character Start*|

`CharacterStart` 클래스는 Unreal Engine에서 작업했던 경험을 되살려 작성하였습니다. 에디터에서 작동할 때, 상주 씬이 중첩 로드되지 않아 있다면, 이 오브젝트는 상주 씬을 자동으로 중첩 로드하고 자신이 속한 씬을 활성 씬으로 만든 후, 상주씬의 캐릭터 오브젝트의 트랜스폼을 자신의 트랜스폼과 일치시킵니다.

빌드 게임에서는 약간 다르게 작동합니다. 
상주 씬에 게임의 시작 월드 씬을 로드하는 로직이 들어있기 때문에, 상주 씬은 게임에서 가장 먼저 로드되어야 하고, 빌드 인덱스 0번이어야 합니다. 이를 비개발 팀원에게 이해시키는 것은 어렵고 필요하지도 않았기 때문에 상주 씬의 빌드 인덱스를 강제로 0번으로 만드는 `PreBuilder` 네이티브 C# 클래스를 작성하였습니다.

<details>
<summary>PreBuilder.cs</summary>

{% highlight csharp %}
using System.Linq;

using UnityEditor;
using UnityEngine;

namespace BM.Editors
{
	/// <summary>
	/// 유니티 에디터에서 빌드 버튼 눌렀을 때의 이벤트를 후킹하여 스크립트 추가. <br/>
	/// SC_PersistentGameplay 씬을 빌드 인덱스 0 으로 강제로 만들고 활성화 한다. <br/>
	/// SC_PersistentGameplay 씬이 빌드 설정에 없으면 경고를 띄우고 빌드를 중지한다. <br/>
	/// 추후 게임이 형태를 갖춰가면 변경
	/// </summary>
	/// <remarks>
	/// 로그는 `%LOCALAPPDATA%/Unity/Editor 에서 확인
	/// </remarks>
	[InitializeOnLoad]
	public static class PreBuilder
	{
		private static readonly string m_persistentGameplaySceneName = "SC_PersistentGameplay";

		static PreBuilder()
		{
			BuildPlayerWindow.RegisterBuildPlayerHandler(OnClickingBuild);
		}

		private static void OnClickingBuild(BuildPlayerOptions options)
		{
			Debug.Log("[BM.PreBuilder] 빌드 후킹 프로세스 시작");

			var scenes = EditorBuildSettings.scenes.ToList();
			var persistentSceneIndex = scenes.FindIndex(scene => scene.path.Contains($"{m_persistentGameplaySceneName}"));

			Debug.Log($"{m_persistentGameplaySceneName}의 빌드 인덱스는 {persistentSceneIndex} 입니다.");

			// 상주 씬이 발견되지 않음
			if (persistentSceneIndex < 0)
			{
				var label = $"File > Build Settings 에 {m_persistentGameplaySceneName} 씬이 없습니다. 해당 씬을 빌드 씬에 추가해 주세요.";

				EditorUtility.DisplayDialog("[BM.PerBuilder] 빌드 오류", label, "알겠습니다. (빌드를 중단합니다)");
				Debug.Log(label);

				return;
			}
			// 상주 씬이 발견되었고, 정상 설정
			else if (persistentSceneIndex == 0)
			{
				Debug.Log($"[BM.PreBuilder] {m_persistentGameplaySceneName} 씬이 이미 빌드 오더 0이었기 때문에, 기본 설정으로 빌드를 시작합니다.");
				BuildPlayerWindow.DefaultBuildMethods.BuildPlayer(options);
			}
			// 상주 씬이 발견되지 않았고, 비정상 설정
			else
			{
				var persistentScene = scenes[persistentSceneIndex];

				scenes.RemoveAt(persistentSceneIndex);
				scenes.Insert(0, persistentScene);

				options.scenes = scenes.Select(scene => scene.path).ToArray();

				Debug.Log($"[BM.PreBuilder] {m_persistentGameplaySceneName} 씬이 빌드 오더 0이 아니었기 때문에, 빌드 오더 0으로 만들었습니다.");

				if (!persistentScene.enabled)
				{
					persistentScene.enabled = true;
					Debug.Log($"[BM.PreBuilder] {m_persistentGameplaySceneName} 씬이 빌드 설정에서 활성화 되지 않았기 때문에, 활성화 시킵니다.");
				}

				BuildPlayerWindow.DefaultBuildMethods.BuildPlayer(options);
			}
		}
	}
}
{% endhighlight %}

</details>

|![StartScene](./Images/StartScene.png)|
|:-:|
|*[이미지] Start Scene Selector*|

또한 빌드 게임의 진입 월드 씬을 설정할 수 있도록 에디터 전용 메뉴를 만들었고, 해당 메뉴에서 Scriptable Object의 내용을 수정하는 방식으로 상주 씬이 빌드 게임의 시작 시점에 어떤 씬을 로드할 지 결정할 수 있도록 만들었습니다. 상주 씬의 `SceneLoadManager`가 해당 Scriptable Object에 기록된 씬을 게임 시작 시점에 로드하고, 해당 씬의 `CharacterStart`를 찾아 플레이어를 이동시키고 초기화합니다.

이에 더해 여러 씬의 테스트를 빌드 게임에서 편하게 만들기 위해, Developer Overlay를 만들어 빌드 게임에서 씬 전환을 쉽게 만들었습니다. 

|![DeveloperOverlay](./Images/DevOverlay.png)|
|:-:|
|*[이미지] Developer Overlay*|

다른 팀원들에게 반응이 좋았던 기능입니다.

---

## "Munchkin" 프로젝트 <sup><i>2024년 6월 ~ 8월</i></sup>

* 직책: 팀장, 메인 프로그래머, 메인 기획자
* 팀 규모: 4명
* 게임 개요 
	* \<Getting Over It\>에서 영감을 얻은 고난이도 2.5D 플랫포밍 게임
	* "달걀 → 병아리 → 닭"이라는 고유의 생애주기를 갖는 캐릭터를 주인공으로 내세운 점이 특이점. 실패가 빈번한 어려운 게임이지만 "가장 가까운 알"에서 "병아리" 상태로 부활한다는 고유의 메커니즘으로 게임을 클리어할 수 있도록 기획.
* 목표: Itch.io에 게임 데모 출시
* 전체 기획서 링크
	* [전체 콘셉트](https://substantial-panther-211.notion.site/9a3725e57d7b41a5891e7c0fe1c0d3d5?pvs=4)
	* [기획 용어 정리](https://substantial-panther-211.notion.site/a19b8ac4a4904419a9b0a693b6b12ae4?pvs=4)
	* [게임의 생애주기](https://substantial-panther-211.notion.site/61fe3ea8d1bb4b14b68105bb148ddb04?pvs=4)
	* [게임플레이 서사](https://substantial-panther-211.notion.site/edf4c88bdcd14b2aa3114abfacb01176?pvs=4)
	* [플레이어 입력](https://substantial-panther-211.notion.site/853508194aae4672a58a6a2715d4f414?pvs=4)
	* [캐릭터 기획](https://substantial-panther-211.notion.site/243480d1e8b44ada8704811f08be5de6?pvs=4)
	* [장치와 함정 기획](https://substantial-panther-211.notion.site/3dd5857436dc4a5abdaf021cf439e263?pvs=4)
	* [레벨과 스테이지 기획](https://substantial-panther-211.notion.site/5553f23380f448b7a10b1157e1f28512?pvs=4)

### 주요 구현 사항

#### 주요 기술적 설계 의사결정 주도

* 게임 플레이 내내 절대 언로드되지 않는 상주 씬(Persistent Scene)에 월드 씬을 런타임에 Additive 모드로 로드 / 언로드하여 게임플레이 월드를 구축
	* 이를 위해, 씬 간의 물리적 인접 관계를 에디터에서 그래프로 표현 후, 런타임에 해당 그래프를 탐색하여 필요한 씬을 로드하고 언로드하는 시스템을 구축.
* 레벨 디자인에서 수정이 용이하도록, Tilemap의 GameObject 브러시를 이용하여 블럭으로 모듈화된 분할 월드 씬 개발


#### 동적 Additive 씬 로딩 시스템 구축

메트로배니아 장르의 게임 처럼 거대한 맵에서 플랫포밍을 하는 게임으로, 플레이어에게 가시적인 로딩이 없었으면 좋겠다고 생각했습니다. 그래서 게임 월드를 작은 씬들로 쪼개, 필요에 따라 런타임에 로드하고 언로드하는 방식을 구현하려 하였습니다.

여기서 씬의 로드가 필요한 경우는 다음과 같습니다.
* 주요 오브젝트(예: 캐릭터)가 현재 존재하는 씬과, 해당 씬과 깊이 $$n$$으로 인접한 씬

위와 같은 상태가 아닌 씬들은 모두 언로드가 필요합니다.

씬의 로드가 필요한 오브젝트는 "캐릭터"와 "알" 이었습니다. 캐릭터가 사망 처리된 경우, 영혼으로 변하여 "알"로 지형을 무시한 채 이동하여 부활할 필요가 있기 때문이었습니다. (여기서 "알"은 Non-Kinematic Rigidbody 오브젝트입니다.)

캐릭터와 알 모두 다음과 같은 요청을 보내는 상황이라고 생각하였습니다.

> 내가 현재 존재하는 씬으로부터, 논리적 거리가 $$n$$이하인 씬들은 로드되어 있어야 하고, 그렇지 않은 씬들은 다른 오브젝트가 요청을 보내지 않았다면 언로드해도 괜찮아.

이를 위해 씬 로드/언로드 요청을 보내는 `SceneLoadTrigger`를 작성하였습니다. 이 스크립트는 해당 스크립트가 부착된 오브젝트가 어떤 씬의 경계[^3]에 들어갈 때, 해당 씬을 기준으로 설정된 거리 이내로 인접한 씬들을 로드해야 한다고 요청을 보냅니다.

[^3]: 씬마다 경계를 의미하는 Trigger Collider를 부착하였습니다.

그리고 다수의 `SceneLoadTrigger`들의 요청을 취합하여 최종적으로 씬 로드/언로드 연산을 수행하는 싱글턴 클래스 `SceneLoadManager`를 작성하였습니다.

씬 로드 / 언로드는 비동기 연산(`AsyncOperation`)이기 때문에 여러 프레임에 걸쳐 이뤄지는 일이지만, 어떤 씬을 로드하라 / 언로드하라 라는 요청은 "주요 오브젝트가 씬의 경계에 들어갈 때"라는 *물리적 사건*에 의해 일어나므로 이론적으로 중복되는 요청이 발생하기 쉬웠습니다.

예를 들어 씬 A가 이미 로드/언로드 연산이 진행 중인 씬에 대해서 또다시 로드/언로드 연산이 요청되는 경우를 처리해야 했습니다.

---

## "Alien" 프로젝트 <sup><i>2024년 3월~2024년 5월</i></sup>

* 팀 규모: 4명
* 직책: 팀장, 메인 프로그래머, 메인 기획자
* 목표: BIC 출품 위한 MVP 제작

---

## Unreal Labs

* 약 20명 규모의 Unreal 엔진 소스코드 분석 연구회
* `ActorComponent` 팀에서 해당 기능을 분석
* [발표자료](https://docs.google.com/presentation/d/19-R6U1GwiAnyQH91bM8MlbIXAxXcxeDGW7L3T93jJ6w/edit?usp=sharing)
* 연구 학생으로 참여