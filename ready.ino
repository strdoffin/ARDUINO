#include <ATX2.h>
#define ll analog(0)
#define lc analog(2)
#define rc analog(1)
#define rr analog(3)
#define bl analog(4)
#define br analog(5)
#define ref 636
#define ref2 697
#define _speed 35
#define _time 290
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

void pause(unsigned int time) { //ฟังก์ชันหยุดหุ่น
  ao();
  delay(time);
}

/*---------------------------------------------*/

void tr90(unsigned int speed, unsigned int time) {
  sr(speed);
  delay(time);
  pause(100);
}

/*---------------------------------------------*/

void tl90(unsigned int speed, unsigned int time) {
  sl(speed);
  delay(time);
  pause(100);
}

/*---------------------------------------------*/

void tr180(unsigned int speed, unsigned int time) {
  time = time * 2;
  sr(speed);
  delay(time);
  pause(100);
}

/*---------------------------------------------*/

void tl180(unsigned int speed, unsigned int time) {
  time = time * 2;
  sl(speed);
  delay(time);
  pause(100);
}

/*---------------------------------------------*/

void FF(unsigned int speed) { //เดินหน้าและ check ซ้ายขวาไม่ให้ชนขอบด้านข้าง
  motor(1, speed - 7);
  motor(2, speed);
  if (ll < ref) {
    sr(50); //ซ้ายเจอดำให้หมุนขวา
  }
  if (rr < ref) {
    sl(50); //ขวาเจอดำให้หมุนซ้าย
  }
}

/*---------------------------------------------*/

void Bset_balance() {   //ชนหลังแล้ว set หลังให้ตรง
  while (br > ref2) {
    motor(1, 0);
    motor(2, -60); //หลังซ้ายเจอดำให้ถอยขวาจนกว่าจะเจอดำ 2 ข้าง
  }
  pause(100);
  while (bl > ref2) {
    motor(1, -60);
    motor(2, 0); //หลังขวาเจอดำให้ถอยซ้ายจนกว่าจะเจอดำ 2 ข้าง
  }
  pause(10);
}

/*---------------------------------------------*/
//เฉพาะกิจ
void Fset_balance2() {  //ชนหน้าแล้ว set หน้าให้ตรง
  
  while (lc > ref && rc > ref) {
    fd(20);
  }
  pause(10);
  if (lc < ref || rc < ref) {
    while (rc > ref) {
      motor(1, 0);
      motor(2, 30); //ซ้ายเจอดำให้เลี้ยวขวาจนกว่าจะเจอดำ 2 ข้าง
    }
    pause(10);


    while (lc > ref) {
      motor(1, 30);
      motor(2, 0); //ขวาเจอดำให้เลี้ยวซ้ายจนกว่าจะเจอดำ 2 ข้าง
    }
    pause(10);

  }
}
void Fset_balance() {  //ชนหน้าแล้ว set หน้าให้ตรง
   pause(10);
  bk(60);
  delay(250);
  pause(100);
  while (lc > ref && rc > ref) {
    fd(20);
  }
  pause(10);
    while (rc > ref) {
      motor(1, 0);
      motor(2, 30); //ซ้ายเจอดำให้เลี้ยวขวาจนกว่าจะเจอดำ 2 ข้าง
    }
    pause(10);
  while (lc > ref) {
      motor(1, 30);
      motor(2, 0); //ขวาเจอดำให้เลี้ยวซ้ายจนกว่าจะเจอดำ 2 ข้าง
    }
    pause(10);
  }

/*---------------------------------------------*/

void FFBKL() {
  while (lc > ref && rc > ref) {
    FF(50);
  }
  pause(100);
  Fset_balance();
  bk(50);
  delay(130);
  pause(100);
  tl90(_speed, _time);
  while (bl > ref2 && br > ref2) {
    bk(20);
  }
  pause(100);
  Bset_balance();
}

/*---------------------------------------------*/

void FFBKR() {
  while (lc > ref && rc > ref) {
    FF(50);
  }
  pause(100);
  Fset_balance();
  bk(50);
  delay(130);
  pause(100);
  tr90(_speed, _time);
  while (bl > ref2 && br > ref2) {
    bk(20);
  }
  pause(100);
  Bset_balance();
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
  pause(200);
}

/*---------------------------------------------*/

void FFS() {
  while (lc > ref && rc > ref) {
    FF(60);
  }
  bk(60);
  delay(100);
  pause(100);
  servoDrop();
  pause(100);
}

