#include <ATX2.h>  // ATX2 Board
#define ll analog(1)  //ซ้ายสุด
#define lc analog(2)  //ซ้ายกลาง
#define rc analog(3)  //ขวากลาง
#define rr analog(4)  //ขวาสุด
#define bl analog(5)  //หลังซ้าย
#define br analog(6)  //หลังขวา
#define ref  560  //กำหนดค่ากลางค่าแสง
#define ref2 355.25
#define _speed 37
#define _time 365
#define _bspeed 37
#define _btime 365
/*---------------------------------------------*/
void readsensor(){  //ฟังก์ชันแสดงค่าจาก sensor 6 ตัว
  glcd(0,0,"%d   ",ll);
  glcd(0,5,"%d   ",lc);
  glcd(0,10,"%d   ",rc);
  glcd(0,15,"%d   ",rr);
  glcd(3,0,"%d   ",bl);
  glcd(3,10,"%d   ",br);
}
/*---------------------------------------------*/
void pause(unsigned int time){  //ฟังก์ชันหยุดหุ่น
  ao();
  delay(time);
}
/*----------------Set balance----------------*/
void Bset_balance(){    //ชนหลังแล้ว set หลังให้ตรง
    if(bl < ref2 && br > ref2){
          while (br > ref2) {
            motor(1,0);    
            motor(2,-60); //หลังซ้ายเจอดำให้ถอยขวาจนกว่าจะเจอดำ 2 ข้าง
    }
      pause(100);}
    if(bl > ref2 && br < ref2){
          while (bl > ref2) {
            motor(1,-60);        
            motor(2,0); //หลังขวาเจอดำให้ถอยซ้ายจนกว่าจะเจอดำ 2 ข้าง
    }
      pause(100);}
    }

/*---------------------------------------------*/

void Fset_balance(){   //ชนหน้าแล้ว set หน้าให้ตรง
    if(ll < ref && rr > ref){
          while (rr > ref) {
            motor(1,0);        
            motor(2,60);  //ซ้ายเจอดำให้เลี้ยวขวาจนกว่าจะเจอดำ 2 ข้าง
    }
      pause(100);}
    
    if(ll > ref && rr < ref){
          while (ll > ref) {
            motor(1,60);        
            motor(2,0);  //ขวาเจอดำให้เลี้ยวซ้ายจนกว่าจะเจอดำ 2 ข้าง
    }
    pause(100);}
    }
/*---------------------------------------------*/
void FF(unsigned int speed){  //เดินหน้าและ check ซ้ายขวาไม่ให้ชนขอบด้านข้าง
        fd(speed);
        if (ll<ref){sr(50);}    //ซ้ายเจอดำให้หมุนขวา
        if (rr<ref){sl(50);}    //ขวาเจอดำให้หมุนซ้าย
    }

/*---------------------------------------------*/
void FFBKL(){  //เดินหน้า ถ้าชน ถอยหลังเลี้ยวซ้าย
        while(lc > ref && rc > ref){FF(30);}
        pause(100);
        if(lc<ref || rc<ref || ll<ref || rr<ref){
          //pause(100);
          Fset_balance();
        }
        if(lc < ref && rc < ref){pause(600);}
        bk(50); //ถอยหลังแล้วหมุน
        delay(160);
        btr90(_bspeed,_btime);
        while(bl > ref2 && br > ref2){bk(15);}  //ถอยจนกว่าจะชน
        if(bl<ref2 || br<ref2){  //ถอยชนแล้ว set หลังให้ตรง
            pause(100);
            Bset_balance();
        }
        if(bl < ref2 && br < ref2){pause(500);}
}
/*---------------------------------------------*/
void FFBKR(){  //เดินหน้า ถ้าชน ถอยหลังเลี้ยวขวา
      while(lc > ref && rc > ref){FF(30);}
      pause(100);
      if(lc<ref || rc<ref ){
        //pause(100);
        Fset_balance();
      }
      if(lc < ref && rc < ref){pause(500);}
      bk(50); //ถอยหลังแล้วหมุน
      delay(160);
      btl90(_bspeed,_btime);
      while(bl > ref2 && br > ref2){  bk(15);}//ถอยจนกว่าจะชน
      if(bl<ref2 || br<ref2){  //ถอยชนแล้ว set หลังให้ตรง
        pause(100);
        Bset_balance();
      }
      if(bl < ref2 && br < ref2){pause(500);}
}
/*---------------------------------------------*/
void FFLrotate(){
  while(lc > ref && rc > ref){FF(60);}
  if(lc<ref || rc<ref){
    pause(100);
    Fset_balance();
  }
  if(lc < ref && rc < ref){pause(600);}
  bk(60); //ถอยหลังแล้วหมุน
  delay(300);
  ao();
  sl(50);
  delay(500);
  while(bl>ref2 && br>ref2){bk(60);}
  Bset_balance();
}
/*----------------turn------------------*/
void FFrotate(){  //เดินหน้า ถ้าชน กลับหลังหัน
    while(lc > ref && rc > ref){FF(60);}
    if(lc<ref || rc<ref){
    pause(100);
    Fset_balance();
    }
    if(lc < ref && rc < ref){pause(600);}
    bk(60); //ถอยหลังแล้วหมุน
    delay(300);
    ao();
    sr(50);
    delay(500);
    while(bl>ref2 && br>ref2){bk(60);}
    Bset_balance();
}
/*---------------------------------------------*/
void tr90(unsigned int speed,unsigned int time){
    sr(speed);
    delay(time);
    pause(100);
}

