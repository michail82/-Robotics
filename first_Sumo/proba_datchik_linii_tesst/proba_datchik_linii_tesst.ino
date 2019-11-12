int digitalPin = 4;

void setup() {
  Serial.begin(9600);   // Скорость работы порта
  Serial.print ("Datchik linii pokazatel "); // Выводим текст
  Serial.println();                             // Пустая строка 
}

void loop() {
  int digitalsig = digitalRead(digitalPin);  // Задаем переменную analogValue для считывания показаний  
  Serial.println(digitalsig);              // Выводим значения
  delay(500);
}
 
