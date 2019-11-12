//мотор-1 
#define inA1 4   
#define inB1 9  
#define pwm1 6  

//мотор-2
#define inA2 7   
#define inB2 8  
#define pwm2 5

void setup()
{
  pinMode(inA1, OUTPUT);     
  pinMode(inB1, OUTPUT);     
  pinMode(pwm1, OUTPUT);    
  pinMode(inA2, OUTPUT);     
  pinMode(inB2, OUTPUT);     
  pinMode(pwm2, OUTPUT);
}

void loop()  
{           
  backward(1023, 1023);    //максимум 1023             
  delay(2000);
  forward(1023, 1023);   
  delay(2000);                    
}

void stop() 
{
  analogWrite(pwm1, 0);
  digitalWrite(inA1, LOW);
  digitalWrite(inB1, LOW);
  analogWrite(pwm2, 0);
  digitalWrite(inA2, LOW);
  digitalWrite(inB2, LOW);
}

void forward(int speed1,int speed2)
{
  digitalWrite(inA1, HIGH);
  digitalWrite(inB1, LOW);
  analogWrite(pwm1, speed1);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB2, LOW);
  analogWrite(pwm2, speed2);
}

void backward(int speed1,int speed2)
{
  digitalWrite(inA1, LOW);
  digitalWrite(inB1, HIGH);
  analogWrite(pwm1, speed1);
  digitalWrite(inA2, LOW);
  digitalWrite(inB2, HIGH);
  analogWrite(pwm2, speed2);
}