void btr90(unsigned int speed,unsigned int time){
    sr(speed);
    delay(time);
    pause(100);
}

/*---------------------------------------------*/
void tl90(unsigned int speed,unsigned int time){
    sl(speed);
    delay(time);
    pause(100);
}

void btl90(unsigned int speed,unsigned int time){
    sl(speed);
    delay(time);
    pause(100);
}

/*---------------------------------------------*/
void tr180(unsigned int speed,unsigned int time){
  time=time*2;
  sr(speed);
  delay(time);
  pause(100);
}
/*---------------------------------------------*/
void tl180(unsigned int speed,unsigned int time){
  time=time*2;
  sl(speed);
  delay(time);
  pause(100);
}
/*---------------------------------------------*/
void back(){
  while(br>ref2 && bl>ref2){bk(30);}
}
/*---------------------------------------------*/
void FFRR(){
    while(lc > ref && rc > ref){FF(30);}
    if(lc<ref || rc<ref){
      pause(100);
      Fset_balance();
     }
    if(lc < ref && rc < ref){pause(600);}
    bk(50); //ถอยหลังแล้วหมุน
    delay(200);
    pause(100);
    tr90(_speed,_time);
    pause(100);
}
/*---------------------------------------------*/
void FFLL(){
  while(lc > ref && rc > ref|| ll<ref || rr<ref){FF(30);}
  if(lc<ref || rc<ref){
    pause(100);
    Fset_balance();
  }
  if(lc < ref && rc < ref){pause(600);}
  bk(50); //ถอยหลังแล้วหมุน
  delay(200);
  pause(100);
  tl90(_speed,_time);
  pause(100);
}
/*---------------------------------------------*/
void FFR(){
  if(bl < ref2 && br > ref2){
      while (br > ref2) {
         motor(1,0);    
         motor(2,-60); //หลังซ้ายเจอดำให้ถอยขวาจนกว่าจะเจอดำ 2 ข้าง
   }
    pause(100);}
if(bl > ref2 && br < ref2){
      while (bl > ref2) {
         motor(1,-60);        
         motor(2,0); //หลังขวาเจอดำให้ถอยซ้ายจนกว่าจะเจอดำ 2 ข้าง
   }
    pause(100);}
}

/*---------------------------------------------*/
void servoDrop(){
  if(lc<ref && rc<ref){
    pause(100);
    servo(1,0);
    delay(200);
    servo(1,110);
    delay(100);
  }
  servo(1,-1);
  pause(200);
}
void FFS() {
  while(lc>ref && rc>ref){
    FF(60);
  }
  bk(60);
  delay(100);
  pause(100);
  servoDrop();
  pause(100);
  bk(60);
  delay(300);
  tr180(_speed,_time);
  back();
  Bset_balance();
}
/*------------------------------*/
void FFBridge(unsigned int speed,unsigned int time){
  bk(speed);
  delay(time);
  pause(100);
}
/**/
void FFSL() {
  while(lc>ref && rc>ref){
    FF(60);
  }
  bk(60);
  delay(100);
  pause(100);
  servoDrop();
  pause(100);
  bk(60);
  delay(300);
  tl180(_speed,_time);
  back();
  Bset_balance();
}
/*---------------------------------*/
void setup() {
  XIO();
  servo(1,90);
  delay(200);
  servo(1,-1);
  OK();
  delay(1000);
  
  //while(lc>ref && rc>ref){FF(20);} Fset_balance(); tr180(_speed,_time);
  //while(lc>ref && rc>ref){FF(20);} Fset_balance();
  //FFBridge(45,2300);
  
  back();
  Bset_balance();
  while(lc>ref && rc>ref){
    FF(60);
  }
  bk(60);
  delay(200);
  tr180(_speed,_time);
  back();
  Bset_balance();
  FF(60);
  delay(750);
  pause(100);
  tl90(_speed,_time);
  while(lc>ref && rc>ref){
    FF(60);
  }
  pause(100);
  Fset_balance();
  FFBridge(45,2300);
  back();
  Bset_balance();
  FF(60);
  delay(200);
  pause(100);
  tl90(_speed,_time);
  FFBKR();
  FFBKR();
  FFS();
  
  FFBKL();
  FFBKL();
  FFBKL();
  FFSL();
  
  FFBKR();
  FF(60);
  delay(770);
  pause(100);
  tl90(_speed,_time);
  back();
  Bset_balance();
  FF(60);
  delay(2200);
  pause(100);
  while(lc>ref && rc>ref){
    FF(60);
  }
  pause(100);
  tr90(_speed,_time);
  FFRR();
  FFBKL();
  while(lc>ref && rc>ref){
    FF(60);
  }
  pause(100);
  bk(60);
  delay(200);
  pause(100);
  tr180(_speed,_time);
  FFBKR();
  FFBKR();
  FFS();

  FFBKL();
  FF(60);
  delay(750);
  pause(100);
  tr90(_speed,_time);
  FF(60);
  delay(1000);
  pause(100);
  tl90(_speed,_time);
  back();
  Bset_balance();
  FF(60);
  delay(2000);
  pause(100);
  while(lc>ref && rc>ref){
    FF(60);
  }
  pause(100);
  tl90(_speed,_time);
  FF(60);
  delay(750);
  pause(100);
  tl90(_speed,_time);
  while(lc>ref && rc>ref){
    FF(60);
  }
  pause(100);
  Fset_balance();
  FFBridge(45,2500);
  back();
  Bset_balance();
  tl90(_speed,_time);
  while(lc>ref && rc>ref){
    FF(60);
  }
  pause(100);
  /* */
}

void loop() {
  //readsensor();
}
