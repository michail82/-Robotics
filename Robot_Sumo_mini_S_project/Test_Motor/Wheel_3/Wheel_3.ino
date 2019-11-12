//Тестировалось на Arduino IDE 1.0.1
int IN4 = 8; //input1 подключен к выводу 8 
int IN3 = 9;
int EN2 = 10;
void setup()
{
 pinMode (EN2, OUTPUT);
 pinMode (IN4, OUTPUT);
 pinMode (IN3, OUTPUT);
}
void loop()
{
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW ); 
  analogWrite(EN2,55);
  delay(2000);
  analogWrite(EN2,105);
  delay(2000);
  analogWrite(EN2,255);
  delay(2000);
  analogWrite(EN2,0);
  delay(5000);
}
