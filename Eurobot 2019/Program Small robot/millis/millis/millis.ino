01
unsigned long previousMillis = - 1000;
02
unsigned long interval = 10000;
03
void setup() {
04
  Serial.begin(9600);
05
}
06
 
07
void loop() {
08
  Serial.print("Millis ");
09
  Serial.print(millis());
10
  Serial.print(" PreviousMillis ");
11
  Serial.print(previousMillis);
12
  Serial.print(" Interval ");
13
  Serial.print(interval);
14
  Serial.print(" Minus ");
15
  Serial.println(millis() - previousMillis);
16
  if (millis() - previousMillis > interval) {
17
    previousMillis = millis();
18
  }
19
}
