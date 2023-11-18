### 과제 수행일: 2023년 3월 21일

### Consensus protocol 구현하기
Concensus, Byzantine faults를 이해하기 위해 간단한 Consensus 기반의 시스템 프로토콜을 구현했습니다.

### 요구사항
#### 이번 과제에서는 put은 사용하지 않습니다. get만 사용한다고 가정합니다. <br>
#### A. 클라이언트가 get 명령어를 수행하면 해당 요청은 모든 서버에 전송됩니다. <br>
#### B. 각 서버는 get 명령어를 받으면 클라이언트에 답신을 보냅니다. <br>
#### C. 우리는 총 3개의 서버를 고려합니다. 이 때 1개의 서버는 key 값이 무엇이든 간에 1을 return합니다. <br>
- 실제로는 그렇지 않지만, 단순화 시킨 것입니다. 즉, get함수를 쓸 필요가 없습니다. <br>
#### D. 남은 2개의 서버들은 랜덤으로 1~3 사이(즉 1 or 2 or 3)의 값을 return합니다. <br>
#### E. 클라이언트는 도착한 메시지를 수합해서 2개 이상의 서버가 동일한 값을 return 했는지 여부를 출력합니다. <Br>
- 2개 이상의 서버가 동일한 값을 return했으면 TRUE, 아니면 FALSE를 출력합니다. <br>
### 결과물
#### 클라이언트
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/de55a332-c7d0-4c3a-96fe-1c58a286a040)

#### 서버1
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/075de752-dd3c-4716-b4a8-0b8a508a3231)

#### 서버2
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/7dda4a70-3b73-4739-870d-f59efd9762d5)

#### 서버3
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/3ff4dfe7-c0d6-4a09-91f0-24c2c4e608cd)
