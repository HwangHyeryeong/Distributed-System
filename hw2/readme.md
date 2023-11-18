### 과제 수행일: 2023년 4월 16일

### Key-Value Store Client-Server 프로그램 구현하기
간단한 KVS를 구현하여 분산 데이터베이스 상에서 사용되는 KVS의 read, write 연산의 기본 개념 구현했습니다.
(wsl의 한계로 파티셔닝은 생략함)

### 요구사항
#### 1. 만약 명령어가 get이라면:
  A. Key-value store를 key를 가지고 lookup(참조)합니다. <br>
  B. 만약 key가 존재한다면, 해당 key에 대한 value를 클라이언트에게 보냅니다.<br>
  C. 만약 key가 존재하지 않는다면, “Key not found” 메시지를 클라이언트에게 보냅니다. <br>
#### 2. 만약 명령어가 put이라면:
  A. Key-value store에 해당 key와 value를 추가/수정 합니다. <br>
  B. 클라이언트에게 “OK”를 회신합니다. <br>
#### 3. 만약 명령어가 get 혹은 put이 아니라면:
  A. 클라이언트에게 “Invalid command”를 회신합니다. <br>
#### 4. Get 명령어의 경우 get x의 형태가 아니라면 Invalid command를 클라이언트에게 회신합니다.
   예를 들어 그냥 get만 보냈다던가 get 3 3처럼 put의 형태로 보냈다던가.. 무조건 get x만 허용합니다. <br>
#### 5. Put 명령어의 경우 put x y의형태가 아니라면 Invalid command를 클라이언트에게 회신합니다.
   예를 들어 그냥 put만 보내거나 put x만 보냈거나, put x y z를 보내면 Invalid command를 회신합니다. <br>
   
### 결과물
#### 클라이언트
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/51671687-f08d-4e3e-8891-3acbd6a8625c)

#### 서버
![image](https://github.com/HwangHyeryeong/Distributed-System/assets/75305711/9fba77fb-dc33-4c2a-af1f-140f734c2ca2)
