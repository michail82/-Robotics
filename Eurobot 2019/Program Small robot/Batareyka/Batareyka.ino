//*****************************************Индикация батареи 
///*
#define IND1 2        
#define IND2 3   
#define IND3 4    
#define IND4 5        
#define IND5 6  
#define TESTER A1 // порт для подключения батарейки
int data;
float voltage;
//*/

void setup() 
{
//*****************************************Индикация батареи 
pinMode(IND1, OUTPUT);
pinMode(IND2, OUTPUT);
pinMode(IND3, OUTPUT);
pinMode(IND4, OUTPUT);
pinMode(IND5, OUTPUT);
pinMode(TESTER, INPUT);
analogWrite(TESTER, LOW);
}
void loop() {
//*****************************************Индикация батареи
data = analogRead(A0);   
voltage = data * 0.0048;  
 
  if ( voltage <= 1.5 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, LOW);
      digitalWrite(IND3, LOW);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}
  
 else if ( voltage >= 2.5 && voltage < 3 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, LOW);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}

  else if ( voltage >= 3 && voltage < 4.5 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, HIGH);
      digitalWrite(IND4, LOW);
      digitalWrite(IND5, LOW);
}

  else if ( voltage >= 4.5 && voltage < 6 ) 
{
      digitalWrite(IND1, HIGH);
      digitalWrite(IND2, HIGH);
      digitalWrite(IND3, HIGH);
      digitalWrite(IND4, HIGH);
      digitalWrite(IND5, HIGH);
}
      

}
