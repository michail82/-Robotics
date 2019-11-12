int IN1 = 13; //input1 подключен к выводу 8 
int IN2 = 12;
int EN1 = 11;
void setup()
{
 pinMode (EN1, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
}
void loop()
{
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW); 
  analogWrite(EN1,55);
  delay(2000);
  analogWrite(EN1,105);
  delay(2000);
  analogWrite(EN1,255);
  delay(2000);
  analogWrite(EN1,0);
  delay(5000);
}
