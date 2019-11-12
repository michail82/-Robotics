int liniya1  = A4;
int liniya2  = A5;

void setup() {
  Serial.begin(9600);   // Скорость работы порта
  Serial.print ("Datchik linii pokazatel "); // Выводим текст
  Serial.println();                             // Пустая строка 
}

void loop() {
  int Lsig1 = analogRead(liniya1);  // Задаем переменную analogValue для считывания показаний  
  int Lsig2 = analogRead(liniya2);
  Serial.print   ("liniya1 = ");  
  Serial.print   (Lsig1);// Выводим значения
  Serial.print   ("   ");
  Serial.print   ("liniya2 = ");  
  Serial.print   (Lsig2);// Выводим значения
  Serial.println ( );
 // delay(500);
}
 
