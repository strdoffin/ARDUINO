//battery 6.0
#include <ATX2.h>
#define ll analog(0)
#define lc analog(2)
#define rc analog(1)
#define rr analog(3)
#define bl analog(4)
#define br analog(5)
#define ref 245
#define ref2 250
#define fspeed 100
/*---------------------------------------------*/
void pause(unsigned int time) {
  AO();
  delay(time);
}

/*---------------------------------------------*/
void readsensor() { //ฟังก์ชันแสดงค่าจาก sensor 6 ตัว
  glcd(5, 0, "%d   ", ll);
  glcd(5, 5, "%d   ", lc);
  glcd(5, 10, "%d   ", rc);
  glcd(5, 15, "%d   ", rr);
  glcd(8, 0, "%d   ", bl);
  glcd(8, 10, "%d   ", br);
}
/*---------------------------------------------*/
void FF(unsigned int speed) {
  motor(1, speed - 7);
  motor(2, speed - 7);
  motor(3, speed);
  motor(4, speed);
  if (ll < ref) {
    SR(50); //ซ้ายเจอดำให้หมุนขวา
  }
  if (rr < ref) {
    SL(50); //ขวาเจอดำให้หมุนซ้าย
  }
}
/*---------------------------------------------*/
void tl90() {
  SL(100);
  delay(360);
  pause(10);
}
/*---------------------------------------------*/
void tr90() {
  SR(100);
  delay(360);
  pause(10);
}
/*---------------------------------------------*/
void FFR(unsigned int speed) {
  while (lc > ref and rc > ref) {
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
void FFL(unsigned int speed) {
  while (lc > ref and rc > ref) {
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
  
    pause(100);
    servo(1, 0);
    delay(300);
    servo(1, 110);
    delay(200);
  
  servo(1, -1);
  pause(10);
}
/*---------------------------------------------*/

void Bset_balance() {   //ชนหลังแล้ว set หลังให้ตรง
  while (br > ref2 and bl > ref2) {
    BK(60);
  }
  pause(200);
  while (br > ref2) {
    motor(1, 0);
    motor(2, 0);
    motor(3, -60);
    motor(4, -60); //หลังซ้ายเจอดำให้ถอยขวาจนกว่าจะเจอดำ 2 ข้าง
  }
  pause(200);
  while (bl > ref2) {
    motor(1, -60);
    motor(2, -60); //หลังขวาเจอดำให้ถอยซ้ายจนกว่าจะเจอดำ 2 ข้าง
    motor(3, 0);
    motor(4, 0);
  }
  pause(200);
}

void FFS(unsigned int speed) {
  while (lc > ref and rc > ref) {
    FF(100);
  }
  pause(100);
  servoDrop();
  pause(100);
}

void first_1() {
  FF(fspeed);
  delay(300);
  pause(10);
  FFR(fspeed);
  FFR(fspeed);
  FFR(fspeed);
  while(lc>ref and rc>ref){
    FF(fspeed);
  }
  pause(10);
  BK(100);
  delay(200);
  pause(10);
  tl90();
  Bset_balance();
  FFS(fspeed);
}
void second_2() {
  BK(100);
  delay(400);
  pause(10);
  tl90();
  Bset_balance();
  FFR(fspeed);
  FFR(fspeed);
  FFS(fspeed);
}
void third_3() {
  while (bl > ref2 and br > ref2) {
    BK(100);
  }
  pause(10);
  FF(fspeed);
  delay(70);
  pause(10);
  tr90();
  FF(fspeed);
  delay(100);
  pause(10);
  FF(fspeed);
  delay(950);
  pause(10);
  tr90();
  Bset_balance(); 
  FF(fspeed);
  delay(1200);//bridge 1
  pause(10);
  FFL(fspeed);
  
  while (lc > ref and rc > ref) {
    FF(fspeed);
  }
  pause(10);

  BK(60);
  delay(200);

  pause(10);

  tl90();
  pause(10);
  
  FFS(fspeed);
}


void forth(){
  while(bl>ref2 and br>ref2){
    BK(100);
  }
  pause(10);
  FF(fspeed);
  delay(100);
  pause(10);
  tl90();
  FFS(fspeed);
  
}

void fifth(){ //yellow 1
  BK(100);
  delay(300);
  pause(10);
  tr90();
  Bset_balance();
  while(lc>ref and rc>ref){
    FF(60);
  }
  pause(10);
}

void sixth(){
  while(bl>ref2 and br>ref2){
    BK(60);
  }
  pause(10);
  FF(fspeed);
  delay(150);
  pause(10);
  tr90();
  FF(fspeed);
  delay(550);
  pause(100);
  tl90();
  Bset_balance();

  FF(fspeed);
  delay(950); //bridge back
  pause(10);
}

void seventh(){ //yellow 2
  while (lc > ref and rc > ref) {
    FF(fspeed);
  }
  pause(10);

  BK(60);
  delay(100);

  pause(10);

  tl90();
  pause(10);
  
  FF(fspeed);
  delay(435);
  pause(10);
  tr90();
  Bset_balance();
  FF(fspeed);
  delay(950);
  pause(10);
  tr90();
  
  while(br>ref2 and bl>ref2){
    BK(60);
  }
  
  pause(10);
  tr90();
  while(br>ref2 and bl>ref2){
    BK(60);
  }
  pause(10);
}

void eighth(){
  FFL(fspeed);
  
  FF(fspeed);
  delay(700);
  pause(10);

  BK(60);
  delay(200);

  pause(10);

  tl90();
  pause(10);
  
  FFR(fspeed);
  FFR(fspeed);
  FFL(fspeed);
  FFL(fspeed);
  FFL(fspeed);
  while(lc>ref and rc>ref){
    FF(fspeed);
  }
  pause(10);
}
/*---------------------------------------------*/
void setup() {
  XIO();
  servo(1, 90);
  delay(200);
  servo(1, -1);
  OK();
  first_1();

  second_2();

  third_3();

  forth();

  fifth();

  sixth();
  
  seventh();

  eighth();
}

void loop() {
  readsensor();
}
