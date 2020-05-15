#include <PS3USB.h>                 // библиотека геймпада PS3!!!  111
// USB shield сьел 9 и 10 порты. На них ничего нельзя вешать
#include <Keypad.h>// подключаем библиотеку клавиатуры
#include <LiquidCrystal_I2C.h>     // Библиотека дисплея
LiquidCrystal_I2C lcd(0x38, 20, 4); // Инициация дисплея
//#define pin_SW_SDA 23   // Назначение вывода Arduino для работы SDA программной шины I2C.
//#define pin_SW_SCL 22   // Назначение вывода Arduino для работы SCL программной шины I2C.
#include <Wire.h>
#include <iarduino_MultiServo.h>   // Подключаем библиотеку для драйвера
iarduino_MultiServo MSS;           // Объявляем переменную MSS, для работы с библиотекой (объект класса iarduino_MultiServo).


// этот блок для PS3 начало ********************************
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
USB Usb;
/* You can create the instance of the class in two ways */
PS3USB PS3(&Usb); // This will just create the instance
bool printAngle;
uint8_t state = 1;
// этот блок для PS3 конец ********************************

// подключение драйверов двигателей
//  двигатель 1 - Драйвер А слот справа
int AenB = 3; // зеленый ШИМ
int Ain3 = 48; // серый
int Ain4 = 49; // фиолетовый,

//  двигатель 2 - работает - Драйвер В слот справа
int BenB = 4; //  синий ШИМ
int Bin3 = 43; // красный не работает на 51 порту
int Bin4 = 44; // коричневый

//  двигатель 3 - работает - Драйвер А слот слева
int AenA = 5; // синий ШИМ
int Ain1 = 46; // черный
int Ain2 = 47; // белый

//  двигатель 4 -  Драйвер В слот слева
int BenA = 6; // синий ШИМ, а к драйверу коричневый
int Bin1 = 45; //оранжевый был 51 - не работал
int Bin2 = 42; //желтый

#define My_CLK 8  // Pin 8 to clk on encoder (интересно, должен быть только ШИМ?)
#define My_DT  11  // Pin 11 to DT on encoder


//переменные
//int Speed_Dec = 10;
int p = 0; // позиционирование по кнопке X
int z = 0;  // позиционирование по кнопке CIRCLE
int a = 0; // позиционирование по кнопке TRIANGLE
int s = 0; // позиционирование по кнопке SQUARE
int ini0, ini1,ini2,ini3, i, j; // переменный начальных положений сервомоторов и прочие
int speed = 0; //скорость двигателей 0-255
int Mytime = 30; // временная задержка для движения
int CoordinateRY, RY1; // для кооринат по веритикали правого джйстика
int CurrentTime;

const byte ROWS = 4; //число строк у нашей клавиатуры

const byte COLS = 4; //число столбцов у нашей клавиатуры

char hexaKeys[ROWS][COLS] = {

{'1','2','3','w'}, // здесь мы располагаем названия наших клавиш, как на клавиатуре,для удобства пользования

{'4','5','6','e'},

{'7','8','9','C'},

{'*','0',' ','D'}

};
byte rowPins[ROWS] = {26, 28, 30, 32}; //к каким выводам подключаем управление строками

byte colPins[COLS] = {34, 36, 38, 40}; //к каким выводам подключаем управление столбцами

//initialize an instance of class NewKeypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {

  // этот блок для PS3 начало ********************************
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 USB Library Started"));
  Serial.println();
  // этот блок для PS3 конец ********************************
 // lcd.init();
  //lcd.backlight();// Включаем подсветку дисплея

  // Авто позиционирование сервопривода. Глубокий смысл непонятен.
  MSS.servoSet(0, SERVO_SG90);   // центральный нижний манипулятор
  MSS.servoSet(1, SERVO_SG90);  // центральный верхний манипулятор
  MSS.servoSet(3, SERVO_SG90);  // манипулятор правый

  MSS.begin(0x40, 50);         // Инициализация модуля (Адрес по умолчанию = 0x40. Частота по умолчанию = 50Гц)
  // начальные настройки серво моторов
  ini0 = 30;
  i = ini0;
  ini1 = 135;
  j = ini1;
  ini3 = 30;
  MSS.servoWrite(0, ini0);   
  MSS.servoWrite(1, ini1); 
  MSS.servoWrite(3, ini3); //правый манипулятор
    
Serial.begin(9600);

lcd.init(); // Инициализируем экран

