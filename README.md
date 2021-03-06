### git commit 할 때 어떤 걸 변경했는 지 명시해주시면 감사하겠습니다.

### Compile in Ubuntu
g++ -I "SnakeFilePath" main.cpp -o output -lncurses

# Game Rule
1. 진행방향과 같은 반대 방향키를 입력하는 경우 실패. 방향키는 직접 정함.

2. Snake의 이동 방향에 Item이 놓여 있는 경우
- Snake가 Item을 획득
- Growth Item의 경우 -> 몸 길이 1 증가 -> 진행방향으로 증가
- Poison Item의 경우 -> 몸 길이 1 감소 -> 꼬리 부분이 감소 -> 몸 길이 3보다 작아지면 실패
2-1. Growth Item과 Poison Item의 출현
- Snake Body가 있지 않은 임의의 위치에 출현
- 출현 후 일정시간이 지나면 사라지고 다른 위치에 나타나야 함.
- 동시에 출현할 수 있는 Item의 수는 3개로 제한함.

3. Gate
- Gate는 두 개가 한 쌍
- Gate는 겹치지 않음.
- Gate는 임의의 위치에 있는 벽에서 나타남.
- Gate는 한번에 한쌍만 나타남.
- Gate에 Snake가 진입 시, 다른 Gate로 진출.
- Gate에 Snake가 진입 중인 경우: Gate는 사라지지 않음. 다른 위치에서 Gate가 나타나지 않음.

4. Gate 진출 방향
1) Gate가 나타나는 벽이 가장자리에 있을 때
- 항상 Map의 안쪽 방향으로 진출.
- 상단벽 -> 아래 방향, 하단벽 -> 위 방향, 좌측벽 -> 우측 방향, 우측벽 -> 좌측 방향
2) Gate가 나타나는 벽이 Map의 가운데 있을 때 다음 순서로 진출
- 진출 방향이 자유로운 경우: 진입 방향으로 진출
- 진출 방향이 좌우인 경우:
	* 우측 진입 시 -> 우로 진출
	* 아래로 진입 시 -> 좌로 진출
	* 좌측 진입 시 -> 좌로 진출
	* 위로 진입 시 -> 좌로 진출
- 진출 방향이 상하인 경우:
	* 우측 진입 시 -> 위로 진출
	* 위쪽으로 진입 시 -> 위로 진출
	* 좌측 진입 시 -> 아래로 진출
	* 아래로 진입 시 -> 아래로 진출

5. Wall과 Immune Wall
- Wall: Gate로 변할 수 있다.
- Immune Wall: Gate로 변할 수 없다.
- All Wall: Snake가 통과할 수 없다. Snake Head와 충돌 시 실패
- Gate의 출현 방법 결정: 게임 시작 후 일정 시간 후 출현 or 몸의 최대 길이 X 초과 시 출현

6. 점수 계산
- 게임 중 몸의 최대 길이 계산 -> 최종 뱀 길이 / 최대 뱀 길이
- 게임 중 획득한 Growth Item의 수
- 게임 중 획득한 Poison Item의 수
- 게임 중 Gate 사용 횟수
- 게임 시간 (Seconds로 계산)
- 게임 방법: 주어진 미션 달성하기
- 미션: 좌측의 각 점수 항목별(최대길이, Growth Item 획득 수, Poison Item 획득 수, Gate 사용 횟수, 게임 시간)로 목표치 도달 시 게임 종료

## CheckList
1. ~~Wall, ImmuneWall 생성~~
	* Wall이 게임판 중간에 생성됬는데 Snake 바로 앞에 생성되면 암살 가능.
2. ~~Gate 생성~~ -> ~~Wall 객체의 위치 중에서 두 곳을 골라 Wall 객체를 삭제시킨 이후, 그 자리에 Gate 객체 생성~~
3. ~~Item의 타이머 생성~~
4. Snake의 Gate 진입, 진출 방향 설정
5. Item의 최대 동시 생성 갯수 설정: 3
6. ~~항목별 점수 생성~~
7. ~~항목별 점수 계산~~
8. ~~ScoreBoard 항목별 목표치, 달성치~~
9. ~~Game Clear 조건 매끄럽게 처리~~

## Additional
1. Esc키를 누르면 User에게 확인 후 종료
2. p키를 눌러 게임 일시중지 시 일시중지임을 인지시켜줄 수 있는 장치 ex) ScoreBoard에서 "Pause" 메시지 출력
3. Game Level Up System -> Difficulty Growth
-> Game Speed 증가, Mission의 항목별 목표치 증가, 추가 벽의 생성 속도/시간 감소, Item의 유지 시간 감소 등
4. ~~Pause~~