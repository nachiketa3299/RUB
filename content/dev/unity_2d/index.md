---
title: "2D 픽셀 게임을 만들 때 필요한 개념들"
categories: ["Unity"]

toc: true
date: 2025-03-03
---

# 유닛(Unit)

* 유니티 내부에서 사용하는 거리 단위로, **1 Unit은 1 m**라고 생각하면 된다.
* 1 유닛이라고도 부르고, 1 유니티 단위라고도 한다.

예를 들어, 자주 사용하는 `transform.position` 의 각 좌표값 역시 모두 1 유닛이 단위이다. 

# PPU(Pixel Per Unit)

* PPU란, 1 유닛에 들어가게 되는 픽셀의 수 
* 2D 게임을 제작할 때에는 **"하나의 유니티 단위에 몇 개의 픽셀이 들어가는가?"** 에 대한 정의가 필요한데, 이를 담당하는 것이 PPU이다.

## PPU를 고려하여 스프라이트 임포트하기

* 스프라이트 제작시 이 스프라이트가 가로로 몇 유닛, 세로로 몇 유닛을 차지하는지 생각하자.

2D 스프라이트 임포트 설정에서 PPU를 설정해 줄 수 있다.
예를 들어, 64x64 스프라이트가 있고, 이 스프라이트를 PPU 50으로 임포트 했다고 하자.

그러면 하나의 유닛에 50개의 픽셀이 들어가므로, 임포트한 2D 스프라이트의 유닛 크기는 (64/50)x(64/50)이 된다.

이 스프라이트가 1 유닛 내에 오롯이 들어가야 한다면, PPU를 64로 설정해 주면 된다.

> 제작중인 게임의 스프라이트에 일관된 PPU값을 적용하는 것은 매우 좋은 선택이다.

# Orthographic Size

* nxm 픽셀의 스프라이트를 임포트
* 임포트한 스프라이트를 PPU를 사용하여 유닛 단위로 바꾼 후, 유니티 월드에 배치

위 두 과정 이후, 최종 게임 화면을 렌더링 하려면 카메라에 대한 계산도 해주어야 한다.

2D 게임에서는 정사 카메라가 사용되며, 유니티 월드를 지정한 해상도의 게임 화면으로 출력하기 위해 Orthographic Size를 잘 설정해 주어야 한다.

* Orthographic Size는 카메라의 세로 반의 길이를 월드 유닛 기준으로 표현한 것
* 가로 너비는 세로 절반 길이와 화면비를 통해 자동으로 계산된다.

예를 들어, Orthographic Size를 3으로 두겠다는 것은, 최종 게임 해상도가 wxh라 하였을 때, h에 총 6 유닛만큼의 월드를 보여주겠다는 뜻이다.

# Pixel Perfect Camera

# 참고 문헌

* [\[일지\] Frostory 픽셀 퍼펙트 세팅/특수한발가락/인디게임 개발 마이너 갤러리](https://gall.dcinside.com/mgallery/board/view/?id=game_dev&no=55170)
* [Pixel Perfect Lights and Particles in Unity! (Tutorial)/Unity/YouTube](https://www.youtube.com/watch?v=2qeNu2QApAM)