lcd.backlight();
}
void loop() { //********************************************************************
  Usb.Task();  // общая инициализация геймпада

  // стоп если ничего не нажато. Чтобы работало норм, ввели задержку Mytime везде
  GlobalStop();
     
  // управление дополнительными передними кнопками
  //  Скорость уменьшается при зажатой R2 и увеличивается при зажатой R2
  if (PS3.getAnalogButton(L2) > 250)
    speed = 70;
  if (PS3.getAnalogButton(R2) > 250)
    speed = 250;
  if (PS3.getAnalogButton(L2) <100 && PS3.getAnalogButton(R2) < 100)
    speed = 130;
    
  // действие по нажатию
  if (PS3.getButtonPress(L1)!=1){  // кнопка L1 - стоп
  
  }
  //***************забор шайб*************** движение вниз
  if (PS3.getAnalogButton(R1)){ 
   
  }
  

    
  // управление джойстиками
  if (PS3.PS3Connected) { // эта проверка позволяет избежать случайных включений

    // управление ПРАВЫМ джойстиком
    CoordinateRY = PS3.getAnalogHat(RightHatY);
    if ( CoordinateRY < 117 && CoordinateRY >30 &&  i > 140) { // вниз
      MSS.servoWrite(1, CoordinateRY);   // от 120 до   120-70
      delay(Mytime);
      RY1 = CoordinateRY - PS3.getAnalogHat(RightHatY);
     // Serial.println(CoordinateRY);

    }
    if (CoordinateRY > 137 ) { // вверх
      Serial.println(CoordinateRY);
      MSS.servoWrite(1, ini1);   // от 120 до   120-70      
      delay(Mytime);
      RY1 = CoordinateRY - PS3.getAnalogHat(RightHatY);
     // Serial.println(RY1);
      
    }
   
    if (PS3.getAnalogHat(RightHatX) < 117 && PS3.getButtonPress(L1)!=1) { 
      //Serial.print(PS3.getAnalogHat(RightHatY));
      
      delay(Mytime);
    }
    if (PS3.getAnalogHat(RightHatX) > 180 && PS3.getButtonPress(L1)!=1) { 
      //Serial.print(PS3.getAnalogHat(RightHatY));
      
      delay(Mytime);
    }
// управление ЛЕВЫМ джойстиком
    if (PS3.getAnalogHat(LeftHatY) < 117) { //  едем вперед
      //Serial.print(PS3.getAnalogHat(LeftHatY));
      MoveForward();
      delay(Mytime);
    }
    if (PS3.getAnalogHat(LeftHatY) > 137) { // едем назад
      //Serial.println(PS3.getAnalogHat(LeftHatY));
      MoveRear();
      delay(Mytime);
    }
    if (PS3.getAnalogHat(LeftHatX) < 117) { // вращение против часовой стрелке
      
      TurnUnclock(); 
      delay(Mytime);
    }
    if (PS3.getAnalogHat(LeftHatX) > 137) { // вращение по часовой стрелке
      MSS.servoWrite(14, 90);
      TurnClock();
      delay(Mytime);
    }
  }  

  // управление левыми 4-мя кнопками
  if (PS3.getButtonPress(UP)) { // кнопка UP - едем вперед
    Serial.print(F("\r\nUp"));
    MoveForward();
    delay(Mytime);
  }
  if (PS3.getButtonPress(DOWN)) {  // кнопка DOWN - едем назад
    Serial.print(F("\r\nDown"));
    MoveRear();
    delay(Mytime);
            
  }

  if (PS3.getButtonPress(LEFT)) {  // кнопка LEFT - движение влево
    Serial.print(F("\r\nLeft"));
    MoveLeft();
    delay(Mytime);
  }
  if (PS3.getButtonPress(RIGHT)) {  // кнопка RIGHT - движение вправо
    Serial.print(F("\r\nRight"));
    MoveRight();
    delay(Mytime);
  }

  // управление правыми 4-мя кнопками

  if (PS3.getButtonClick(TRIANGLE)) {
j = ini1 - 90; 
    MSS.servoWrite(1, j); // начальное 135
    delay(Mytime);
    
    if (p % 2 != 0) {
      j = ini1;
      MSS.servoWrite(1, j);
      delay(Mytime);
    }
    p++;

  }
  
  if (PS3.getButtonClick(CROSS) && j >100) {
    i = ini0+130;
    MSS.servoWrite(0, i); // вниз 150
    delay(Mytime);
    
    if (z % 2 != 0) {
      i = ini0;
      MSS.servoWrite(0, i); // вверх  - начальное положение
      delay(Mytime);   
    }
    z++;
  }
  
  if (PS3.getButtonClick(CIRCLE)) { // правый манипулятор  
    
    MSS.servoWrite(3, ini3+60);
    delay(Mytime);
    
    if (a % 2 != 0) {
      MSS.servoWrite(3, ini3);
      delay(Mytime);
    }
    a++;     
  }
  if (PS3.getButtonClick(SQUARE)) { // левый нижний_для забора шайб
     MSS.servoWrite(0, ini0+65);;
    delay(Mytime);
    
    if (s % 2 != 0) {
      MSS.servoWrite(0, ini0);
      delay(Mytime);
    }
    s++;
  }
char customKey = customKeypad.getKey();

if (customKey){

lcd.print(customKey);
}
if (customKey=='*'){
  lcd.clear();
}
if (customKey=='w'){
  lcd.print("e take");
}
if (customKey=='e'){
  lcd.print("x.");
}
}

