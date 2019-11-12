//***************************************************************EUROBOT_ROBOT********************************
//*******************************************Ultrasonic
#include "Ultrasonic.h"

Ultrasonic Ultrasonic_Straight (11, 12); // Trig - first, Echo - second
Ultrasonic Ultrasonic_Right    (9, 10);
Ultrasonic Ultrasonic_Left     (7, 8);

//*****************************************************************
//*****************************************Время работы программы
unsigned long time;
//*****************************************Индикация батареи 
///*
#define IND1 2        
#define IND2 3   
#define IND3 4    
#define IND4 5        
#define IND5 6  
#define TESTER A0 // порт для подключения батарейки
int data;
float voltage;
//*/
//******************************************************************
//******************************************Cервоприводы
#include <Servo.h>
Servo servo1; 
Servo servo2; 
//********************************************************************************************

void setup() 
{
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

  float u_r = Ultrasonic_Right.Ranging(CM);     // get distance
  float u_s = Ultrasonic_Straight.Ranging(CM);     // get distance
  float u_l = Ultrasonic_Left.Ranging(CM);     // get distance
// /* 
  Serial.print    ("Ultrasonic_Right:");
  Serial.print    (u_r);
  Serial.print    ("     ");
  Serial.print    ("Ultrasonic_Straight:");
  Serial.print    (u_s);
  Serial.print    ("     ");
  Serial.print    ("Ultrasonic_Left:");
  Serial.println  (u_l);        // print the distance
//*/

//*****************************Начало логики поворотов 
                                    //    servo1.write(95);
                                    //    servo2.write(96.5);
                      //servo1.write(-360);
                      //servo2.write(360);
                     //  servo2.write(100); замедленно
//************************************Логика позиционирования ПРАВАЯ ЛЕВАЯ стена 


//******************************************************************************
//************************************Сценарий езды вдоль ПРАВОЙ ЛЕВОЙ стены
if  (u_l < 20) 
{
 u_r = 0;
 servo1.write(90);
 }
if  (u_r > 20) 
{
servo1.write(90);
}
else 
{
servo1.write(-360);
servo2.write(360);
}

//********************************************************************


//*****************************************Индикация батареи
///*
data = analogRead(A0);   
voltage = data * 0.0048;  
 
  if ( voltage <= 1 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, HIGH);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}
  
 else if ( voltage >= 1 && voltage < 2 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, LOW);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}

  else if ( voltage >= 2 && voltage < 3 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, HIGH);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}

  else if ( voltage >= 3 && voltage < 4 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, HIGH);
      digitalWrite(IND4, HIGH);
      digitalWrite(IND5, LOW);
}
      
  else if ( voltage <= 5  ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, HIGH);
      digitalWrite(IND4, HIGH);
      digitalWrite(IND5, HIGH);
}
   //   digitalWrite(IND1, LOW);
   //  digitalWrite(IND2, LOW);
    // digitalWrite(IND3, LOW);
    // digitalWrite(IND4, LOW);
   //  digitalWrite(IND5, LOW);

    //  delay (500);
//*/
//***************************************Время работы программы (сервы)
/*
time = millis();
if (time > 100000)
{
servo1.detach();
servo2.detach();
}
*/
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
//*******************************************Кнопка STOP
if (digitalRead(13) == LOW )
{
 servo1.detach();
 servo2.detach();
}
//*******************************************Ультразву Центр 
}
