#include <ATX2.h>
#define ll analog(0)
#define lc analog(2)
#define rc analog(1)
#define rr analog(3)
#define bl analog(4)
#define br analog(5)
#define ref (370+100)/2
#define ref2 (450+100)/2
#define fspeed 100
/*---------------------------------------------*/
void pause(unsigned int time){
  AO();
  delay(time);
}

/*---------------------------------------------*/
void readsensor() { //ฟังก์ชันแสดงค่าจาก sensor 6 ตัว
  glcd(0, 0, "%d   ", ll);
  glcd(0, 5, "%d   ", lc);
  glcd(0, 10, "%d   ", rc);
  glcd(0, 15, "%d   ", rr);
  glcd(3, 0, "%d   ", bl);
  glcd(3, 10, "%d   ", br);
}
/*---------------------------------------------*/
void FF(unsigned int speed){
  motor(1,speed-7);
  motor(2,speed-7);
  motor(3,speed);
  motor(4,speed);
  if (ll < ref) {
    SR(50); //ซ้ายเจอดำให้หมุนขวา
  }
  if (rr < ref) {
    SL(50); //ขวาเจอดำให้หมุนซ้าย
  }
}
/*---------------------------------------------*/
void tl90(){
  SL(100);
  delay(360);
  pause(10);
}
/*---------------------------------------------*/
void tr90(){
  SR(100);
  delay(360);
  pause(10);
}
/*---------------------------------------------*/
void FFR(unsigned int speed){
  while(lc>ref and rc>ref){
    FF(speed);
  }
  pause(10);
  
  BK(60);
  delay(200);
  
  pause(10);
  
  tr90();
  pause(10);
}
/*---------------------------------------------*/
void FFL(unsigned int speed){
  while(lc>ref and rc>ref){
    FF(speed);
  }
  pause(10);
  
  BK(60);
  delay(200);
  
  pause(10);
  
  tl90();
  pause(10);
}
/*---------------------------------------------*/

void servoDrop() {//Drop Payload
  if (lc < ref && rc < ref) {
    pause(100);
    servo(1, 0);
    delay(200);
    servo(1, 110);
    delay(100);
  }
  servo(1, -1);
  pause(10);
}
/*---------------------------------------------*/

void FFS(unsigned int speed){
  while(lc >ref and rc>ref){
    FF(100);
  }
  pause(10);
  servoDrop();
  pause(10);
}
/*---------------------------------------------*/
void setup() {
  XIO();
  servo(1, 90);
  delay(200);
  servo(1, -1);
  OK();

  FFR(fspeed);
  FFR(fspeed);
  FFR(fspeed);
  FFL(fspeed);
  FFS(fspeed);
  
  BK(100);
  delay(300);
  pause(10);
  tl90();
  FFR(fspeed);
  FFR(fspeed);
  FFS(fspeed);
  
  while(bl >ref2 and br> ref2){
    BK(100);
  }
  pause(10);
  FF(fspeed);
  delay(200);
  tr90();
  FF(fspeed);
  delay(1000);
  tr90();
  
  FF(fspeed);
  delay(800);
  
  pause(10);
  FFR(fspeed);
  FFS(fspeed);

  BK(100);
  delay(300);
  pause(10);
  tr90();
  while(lc>ref and rc>ref){
    FF(fspeed);
  }
  pause(10);
  while(bl>ref2 and br>ref2){
    BK(100);
  }
  pause(10);
  FF(fspeed);
  delay(100);
  pause(10);
  tr90();
  FFL(fspeed);
  FFS(fspeed);
  
  while(br>ref2 and bl>ref2){
    BK(100);
  }
  pause(10);
  FF(fspeed);
  delay(100);
  pause(10);
  tl90();
  FF(fspeed);
  delay(300);
  pause(10);
  tr90();
  
  FF(fspeed);
  delay(800);
  
  FFR(fspeed);
  
  FFL(fspeed);
  FFL(fspeed);
  FFR(fspeed);
  while(lc>ref and rc>ref){
    FF(fspeed);
  }
  pause(10);
  while(bl>ref2 and br>ref2){
    BK(100);
  }
  pause(10);
  FF(fspeed);
  delay(100);
  pause(10);
  tr90();
  FF(fspeed);
  delay(300);
  pause(10);
  tl90();
  FFR(fspeed);
  FFR(fspeed);
  FFL(fspeed);
  FFL(fspeed);
  FFL(fspeed);
  while(lc>ref and rc>ref){
    FF(100);
  }
  pause(10);
  
}

void loop() {
  //readsensor();
}
