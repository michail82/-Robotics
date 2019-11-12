int IN3 = 2; //input1 подключен к выводу 8 
int IN4 = 4;
int EN2 = 3;

int IN1 = 7; //input1 подключен к выводу 8 
int IN2 = 6;
int EN1 = 5;

void setup()
{
 pinMode (EN2, OUTPUT);
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);

 pinMode (EN1, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
}
void loop()
{
  digitalWrite (IN3, HIGH);
  digitalWrite (IN1, HIGH);
  digitalWrite (IN4, LOW ); 
  digitalWrite (IN2, LOW);
  analogWrite(EN1,55);
  analogWrite(EN2,55);
  delay(2000);
  analogWrite(EN1,105);
  analogWrite(EN2,105);
  delay(2000);
  analogWrite(EN2,255);
  analogWrite(EN1,255);
  delay(2000);
  analogWrite(EN1,0);
  analogWrite(EN2,0);
  delay(5000);
}
