int led =  2;
int led1 = 3;
int led2 = 4;

void setup() {

  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(A1, OUTPUT);

}

void loop(){

if (digitalRead(A1) == HIGH) 
{
digitalWrite(led,  HIGH);

}
if (digitalRead(A1) == LOW) 
{
digitalWrite(led,  LOW);

}

}
