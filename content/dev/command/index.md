---
title: "[디자인 패턴] 명령 패턴"
toc: true
date: 2025-04-24
lastmod: 2025-04-24
---

# 유니티에서의 커맨드 패턴

일련의 **특정 행동**을 *추적*하려는 경우에 유용하다.

실행 취소/다시 실행 기능이 사용되거나, 입력의 내역이 목록으로 유지되는 게임을 플레이해본 적 있따면, 아마 커맨드 패턴을 사용하고 있을 확률이 높다.

메서드를 직접 호출하는 대신, 커맨드 패턴을 사용하면 "커맨드 오브젝트"라는 하나 이상의 메서드 호출을 캡슐화 할 수 있다.

커맨드 오브젝트를 대기열이나 스택과 같은 컬렉션에 저장하면, 오브젝트의 실행 타이밍을 제어할 수 있다. 이 저장된 일련의 행동을 나중에 재생할 수 있도록, 잠재적으로 지연하거나 실행을 취소할 수 있다.

커맨드 패턴을 구현하려면 행동을 포함한 일반 오브젝트, 즉 커맨드 오브젝트가 필요하다. 이 커맨드 오브젝트에는 로직을 수행할 작업과, 해당 작업을 실행 취소하는 방법이 포함된다.

```csharp
public interface ICommand
{
  void Execute();
  void Undo();
}
```

모든 게임플레이 행동이 `ICommand` 인터페이스를 구현한다고 가정한다. (사실, 추상 클래스로도 가능하다.)

각 커맨드 오브젝트는 자체의 `Execute`와 `Undo` 메서드를 처리한다.
==따라서, 게임에 더 많은 커맨드를 추가해도 기존의 커맨드에는 아무런 영향을 끼치지 않는다.==

커맨드를 실행 및 취소하려면 다른 클래스가 필요한데, `CommandInvoker` 클래스이다.

```csharp
public class CommandInvoker
{
  static Stack<ICommand> _undoStack = new();

  public static void ExecuteCommand(ICommand command)
  {
    command.Execute();
    undoStack.Push(command);
  }

  public static void UndoCommand()
  {
    if (undoStack.Count <= 0)
    {
      return;
    }

    ICommand activeCommand = undoStack.Pop();
    activeCommand.Undo();
  }
}
```

플레이어를 애플리케이션의 미로 안에서 이동하도록 구현하는 경우를 예로 들어보자.

플레이어의 위치 이동을 처리하는 `PlayerMover`를 작성한다.

```csharp
public class PlayerMover : MonoBehaviour
{
  [SerializeField] LayerMask _obstacleLayer;

  const float _boardSpacing = 1f;

  public void Move(Vector3 movement)
  {
    transform.position += movement;
  }

  public bool IsValidMove(Vector3 movement)
  {
    return !Physics.Raycast
    (
      transform.position, movement,
      _boardSpacing, _obstacleLayer
    );
  }
}
```

여기에 커맨드 패턴을 적용해 보자. `PlayerMover`의 `Move` 메서드를 오브젝트로 캡처한다. `Move`를 직접 호출하는 대신, `ICommand` 인터페이스를 구현하는 새 클래스 `MoveCommand`를 만든다.

```csharp
public class MoveCommand : ICommand
{
  PlayerMover _playerMover;
  Vector3 _movement;

  public MoveCommand(PlayerMover player, Vector3 moveVector)
  {
    _playerMover = player;
    _movement = moveVector;
  }

  public void Execute()
  {
    _playerMover.Move(movement);
  }

  public void Undo()
  {
    _playerMover.Move(-movement);
  }
}
```

`Execute`는 구현하려는 로직을 저장한다.

`MoveCommand`가 실행하려는 모든 파라미터를 저장하는 것을 눈여겨 본다. 생성자를 통해 해당 정보를 받고 있다.

커맨드 오브젝트를 만들고 필요한 파라미터를 저장하면, `CommandInvoker`의 정적 `ExecuteCommand`및 `UndoCommand` 메서드가 `MoveCommand`에 전달된다. 

그러면 `MoveCommand`의 `Execute` 또는 `Undo`가 실행되면서, 실행 취소 스택에서 커멘드 오브젝트가 추적된다.

{{<puml>}}
@startuml
hide empty member
title "Command Pattern"

interface ICommand {
  + Execute()
  + Undo()
}

class MoveCommand implements ICommand {
  - _playerMover
  - _movement
}

class CommandInvoker {
  - _undoStack
  + ExecuteCommand()
  + UndoCommand()
}

class InputManager {
  - _forwardButton
  + RunPlayerCommand()
  + OnUndoInput()
}

class PlayerMover {
  - _obstacleLayer
  + Move()
}

InputManager -d-> PlayerMover
InputManager -r-> CommandInvoker
CommandInvoker -r-> ICommand
MoveCommand -d-> PlayerMover


@enduml
{{</puml>}}

입력을 받는 부분의 `RunPlayerCommand`에서는 다음과 같은 일이 발생한다.

```csharp
private void RunPlayerCommand(PlayerMover playerMover, Vector3 movement)
{
  if (playerMover == null)
  {
    return;
  }

  if (playerMover.IsValidMove(movement))
  {
    ICommand command = new MoveCommand(playerMover, movement);
    CommandInvoker.ExecuteCommand(command);
  }
}
```

## 장점과 단점

- 다시 실행 또는 실행 취소 기능을 여러 커맨드 오브젝트를 생성하듯, 간단히 구현할 수 있다.
- 커맨드 버퍼를 사용하면, 특정한 컨트롤로 행동 시퀀스를 재생할 수도 있다.
- 특정 버튼을 순서에 맞게 클릭하면 콤보 기술이나 공격이 트리거되는 격투 게임을 구현할 수도 있다. (콤보를 훨씬 간편하게 설정할 수 있다.)
- 다른 디자인 패턴과 마찬가지로, 더 많은 구조를 유발한다. 추가 클래스와 인터페이스가 애플리케이션에 커맨드 오브젝트를 배포하는 데에 충분한 이점을 제공하는 위치를 파악하여 결정해야 한다.

## 응용

- 커맨드를 엄청 많이 만들 수 있다. 그래야 커맨드 패턴의 진가.
- 스택을 하나 더 유지하면, 다시 실행 기능을 추가할 수도 있다.
- 커멘드 오브젝트 버퍼의 구조에 따라 행동을 바꿀 수 있다.
- 스택 크기를 제한할 수도 있다.
- 필요 파라미터는 생성자로 전달한다.

`CommandInvoker`는 커맨드 오브젝트의 내부 작업을 보지 않고 오직 `Execute`와 `Undo`만 호출한다. 생성자 호출할 때에만 전달한다.

