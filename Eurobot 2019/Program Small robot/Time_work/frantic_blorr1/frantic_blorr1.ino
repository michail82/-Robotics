#define time_reload 100000  //обнуление millis
#define time_reload1 1000  //обнуление millis
#include <Servo.h>
Servo servo; 


byte i;           // задаем переменную для цифровых выходов
byte LedMax = 13; // максимальное количество выходов (диодов)
unsigned long time;

void setup()
{
Serial.begin(9600);
for(i=2; i<=LedMax; i++) { pinMode(i, OUTPUT); }

servo.attach(A3);

}
  
void loop()
{
Serial.print("Time: ");

  time = millis();
  Serial.println(time);

for(i=2; i<=LedMax; i++)
digitalWrite (i, HIGH);

if (time > 2000) digitalWrite(4, LOW);
if (time > 2500) digitalWrite(5, LOW);  
if (time > 3000) digitalWrite(6, LOW);
if (time > 3500) digitalWrite(7, LOW);
if (time > 4000) digitalWrite(8, LOW);
//  delay (1000);
//digitalWrite(5, LOW);
 // delay (1000);
if (time > 5000) digitalWrite(4, HIGH);
if (time > 5500) digitalWrite(5, HIGH);  
if (time > 6000) digitalWrite(6, HIGH);
if (time > 6500) digitalWrite(7, HIGH);
if (time > 7000) digitalWrite(8, HIGH);

servo.write(360); //ставим вал под 0

if (time > 7000) 
{ 
servo.detach();
}
 
void(* resetFunc) (void) = 0; 
if (millis()>time_reload)
  {
    resetFunc();
  }
}
