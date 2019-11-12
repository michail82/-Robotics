// Укажем, что к каким пинам подключено
int trigPinL = 7; 
int echoPinL = 8;  

int trigPinS = 11; 
int echoPinS = 12;  

int trigPinR = 9; 
int echoPinR = 10; 

 
void setup() { 
  Serial.begin (9600); 
  
  pinMode(trigPinR, OUTPUT); 
  pinMode(echoPinR, INPUT); 
  
  pinMode(trigPinS, OUTPUT); 
  pinMode(echoPinS, INPUT); 
} 
 
void loop() { 
 
  int durationR, distanceR;
  int durationS, distanceS;

  
  // для большей точности установим значение LOW на пине Trig
 
  digitalWrite(trigPinR, LOW); 
  digitalWrite(trigPinS, LOW); 
  delayMicroseconds(2); 

  // Теперь установим высокий уровень на пине Trig
  
  digitalWrite(trigPinR, HIGH);
  digitalWrite(trigPinS, HIGH);
  delayMicroseconds(10); 
  
  digitalWrite(trigPinR, LOW); 
  digitalWrite(trigPinS, LOW); 
  
  // Узнаем длительность высокого сигнала на пине Echo
  
 durationR = pulseIn(echoPinR, HIGH);
   
//  durationS = pulseIn(echoPinS, HIGH); 
  
  // Рассчитаем расстояние
  
  distanceR = durationR / 58;
 
  
  // Выведем значение в Serial Monitor
  
 // Serial.print  ("Left cm:"); 
 // Serial.println     (distanceL); 
 // Serial.println   ("      ");
  Serial.print  ("Ultrasonic_Right:"); 
  Serial.print  (distanceR); 
  Serial.print  ("      "); 
  Serial.print  ("Ultrasonic_Straight:");
  Serial.print  ("BBB"); 
  Serial.print  ("      "); 
  Serial.print  ("Ultrasonic_Left:");
  Serial.println  ("CCC"); 
  
 delay(100);
}
