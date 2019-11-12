#include "Ultrasonic.h"

Ultrasonic Ultrasonic_Straight (11, 12); // Trig - first, Echo - second
Ultrasonic Ultrasonic_Right    (9, 10);
Ultrasonic Ultrasonic_Left     (7, 8);

 #include<Servo.h>//подключаем билиотеку для управления сервоприводами
Servo servo1;
Servo servo2;

unsigned long time;

void setup()
{
//*********************************************Перемычка

pinMode(A2, OUTPUT);

//********************************************Кнопка STOP

pinMode(13, OUTPUT);

//*****************************************************
  
  Serial.begin(9600);           // start the serial port
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  servo1.attach(A3);
  servo2.attach(A4);
   servo1.write(95);
   servo2.write(96.5);
}
void loop()
{

  float u_r = Ultrasonic_Right.Ranging(CM);     // get distance
  float u_s = Ultrasonic_Straight.Ranging(CM);     // get distance
  float u_l = Ultrasonic_Left.Ranging(CM);     // get distance
  
  Serial.print    ("Ultrasonic_Right:");
  Serial.print    (u_r);
  Serial.print    ("     ");
  Serial.print    ("Ultrasonic_Straight:");
  Serial.print    (u_s);
  Serial.print    ("     ");
  Serial.print    ("Ultrasonic_Left:");
  Serial.println  (u_l);        // print the distance


if  (u_s < 10) 
{
   servo1.write(95);
   servo2.write(96.5);
   
   digitalWrite(4, HIGH);
}
else
{
    servo1.write(-360);
    servo2.write(360);
  
    digitalWrite(4, LOW);
}
//*******************************************Кнопка STOP
if (digitalRead(13) == LOW )
{
 servo1.detach();
 servo2.detach();
}

//***************************************Время работы программы (сервы)
time = millis();
if (time > 10000)
{
servo1.detach();
servo2.detach();
}
//*************************************************************************
//********************************************Перемычка Start
if (digitalRead(A2) == HIGH)
{
servo1.write(95);
servo2.write(96.5);
}
//else
//{
//servo1.write(-360);
//servo2.write(360); 
//}

}
 // delay(500);                               // arbitrary wait time.