// подпрограммы
void GlobalStop() {
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, LOW);
  digitalWrite(Ain3, LOW);
  digitalWrite(Ain4, LOW);
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, LOW);
  digitalWrite(Bin3, LOW);
  digitalWrite(Bin4, LOW);
  
  
}

void MoveForward() {
  // запуск двигателя 1
  digitalWrite(Ain3, HIGH);
  digitalWrite(Ain4, LOW);
  analogWrite(AenB, speed);
  // запуск двигателя 2
  digitalWrite(Bin3, LOW);
  digitalWrite(Bin4, HIGH);
  analogWrite(BenB, speed);
  // запуск двигателя 3
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, HIGH);
  analogWrite(AenA, speed);
  // запуск двигателя 4
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(BenA, speed);
  
  
}

void MoveRear() {
  // запуск двигателя 1
  digitalWrite(Ain3, LOW);
  digitalWrite(Ain4, HIGH);
  analogWrite(AenB, speed);
  // запуск двигателя 2
  digitalWrite(Bin3, HIGH);
  digitalWrite(Bin4, LOW);
  analogWrite(BenB, speed);
  // запуск двигателя 3
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(AenA, speed);
  // запуск двигателя 4
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(BenA, speed);
  
}

void MoveLeft() {     // параллельное перемещение
  // запуск двигателя 1
  digitalWrite(Ain3, LOW);
  digitalWrite(Ain4, HIGH);
  analogWrite(AenB, speed);
  // запуск двигателя 2
  digitalWrite(Bin3, LOW);
  digitalWrite(Bin4, HIGH);
  analogWrite(BenB, speed);
  // запуск двигателя 3
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, HIGH);
  analogWrite(AenA, speed);
  // запуск двигателя 4
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(BenA, speed);
  
}

void MoveRight () {   // параллельное перемещение
  // запуск двигателя 1
  digitalWrite(Ain3, HIGH);
  digitalWrite(Ain4, LOW);
  analogWrite(AenB, speed);
  // запуск двигателя 2
  digitalWrite(Bin3, HIGH);
  digitalWrite(Bin4, LOW);
  analogWrite(BenB, speed);
  // запуск двигателя 3
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(AenA, speed);
  // запуск двигателя 4
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(BenA, speed);
  
}

void TurnUnclock() {  //  поворот против часовой стрелки
  int speed1 = speed*0.7;
  // запуск двигателя 1
  digitalWrite(Ain3, LOW);
  digitalWrite(Ain4, HIGH);
  analogWrite(AenB, speed1);
  // запуск двигателя 2
  digitalWrite(Bin3, HIGH);
  digitalWrite(Bin4, LOW);
  analogWrite(BenB, speed1);
  // запуск двигателя 3
  digitalWrite(Ain1, LOW);
  digitalWrite(Ain2, HIGH);
  analogWrite(AenA, speed1);
  // запуск двигателя 4
  digitalWrite(Bin1, LOW);
  digitalWrite(Bin2, HIGH);
  analogWrite(BenA, speed1);
  
}

void TurnClock() {  //  поворот по часовой стрелки
  // запуск двигателя 1
  int speed1 = speed*0.7;
  digitalWrite(Ain3, HIGH);
  digitalWrite(Ain4, LOW);
  analogWrite(AenB, speed1);
  // запуск двигателя 2
  digitalWrite(Bin3, LOW);
  digitalWrite(Bin4, HIGH);
  analogWrite(BenB, speed1);
  // запуск двигателя 3
  digitalWrite(Ain1, HIGH);
  digitalWrite(Ain2, LOW);
  analogWrite(AenA, speed1);
  // запуск двигателя 4
  digitalWrite(Bin1, HIGH);
  digitalWrite(Bin2, LOW);
  analogWrite(BenA, speed1);
}