/*---------------------------------------------*/

void back(unsigned int speed) {
  motor(1,-speed+7);
  motor(2,-speed);
}

/*---------------------------------------------*/

void FFRR(unsigned int speed,unsigned int time) {
  while (lc > ref && rc > ref) {
    FF(60);
  }
  if (lc < ref || rc < ref) {
    pause(100);
    Fset_balance();
  }
  if (lc < ref && rc < ref) {
    pause(600);
  }
  bk(60); //ถอยหลังแล้วหมุน
  delay(230);
  pause(100);
  tr90(speed, time+25);
  pause(100);
}
/**/
void FFLL(unsigned int speed,unsigned int time) {
  while (lc > ref && rc > ref) {
    FF(60);
  }
  if (lc < ref || rc < ref) {
    pause(100);
    Fset_balance();
  }
  if (lc < ref && rc < ref) {
    pause(600);
  }
  bk(60); //ถอยหลังแล้วหมุน
  delay(230);
  pause(100);
  tl90(speed, time+20);
  pause(100);
}
/**/
void FFRR2(){
  while (lc > ref && rc > ref) {
    FF(55);
  }
  if (lc < ref || rc < ref) {
    pause(100);
    Fset_balance();
  }
  if (lc < ref && rc < ref) {
    pause(600);
  }
  bk(60); //ถอยหลังแล้วหมุน
  delay(250);
  pause(100);
  tr90(_speed, _time-40);
  pause(100);
}
/*---------------------------------------------*/
void bridge(unsigned int time, unsigned int speed) {
  motor(1, -speed + 7);
  motor(2, -speed);
  delay(time);
  pause(10);
}

void setup() {
  XIO();
  servo(1, 90);
  delay(200);
  servo(1, -1);
  OK();
  delay(1000);
  FFRR(_speed,_time);
  FFBKR();
  FFBKR();
  FFBKL();
  FFS();
  
  back(60);
  delay(450);
  pause(10);
  tl90(_speed,_time);
  while(br>ref2 && bl>ref2){
    back(20);
  }
  pause(10);
  Bset_balance();
  pause(10);
  FFRR(_speed,_time);
  FFRR(_speed,_time);
  FFS();

  back(60);
  delay(200);
  pause(1000);
  tl180(_speed,_time);
  while(bl>ref2 && br>ref2){
    back(20);
  }
  pause(10);
  Bset_balance();
  pause(10);
  FFBKL();
  FF(60);
  delay(1150);
  pause(500);
  tl90(_speed,_time);
  pause(10);
  back(40);
  delay(400);
  pause(10);
  while(lc>ref && rc>ref){
    FF(20);
  }
  pause(10);
  Fset_balance2();
  bridge(1700,67);
  
  while(br>ref2 && bl>ref2){
    back(20);
  }
  pause(10);
  Bset_balance();
  pause(10);
  FF(20);
  delay(300);
  pause(500);
  tr90(_speed,_time);
  while(lc>ref && rc>ref){
    FF(60);
  }
  pause(200);
  back(60);
  delay(200);
  pause(200);
  tl90(_speed,_time);
  while(br>ref2 && bl>ref2){
    back(20);
  }
  Bset_balance();
  pause(10);
  FFS();
  
  while(br>ref2 && bl>ref2){
    back(20);
  }
  pause(10);
  Bset_balance();
  pause(10);
  FF(60);
  delay(150);
  pause(10);
  tl90(_speed,_time);
  while(bl>ref2 && br>ref2){
    back(20);
  }
  Bset_balance();
  FFS();
  
  Fset_balance();
  back(60);
  delay(800);
  pause(900);
  tl90(_speed,_time);
  pause(10);
  back(40);
  delay(400);
  pause(10);
  while(lc>ref && rc>ref){
    FF(20);
  }
  Fset_balance();
  bridge(1850,60);
  
  while(br>ref2 && bl>ref2){
    back(20);
  }
  Bset_balance();
  pause(10);
  FF(60);
  delay(200);
  pause(1000);
  tl90(_speed,_time);
  pause(100);
  FFBKL();
  FFBKL();
  FF(60);
  delay(1100);
  pause(1000);
  tr90(_speed,_time);
  FFRR(_speed,_time);
  FFBKR();
  FFBKL();
  FFBKL();
  FFBKL();
  FFS();
}

void loop() {
  //readsensor();
}
