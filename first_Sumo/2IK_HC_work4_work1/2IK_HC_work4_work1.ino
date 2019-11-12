#define Trig 6
#define Echo 12
#define ledPin 13
#define ledPin1 9
#define ledPin2 5
#define pin A0 //желтый провод дальномера подключаем к выводу А0 Arduino
#define pin1 A1
#define buzz 7
#include<Servo.h>//подключаем билиотеку для управления сервоприводами
Servo servo1;
Servo servo2;
int servopin1 = 11;
int servopin2 = 12;
int liniya = 4;
void setup ()
  {
    servo1.write(360);  // servo1.write(360);
     servo2.write(-360);  // servo2.write(-360);
    
    delay (900  );
    pinMode (servopin1, OUTPUT);
    pinMode (servopin2, OUTPUT);
    pinMode (pin, INPUT);
    pinMode (pin1, INPUT);
    pinMode(Trig, OUTPUT); //инициируем как выход 
    pinMode(Echo, INPUT); //инициируем как вход 
    pinMode(ledPin, OUTPUT); 
    pinMode(buzz, OUTPUT);
    Serial.begin (9600); 
    servo1.attach(10);
    servo2.attach(11);
   
}
unsigned int impulseTime=0; 
unsigned int distance_cm=0; 
void loop ()
{
    float value = analogRead (pin); // считываем напряжение с дальномера
    float value1 = analogRead (pin1);
    float range = get_gp2d12 (value);
    float range1 = get_gp2d121 (value1);
  digitalWrite(Trig, HIGH); 
  /* Подаем импульс на вход trig дальномера */
  //delayMicroseconds(10); // равный 10 микросекундам 
  digitalWrite(Trig, LOW); // Отключаем 
  impulseTime=pulseIn(Echo, HIGH); // Замеряем длину импульса 
  distance_cm=impulseTime/58; // Пересчитываем в сантиметры 


if (liniya  = 0 )
 
 {
analogWrite (servopin1, LOW);
digitalWrite (servopin2, LOW);
    } 
   if (distance_cm<=30)  // Расстояние < 40
  {
  servo1.write(360);  // servo1.write(360);
  servo2.write(-360);  // servo2.write(-360);
  }
    if (distance_cm>30)
  {
    servo1.write(-100 ); 
    servo2.write(-100);
  } 
 

if (distance_cm<30)
{     
digitalWrite(ledPin, HIGH); // Светодиод горит 
}  
else 
{   
digitalWrite(ledPin, LOW); // иначе не горит 
}  
if (range1<100)
{     
analogWrite(ledPin1, 255); // Светодиод горит 
}  
else 
{   
analogWrite(ledPin1, 0); // иначе не горит 
}  
if (range<100)
{     
analogWrite(ledPin2, 255); // Светодиод горит 
}  
else 
{   
analogWrite(ledPin2, 0); // иначе не горит 
}  
  if (distance_cm<20)  // Расстояние < 10
  {
     tone(buzz, 500, 200);
  }
   else 
  {
    digitalWrite(buzz, LOW); // И пьезоизлучатель
  }

    Serial.print ("Датчик 1 IK = ");
    Serial.print (range);
    Serial.print (" mm");
    Serial.print ("         ");
    Serial.print ("Датчик 2 IK = ");
    Serial.print (range1);
    Serial.print (" mm");
    Serial.print ("         ");
    Serial.print ("Датчик 3 HC = ");
    Serial.print (distance_cm);
    Serial.print (" cm");
    Serial.println ();
//  delay (500);

}
float get_gp2d12 (float value) 
{ // переводим значение напряжения в расстояние
    if (value < 10) value = 10;
    return ((67870.0 / (value - 3.0)) - 40.0);
}
float get_gp2d121 (float value1) 
{ // переводим значение напряжения в расстояние
    if (value1 < 10) value1 = 10;
    return ((67870.0 / (value1 - 3.0)) - 40.0); 
}
