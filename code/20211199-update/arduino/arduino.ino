#include <Thread.h>
#include <ThreadController.h>
#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial HC06(2,3);

ThreadController controll = ThreadController();
Thread thr1 = Thread();
Thread thr2 = Thread();

Stepper stepper(200, 8, 9, 10, 11);



int interval = 3;
int n_items = 10;
String str="";
char str1[50];
char buff[] = "HI";
boolean stopflag = true;

void recv_str(){
  while(HC06.available()){
  char data = HC06.read();
  str += data;
  }
  delay(5);
}

void recv_str_thread(){
  recv_str();
  char tempData[10];
 
  if(!str.equals("")){
  Serial.println(str);
  if(str == "STOP 0"){
    Serial.println("recv STOP 0");
    stopflag = true;
  }else if(str.indexOf("INTERVAL ",0) == 0){
    str.substring(9).toCharArray(tempData,4);
    if(isDigit(tempData[0]) == 1)
      interval = atoi(tempData);
    Serial.println(interval);
  }else if(str.indexOf("ITEMS ",0) == 0){
    str.substring(6).toCharArray(tempData,4);
    if(isDigit(tempData[0]) == 1)
      n_items = atoi(tempData);
    Serial.println(n_items);
  }else if(str == "START 0"){
    Serial.println("recv START 0");
    stopflag = false;
  }
  str="";
 }
}

void loop_thread(){
  int i = 0;
  double randnum;
  String randdata = "";
  if(stopflag)
    return
  randomSeed(analogRead(2));
  for(i = 0;i < n_items; i++){
    randnum = random(0,100)/(double)100;
    randdata+=randnum;
    if(i != n_items - 1)
      randdata+=",";
  }
  Serial.println(randdata);
  HC06.print(randdata);
  delay(5);
}


void setup() {
 Serial.begin(9600); //pc와 아두이노간 통신
 HC06.begin(9600);//아두이노와 블루투스 모듈간 통신
 thr1.onRun(recv_str_thread);
 thr1.setInterval(500);

 thr2.onRun(loop_thread);
 thr2.setInterval(interval * 1000);

 controll.add(&thr1);
 controll.add(&thr2);

 stepper.setSpeed(30);
}

void loop() {
//  recv_str();
//  if(thr1.shouldRun())
//    thr1.run();
//  if(thr2.shouldRun())
//    thr2.run();
  controll.run();
}
