// Колесо 1
int IN3 = 2;  
int IN4 = 4;
int EN1 = 3;
// Колесо 2
int IN1 = 7;  
int IN2 = 6;
int EN2 = 5;
// Колесо 3
int IN33 = 9;  
int IN44 = 8;
int EN3 = 10;
// Колесо 4
int IN11 = 13; 
int IN22 = 12;
int EN4 = 11;

void setup()
{
 pinMode (EN1, OUTPUT);
 pinMode (EN2, OUTPUT);
 pinMode (EN3, OUTPUT);
 pinMode (EN4, OUTPUT);
 pinMode (IN1, OUTPUT);
 pinMode (IN2, OUTPUT);
 pinMode (IN3, OUTPUT);
 pinMode (IN4, OUTPUT);
 pinMode (IN11, OUTPUT);
 pinMode (IN22, OUTPUT);
 pinMode (IN33, OUTPUT);
 pinMode (IN44, OUTPUT);
}
void loop()
{
//Колесо 1
  digitalWrite (IN4, LOW);
  digitalWrite (IN3, HIGH ); 
//Колесо 2  
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
//Колесо 3  
  digitalWrite (IN44, LOW);
  digitalWrite (IN33, HIGH );
//Колесо 4  
  digitalWrite (IN11, HIGH);
  digitalWrite (IN22, LOW ); 

  analogWrite(EN1,55);
  analogWrite(EN2,55);
  analogWrite(EN3,55);
  analogWrite(EN4,55);
  delay(2000);
  analogWrite(EN1,105);
  analogWrite(EN2,105);
  analogWrite(EN3,105);
  analogWrite(EN4,105);
  delay(2000);
  analogWrite(EN1,255);
  analogWrite(EN2,255);
  analogWrite(EN3,255);
  analogWrite(EN4,255);
  delay(2000);
  analogWrite(EN1,0);
  analogWrite(EN2,0);
  analogWrite(EN3,0);
  analogWrite(EN4,0);
  delay(5000);
}
