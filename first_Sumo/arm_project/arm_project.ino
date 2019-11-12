#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int a0[256];
int minA0=1000;
int maxA0=0;
int a1[256];
int minA1=1000;
int maxA1=0;
int v0=0;
int v1=0;
int v2=0;
int v3=0;
void m1(){
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
}
void m2(){
  servo1.write(180);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);
  servo5.write(180);
}
void m3(){
  servo1.write(0);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);
  servo5.write(180);
}void m4(){
  servo1.write(180);
  servo2.write(0);
  servo3.write(180);
  servo4.write(180);
  servo5.write(180);
}void m5(){
  servo1.write(180);
  servo2.write(0);
  servo3.write(0);
  servo4.write(180);
  servo5.write(180);
}void m6(){
  servo1.write(0);
  servo2.write(0);
  servo3.write(180);
  servo4.write(180);
  servo5.write(180);
}void m7(){
  servo1.write(0);
  servo2.write(0);
  servo3.write(180);
  servo4.write(180);
  servo5.write(180);
}void m8(){
  servo1.write(0);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);
  servo5.write(180);
}void m9(){
  servo1.write(0);
  servo2.write(180);
  servo3.write(180);
  servo4.write(180);
  servo5.write(0);
}void m10(){
  servo1.write(180);
  servo2.write(0);
  servo3.write(0);
  servo4.write(180);
  servo5.write(0);
}
void setup() {
  Serial.begin(115200);
  servo1.attach(10);
  servo2.attach(9);
  servo3.attach(6);
  servo4.attach(5);
  servo5.attach(3);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
}

void loop() {
  minA0=1000;
  maxA0=0;
  minA1=1000;
  maxA1=0;
  //Serial.write("A0");
  //Serial.write(map(analogRead(A0),0,1023,0,1000));
  //Serial.write("A1");
  //Serial.write(map(analogRead(A1),0,1023,0,1000));
  //delay(3);
  for(int i=0;i<256;i++){
    a0[i]=map(analogRead(A0),0,1023,0,500);
    a1[i]=map(analogRead(A1),0,1023,0,500);
  }
  for(int i=0;i<256;i++){
    if(minA0>a0[i]){
      minA0=a0[i];
    }
    if(maxA0<a0[i]){
      maxA0=a0[i];
    }
    if(minA1>a1[i]){
      minA1=a1[i];
    }
    if(maxA1<a1[i]){
      maxA1=a1[i];
    }
  }
  v0=maxA0-minA0;
  v1=maxA1-minA1;
  delay(500);
  minA0=1000;
  maxA0=0;
  minA1=1000;
  maxA1=0;
  //Serial.write("A0");
  //Serial.write(map(analogRead(A0),0,1023,0,1000));
  //Serial.write("A1");
  //Serial.write(map(analogRead(A1),0,1023,0,1000));
  //delay(3);
  for(int i=0;i<256;i++){
    a0[i]=map(analogRead(A0),0,1023,0,500);
    a1[i]=map(analogRead(A1),0,1023,0,500);
  }
  for(int i=0;i<256;i++){
    if(minA0>a0[i]){
      minA0=a0[i];
    }
    if(maxA0<a0[i]){
      maxA0=a0[i];
    }
    if(minA1>a1[i]){
      minA1=a1[i];
    }
    if(maxA1<a1[i]){
      maxA1=a1[i];
    }
  }
  v2=maxA0-minA0;
  v3=maxA1-minA1;
  delay(500);

  if((v0>150)and(v1<150)and(v2<150)and(v3<150)){
    m1();
  }
  if((v0<150)and(v1>150)and(v2<150)and(v3<150)){
    m2();
  }
  if((v0>150)and(v1>150)and(v2>150)and(v3>150)){
    m3();
  }if((v0>150)and(v1>150)and(v2>150)and(v3<150)){
    m4();
  }if((v0>150)and(v1<150)and(v2<150)and(v3>150)){
    m5();
  }if((v0>150)and(v1>150)and(v2<150)and(v3>150)){
    m6();
  }if((v0<150)and(v1>150)and(v2>150)and(v3>150)){
    m7();
  }if((v0>150)and(v1<150)and(v2>150)and(v3<150)){
    m8();
  }if((v0>150)and(v1<150)and(v2>150)and(v3<150)){
    m9();
  }if((v0>150)and(v1<150)and(v2<150)and(v3>150)){
    m10();
  }
}


