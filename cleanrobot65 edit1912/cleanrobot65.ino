#include <ATX2.h>	// ATX2 Board
#define ll analog(1)  //ซ้ายสุด
#define lc analog(2)  //ซ้ายกลาง
#define rc analog(3)  //ขวากลาง
#define rr analog(4)  //ขวาสุด
#define bl analog(5)  //หลังซ้าย
#define br analog(6)  //หลังขวา
#define ref 600   //กำหนดค่ากลางค่าแสง
#define ref2 560

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
            motor(1,10);    
            motor(2,-60); //หลังซ้ายเจอดำให้ถอยขวาจนกว่าจะเจอดำ 2 ข้าง
    }
      pause(100);}
    if(bl > ref2 && br < ref2){
          while (bl > ref2) {
            motor(1,-60);        
            motor(2,10); //หลังขวาเจอดำให้ถอยซ้ายจนกว่าจะเจอดำ 2 ข้าง
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
void FF(){  //เดินหน้าและ check ซ้ายขวาไม่ให้ชนขอบด้านข้าง
        fd(60);
        if (ll<ref){sr(50);}    //ซ้ายเจอดำให้หมุนขวา
        if (rr<ref){sl(50);}    //ขวาเจอดำให้หมุนซ้าย
    }
    
/*---------------------------------------------*/
void FFBKL(){  //เดินหน้า ถ้าชน ถอยหลังเลี้ยวซ้าย
        while(lc > ref && rc > ref){ FF(); }
        if(lc<ref || rc<ref){
          pause(100);
          Fset_balance();
        }
        if(lc < ref && rc < ref){pause(600);}
        bk(60); //ถอยหลังแล้วหมุน
        delay(200);
        tr90();
        while(bl > ref2 && br > ref2){bk(30);}  //ถอยจนกว่าจะชน
        if(bl<ref2 || br<ref2){  //ถอยชนแล้ว set หลังให้ตรง
            pause(100);
            Bset_balance();
        }
        if(bl < ref2 && br < ref2){pause(500);}
}
/*---------------------------------------------*/
void FFBKR(){  //เดินหน้า ถ้าชน ถอยหลังเลี้ยวขวา
      while(lc > ref && rc > ref){FF();}
      if(lc<ref || rc<ref){
        pause(100);
        Fset_balance();
      }
      if(lc < ref && rc < ref){pause(500);}
      bk(50); //ถอยหลังแล้วหมุน
      delay(300);
      tl90();
      while(bl > ref2 && br > ref2){  bk(30);}//ถอยจนกว่าจะชน
      if(bl<ref2 || br<ref2){  //ถอยชนแล้ว set หลังให้ตรง
        pause(100);
        Bset_balance();
      }
      if(bl < ref2 && br < ref2){pause(500);}
}

    
/*---------------------------------------------*/

void FFLrotate(){
  while(lc > ref && rc > ref){FF();}
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
    while(lc > ref && rc > ref){FF();}
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

void tr90(){
    sr(57);
    delay(252);
    pause(100);
}
void tl90(){
    sl(57);
    delay(252);
    pause(100);
}
void back(){
  while(br>ref2 && bl>ref2){bk(30);}
}
/*---------------------------------------------*/
void FFRR(){
    while(lc > ref && rc > ref){FF();}
    if(lc<ref || rc<ref){
      pause(100);
      Fset_balance();
     }
    if(lc < ref && rc < ref){pause(600);}
    bk(60); //ถอยหลังแล้วหมุน
    delay(300);
    tr90();
    pause(100);
}

void FFLL(){
  while(lc > ref && rc > ref){FF();}
  if(lc<ref || rc<ref){
    pause(100);
    Fset_balance();
  }
  if(lc < ref && rc < ref){pause(600);}
  bk(60); //ถอยหลังแล้วหมุน
  delay(300);
  tl90();
  pause(100);
}
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
    servo(1,10);
    delay(200);
    servo(1,90);
    delay(100);
  }
  servo(1,-1);
  tr90();
  tr90();
}

void setup() {
  XIO();
  servo(1,90);
  delay(200);
  servo(1,-1);
  OK();
  delay(1000);
  while(lc>ref && rc>ref){
    FF();
  }
  pause(100);
  servoDrop();
  
}

void loop() {
  //readsensor();
}
