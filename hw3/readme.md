### 과제 수행일: 2023년 5월 7일

### Primary-Backup (PB) replication protocol을 사용하는 key-value store 기반 replicated storage 구현하기
PB 프로토콜을 직접 구현하여 Replication 이해하기

### 요구사항
#### 1. server.c를 적절히 수정해서 leader와 follower 역할을 수행할 수 있는 서버프로그램을 작성하세요.
  A. 실행시 인자를 입력해서 leader와 follower 역할을 구분할 수 있습니다. 1이면 leader, 0이면 follower <br>
  B. Leader는 get 명령어를 받으면 해당하는 값을 client에게 reply로 return합니다. <br>
  C. Leader는 put 명령어를 받으면 다른 follower들에게 이를 전파합니다. <br>
  D. Follower는 leader로부터 put 명령어를 받으면 값을 갱신 후 leader에게 ack을 회신합니다. <br>
  E. Leader는 모든 Follower들로부터 ack을 회신하였다면, client에게 reply를 보내 commit합니다. <br>

### 결과물
#### client
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/c2cf5168-0766-48cf-955b-323bff6224f9)

#### leader
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/1fedee2a-dfa3-464e-8fac-ebfc5f37699c)

#### follower1
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/f249fa77-14e3-4986-8016-b0a7cff61b39)

#### follower2
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/207c1709-e58f-476a-ad55-8117629f51d5)
