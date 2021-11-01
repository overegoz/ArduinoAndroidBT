# ArduinoAndroidBT

## 환경구성
* 센서: Arduino UNO, Bluetooth module (BT)
* 앱: Android, App Inventor

## 센서부 연결
![Arduino-BT connection](/imgs/Arduino-BT-connection.JPG)
![BT module](/imgs/BT-module.JPG)

## 앱 사용
1. App Inventor 에서 코딩 <https://appinventor.mit.edu/>
  * 웹브라우저에서 블록 기반의 GUI 코딩
  * 구글 계정이 있어야 이용할 수 있음
2. 안드로이드 폰에서 Mit AI2 Companion 앱 다운로드
  * 웹에서 개발한 코드에 대한 QR 코드를 얻을 수 있는데, AI2 앱에서 해당 QR 코드를 스캔하면 안드로이드 폰에서 코드를 구동할 수 있음
  
## 해결할 문제들 또는 주의사항
* 그래프를 위한 외부 라이브러리를 사용하는데, 이를 위해 안드로이드 폰은 인터넷 연결이 되어 있어야 함
* 그래프를 표현하기 위해 별도의 html 파일을 사용하는데, 이는 App Inventor에서 연결/등록 해 줘야함
* 아두이노에서 send와 receive를 분리하기 위해 thread를 사용하는데, thread가 timer 기반으로 구현되었고, BT를 통한 송수신 중간에 thread가 trigger 되는 경우가 있어서 전체적인 동작을 방해함
  * 아두이노가 BT를 통해서 수신하는 데이터는 제어/control 메시지이고, 데이터 양이 많지 않아서, 굳이 thread를 사용하거나 할 필요 없음
  * 또한 thread로 인해서 sleep delay에 오차가 발생하고, 오차가 점점 누적된다.
  * Thread 없는 구현으로 바꾸고, 메인 loop에서 is_available 같은 메소드를 사용해서 BT 수신 데이터가 있는지를 확인하자  
* BT가 하나의 바이트 단위로 send/receive가 되는데, 이러면 send/receive 속도가 느려진다. 
  * BT의 send/receive 속도를 높일 수 있는 방법 찾아보기
* 아두이노 BT의 이름이 fireAlarm으로 설정되어 있는데, 이를 변경할 수 있는 방법을 찾아보자  
  