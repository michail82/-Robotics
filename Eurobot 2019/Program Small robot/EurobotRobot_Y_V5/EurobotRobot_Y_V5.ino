//***************************************************************EUROBOT_ROBOT********************************
//*******************************************Ultrasonic
#include "Ultrasonic.h"

Ultrasonic Ultrasonic_Straight (11, 12); // Trig - first, Echo - second
Ultrasonic Ultrasonic_Right    (9, 10);
Ultrasonic Ultrasonic_Left     (7, 8);

//***************************************************************** Кнопка STOP
#define KNOPKA 13 

//*****************************************Время работы программы
unsigned long time;
//*****************************************Индикация батареи 
///*
#define IND1 2        
#define IND2 3   
#define IND3 4    
#define IND4 5        
#define IND5 6  
#define TESTER A1 // порт для подключения батарейки
int data;
float voltage;
//*/
//******************************************************************
//******************************************Cервоприводы
#include <Servo.h>
Servo servo1; 
Servo servo2; 
//********************************************************************************************
// *******************************************************Движение Право Лево 
 
float side = 0;


void setup() 
{
// *******************************************************Движение Право Лево 
// 1-Левая сторона 2-Правая сторона

if (Ultrasonic_Right.Ranging(CM) > 25)
{
  side=1;
}

if (Ultrasonic_Left.Ranging(CM) > 25)
{
  side=2;
}
delay (100);
//*******************************************Ultrasonic 


Serial.begin(9600); 
  
//*******************************************Сервоприводы
servo1.attach(A3); 
servo2.attach(A4); 

servo1.write(95);
servo2.write(96.5);

//*****************************************Индикация батареи 
pinMode(IND1, OUTPUT);
pinMode(IND2, OUTPUT);
pinMode(IND3, OUTPUT);
pinMode(IND4, OUTPUT);
pinMode(IND5, OUTPUT);
pinMode(TESTER, INPUT);
analogWrite(TESTER, LOW);
//*********************************************Перемычка

pinMode(A2, OUTPUT);

//********************************************Кнопка STOP

pinMode(13, OUTPUT);

}
//*****************************************************************************
void loop() {
//******************************************Сервоприводы 

//servo1.write(-360);
//servo2.write(360); 

//*******************************************Ultrasonic 

  float u_r = Ultrasonic_Right.Ranging(CM);        // get distance
  float u_s = Ultrasonic_Straight.Ranging(CM);     // get distance
  float u_l = Ultrasonic_Left.Ranging(CM);         // get distance
// /* 
  Serial.print    ("Ultrasonic_Right:");
  Serial.print    (u_r);
  Serial.print    ("     ");
  Serial.print    ("Ultrasonic_Left:");
  Serial.print    (u_s);
  Serial.print    ("     ");
  Serial.print    ("Ultrasonic_Straight:");
  Serial.print    (u_l);
  Serial.print    ("     ");
  Serial.print    (side);
  Serial.println ();
  
        // print the distance
//*/

//*****************************Начало логики поворотов 
                                    //    servo1.write(95); stop           servo1.write(90); медленнней
                                    //    servo2.write(96.5); stop         servo2.write(100); медленнней
                      servo1.write(-360);
                      servo2.write(360);
                      
//************************************Сценарий езды вдоль ПРАВОЙ ЛЕВОЙ стены 
//************************************Если по отдельности
//*******************************************Левый борт зеленый
//if  (u_l < 10) 
//{
// servo1.write(90);
// }
//******************************************************
//****************************************** Правый борт желтый
//if  (u_r > 15)
//{
//servo1.write(90);
//}
//******************************************Логика Правый Левый борт !!!!!!!!!!!!!!!!!!!
if (side == 1) 
{
if  (u_l < 15)  servo1.write(90);
else 
{
servo1.write(-360);
servo2.write(360);
}
}

if (side == 2) 
{
if  (u_r > 15)  servo1.write(90);
else 
{
servo1.write(-360);
servo2.write(360);
}
}
//if ((u_r < 15) && (u_r > 5))
//{
 //servo1.write(90);
//}
//******************************************************************************


//******************************************************
                                                    
//if  ((u_l < 20) || (u_r > 1))
// {
// servo1.write(90);
//
//}
//if  (u_r > 20)// && (u_l > 1))
// else if  ((u_r < 20) && (u_l > 1))
//{
// servo1.write(90);
//}
//else 
//{
//servo1.write(-360);
//servo2.write(360);
//}

//********************************************************************


//*****************************************Индикация батареи
///*
data = analogRead(A0);   
voltage = data * 0.0048;  
 
  if ( voltage <= 1.5 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, LOW);
      digitalWrite(IND3, LOW);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}
  
 else if ( voltage >= 2.5 && voltage < 3 ) 
{
      digitalWrite(IND1, LOW);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, LOW);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}

  else if ( voltage >= 3 && voltage < 4.5 ) 
{
      digitalWrite(IND1, LOW);
      digitalWrite(IND2, LOW);
      digitalWrite(IND3, HIGH);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}

  else if ( voltage >= 4.5 && voltage < 6 ) 
{
      digitalWrite(IND1, LOW);
      digitalWrite(IND2, LOW);
      digitalWrite(IND3, LOW);
      digitalWrite(IND4, HIGH);
      digitalWrite(IND5, HIGH);
}
   //   digitalWrite(IND1, LOW);
  //    digitalWrite(IND2, LOW);
    //  digitalWrite(IND3, LOW);
    //  digitalWrite(IND4, LOW);
   //   digitalWrite(IND5, LOW);

    //  delay (500);
//*/
//***************************************Время работы программы (сервы)

time = millis();
if (time > 20000)
{
servo1.detach();
servo2.detach();
}

//********************************************Перемычка Start
if (digitalRead(A2) == HIGH)
{
servo1.write(95);
servo2.write(96.0);
}
//else
//{
//servo1.write(-360);
//servo2.write(360); 
//}
//*******************************************Кнопка STOP
if (digitalRead(KNOPKA) == LOW )
{
// digitalWrite (KNOPKA, LOW);
 servo1.detach();
 servo2.detach();
}
//*******************************************Ультразву Центр 
}
