#include <Servo.h> //используем библиотеку для работы с сервоприводом
Servo servo1; //объявляем переменную servo типа Servo
Servo servo2;
void setup() //процедура setup
{
servo1.attach(A3); //привязываем привод к порту 8
servo2.attach(A4); //привязываем привод к порту 8
}
void loop() //процедура loop
{
servo1.write(90);
servo2.write(100); //ставим вал под 180
}
