#include <PS3USB.h>                 // библиотека геймпада PS3
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
//int Speed_Dec = 10;                                                                             //СЕРВАКИ
int p = 0; // позиционирование по кнопке X
int a = 0;  // позиционирование по кнопке CIRCLE SQUARE
int z = 0;  // позиционирование по кнопке TRIANGLE
int k = 0; // kleshnya
int speedZ = 0;
int speedY = 0;
int speedX = 0;
int LowSpeed = 0;

//переменные для управления двигателями
signed short int motor1;
signed short int motor2;
signed short int motor3;
signed short int motor4;



int ini0, ini1, ini2, ini3, ini4, i, j; // переменный начальных положений сервомоторов и прочие
//int speed = 0; //скорость двигателей 0-255 **************************************************************************************************************************************************
int Mytime = 30; // временная задержка для движения
int CoordinateRY, RY1; // для кооринат по веритикали правого джйстика
int CurrentTime;
int Score;

const byte ROWS = 4; //число строк у нашей клавиатуры

const byte COLS = 4; //число столбцов у нашей клавиатуры

char hexaKeys[ROWS][COLS] = {

  {'1', '2', '3', 'A'}, // здесь мы располагаем названия наших клавиш, как на клавиатуре,для удобства пользования

  {'4', '5', '6', 'B'},

  {'7', '8', '9', 'C'},

  {'*', '0', '#', 'D'}

};
byte rowPins[ROWS] = {26, 28, 30, 32}; //к каким выводам подключаем управление строками

byte colPins[COLS] = {34, 36, 38, 40}; //к каким выводам подключаем управление столбцами

//initialize an instance of class NewKeypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {  //***************************************************************************************************************************************************************************************************************

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
  MSS.servoSet(3, SERVO_SG90);  // манипулятор правый
  MSS.servoSet(1, SERVO_SG90);  // плечо манипулятора
  MSS.servoSet(4, SERVO_SG90);//основа
  MSS.servoSet(2, SERVO_SG90);//клешня
  MSS.begin(0x40, 50);         // Инициализация модуля (Адрес по умолчанию = 0x40. Частота по умолчанию = 50Гц)
  // начальные настройки серво моторов
  Score = 0;
  ini0 = 30;
  i = ini0;
  ini1 = 120;
  j = ini1;
  ini3 = 25;
  ini4 = 15;
  ini2 = 65; //значение для клешни
  servo();
  Serial.begin(9600);

  lcd.init(); // Инициализируем экран

  lcd.backlight();
}







void loop() { //*****************************************************************************************************************************************************************************************
  Usb.Task();  // общая инициализация геймпада

  // стоп если ничего не нажато. Чтобы работало норм, ввели задержку Mytime везде


  // управление дополнительными передними кнопками
  //  Скорость уменьшается при зажатой R2 и увеличивается при зажатой L2
  if (PS3.getAnalogButton(L2) > 250)
    LowSpeed = 1;
  else
    LowSpeed = 0;

  // действие по нажатию
  if (PS3.getButtonClick(L1)) { // кнопка L1 - стоп

    if (p != 3) {
      p = 3;
      servo();

    }
    else {
      p = 0;
      servo();

    }
  }
  //***************забор шайб*************** движение вниз
  if (PS3.getButtonClick(R1)) {
    if (a != 0) {
      a = 0;
      servo();
      delay(250);
    }
    if (p != 2) {
      p = 2;

      servo();

    }
    else {
      p = 0;
      servo();


    }
  }
  if (PS3.getButtonClick(L3)) {
    if (p != 1) {
      p = 1;
      servo();
    } else {
      p = 0;
      servo();
    }


  }


  // управление джойстиками
  if (PS3.PS3Connected) { // эта проверка позволяет избежать случайных включений

    // управление ПРАВЫМ джойстиком



    // управление ЛЕВЫМ джойстиком


    if (LowSpeed == 0) {
      speedY = map(PS3.getAnalogHat(LeftHatY), 0, 255, 200, -200);
      speedZ = map(PS3.getAnalogHat(LeftHatX), 0, 255, 130, -130);

      if (PS3.getButtonPress(UP)) { // кнопка UP - едем вперед
        speedY = 200;
        delay(Mytime);
      }
      if (PS3.getButtonPress(DOWN)) {  // кнопка DOWN - едем назад
        speedY = -200;
        delay(Mytime);

      }

      if (PS3.getButtonPress(LEFT)) {  // кнопка LEFT - движение влево
        speedX = 200;
        delay(Mytime);
      } else {
        if (PS3.getButtonPress(RIGHT)) {  // кнопка RIGHT - движение вправо
          speedX = -200;
          delay(Mytime);
        }
        else {
          speedX = 0;
        }
      }

    } else {
      speedY = map(PS3.getAnalogHat(LeftHatY), 0, 255, 70, -70);
      speedZ = map(PS3.getAnalogHat(LeftHatX), 0, 255, 50, -50);

      if (PS3.getButtonPress(UP)) { // кнопка UP - едем вперед
        speedY = 100;
        delay(Mytime);
      }
      if (PS3.getButtonPress(DOWN)) {  // кнопка DOWN - едем назад
        speedY = -100;
        delay(Mytime);

      }

      if (PS3.getButtonPress(LEFT)) {  // кнопка LEFT - движение влево
        speedX = 100;
        delay(Mytime);
      } else {
        if (PS3.getButtonPress(RIGHT)) {  // кнопка RIGHT - движение вправо
          speedX = -100;
          delay(Mytime);
        }
        else {
          speedX = 0;
        }
      }

    }




    // управление левыми 4-мя кнопками




    // управление правыми 4-мя кнопками

    if (PS3.getButtonClick(TRIANGLE)) {
      if (k != 0) {
        k = 0;
        servo();
      }
      else {
        k = 1;
        servo();

      }
    }

    if (PS3.getButtonClick(CROSS)) {
      if (p != 0) {
        p = 0;
        servo();
        delay(250);
      }
      if (a != 2) {
        a = 2;
        servo();
      }
      else {
        a = 0;
        servo();
      }
    }

    if (PS3.getButtonClick(CIRCLE)) { // правый манипулятор


      if (z != 1) {
        z = 1;
        servo();
      } else {
        z = 0;
        servo();
      }
    }
    if (PS3.getButtonClick(SQUARE)) {// левый нижний_для забора шайб
      if (p != 0) {
        p = 0;
        servo();
        delay(250);
      }
      if (a != 1) {
        a = 1;
        servo();
      }
      else {
        a = 0;
        servo();
      }
    }
  }







  char customKey = customKeypad.getKey();

  if (Score / 100 == 0) {
    if (customKey == '0') {
      Score = Score * 10;
      lcd.clear();
      lcd.print(Score);
    } else {
      if (customKey == '1') {
        Score = Score * 10 + 1;
        lcd.clear();
        lcd.print(Score);
      } else {
        if (customKey == '2') {
          Score = Score * 10 + 2;
          lcd.clear();
          lcd.print(Score);
        } else {
          if (customKey == '3') {
            Score = Score * 10 + 3;
            lcd.clear();
            lcd.print(Score);
          } else {
            if (customKey == '4') {
              Score = Score * 10 + 4;
              lcd.clear();
              lcd.print(Score);
            } else {
              if (customKey == '5') {
                Score = Score * 10 + 5;
                lcd.clear();
                lcd.print(Score);
              } else {
                if (customKey == '6') {
                  Score = Score * 10 + 6;
                  lcd.clear();
                  lcd.print(Score);
                } else {
                  if (customKey == '7') {
                    Score = Score * 10 + 7;
                    lcd.clear();
                    lcd.print(Score);
                  } else {
                    if (customKey == '8') {
                      Score = Score * 10 + 8;
                      lcd.clear();
                      lcd.print(Score);
                    } else {
                      if (customKey == '9') {
                        Score = Score * 10 + 9;
                        lcd.clear();
                        lcd.print(Score);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  if (customKey == '*') {
    Score = 0;
    lcd.clear();
    lcd.print(Score);
  } else {
    if (customKey == 'A') {
      Score = 0;
      lcd.clear();
      lcd.print(Score);
    } else {
      if (customKey == 'B') {
        Score = 0;
        lcd.clear();
        lcd.print(Score);
      } else {
        if (customKey == 'C') {
          Score = 0;
          lcd.clear();
          lcd.print(Score);
        } else {
          if (customKey == 'D') {
            Score = 0;
            lcd.clear();
            lcd.print(Score);
          } else {
            if (customKey == '#') {
              Score = 0;
              lcd.clear();
              lcd.print(Score);
            }
          }
        }
      }
    }
  }
  speedX = constrain(speedX, -250, 250);
  speedY = constrain(speedY, -250, 250);
  speedZ = constrain(speedZ, -250, 250);
  Move();
}


// подпрограммы ****************************************************************************************************************************************************************************

void servo() {


  switch (p) { //----------------------------------------------------------------------------------------------------------------------
    case 0:
      MSS.servoWrite(1, ini1 - 15);

      MSS.servoWrite(4, ini4);

      break;
    case 1:
      MSS.servoWrite(1, ini1 - 10);

      MSS.servoWrite(4, ini4 + 15);

      break;
    case 2:
      MSS.servoWrite(4, ini4 + 140);

      MSS.servoWrite(1, ini1 - 60);

      break;
    case 3:
      MSS.servoWrite(1, ini1 - 100);

      MSS.servoWrite(4, ini4 + 100);

      break;
    case 4:

      break;
  }
  switch (a) { //----------------------------------------------------------------------------------------------------------------------
    case 0:
      MSS.servoWrite(0, ini0 - 10);

      break;
    case 1:
      MSS.servoWrite(0, ini0 + 65);

      break;
    case 2:
      MSS.servoWrite(0, ini0 + 130); // вниз 150

      break;
    case 3:

      break;
    case 4:

      break;
  }
  switch (z) { //----------------------------------------------------------------------------------------------------------------------
    case 0:
      MSS.servoWrite(3, ini3+30);

      break;
    case 1:
      MSS.servoWrite(3, ini3 + 70);

      break;
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
  }
  switch (k) { //----------------------------------------------------------------------------------------------------------------------
    case 0:
      MSS.servoWrite(2, ini2 + 52);

      break;
    case 1:
      MSS.servoWrite(2, ini2);

      break;
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
  }





}


void Move() {
  motor1 = speedX - speedY;
  motor2 = - speedX - speedY;
  motor3 = speedX + speedY;
  motor4 = - speedX + speedY;

  motor1 = constrain(motor1, -240, 240);
  motor2 = constrain(motor2, -240, 240);
  motor3 = constrain(motor3, -240, 240);
  motor4 = constrain(motor4, -240, 240);

  motor1 += speedZ;
  motor2 += speedZ;
  motor3 += speedZ;
  motor4 += speedZ;

  motor1 = constrain(motor1, -250, 250);
  motor2 = constrain(motor2, -250, 250);
  motor3 = constrain(motor3, -250, 250);
  motor4 = constrain(motor4, -250, 250);

  Serial.println(motor1);
  Serial.print("   ");
  Serial.print(motor2);
  Serial.print("   ");
  Serial.print(motor3);
  Serial.print("   ");
  Serial.print(motor4);
  Serial.print("   ");

  //*******************************************************************************************************
  if (motor1 > -4 && motor1 < 4) {
    digitalWrite(Ain3, LOW);
    digitalWrite(Ain4, LOW);
  } else {
    if (motor1 > 4) {
      digitalWrite(Ain3, LOW);
      digitalWrite(Ain4, HIGH);
      analogWrite(AenB, abs(motor1));
    } else
    {
      if (motor1 < -4) {
        digitalWrite(Ain3, HIGH);
        digitalWrite(Ain4, LOW);
        analogWrite(AenB, abs(motor1));
      }
    }
  }

  //**************************************************************************************************************
  if (motor2 > -4 && motor2 < 4) {
    digitalWrite(Bin3, LOW);
    digitalWrite(Bin4, LOW);
  } else {
    if (motor2 > 4) {
      digitalWrite(Bin3, HIGH);
      digitalWrite(Bin4, LOW);
      analogWrite(BenB, abs(motor2));
    } else
    {
      if (motor2 < -4) {
        digitalWrite(Bin3, LOW);
        digitalWrite(Bin4, HIGH);
        analogWrite(BenB, abs(motor2));
      }
    }
  }

  //*********************************************************************************************************************
  if (motor3 > -4 && motor3 < 4) {
    digitalWrite(Ain1, LOW);
    digitalWrite(Ain2, LOW);
  } else {
    if (motor3 > 4) {
      digitalWrite(Ain1, LOW);
      digitalWrite(Ain2, HIGH);
      analogWrite(AenA, abs(motor3));
    } else
    {
      if (motor3 < -4) {
        digitalWrite(Ain1, HIGH);
        digitalWrite(Ain2, LOW);
        analogWrite(AenA, abs(motor3));
      }
    }
  }

  //****************************************************************************************************************************
  if (motor4 > -4 && motor4 < 4) {
    digitalWrite(Bin1, LOW);
    digitalWrite(Bin2, LOW);
  } else {
    if (motor4 > 4) {
      digitalWrite(Bin1, LOW);
      digitalWrite(Bin2, HIGH);
      analogWrite(BenA, abs(motor4));
    } else
    {
      if (motor4 < -4) {
        digitalWrite(Bin1, HIGH);
        digitalWrite(Bin2, LOW);
        analogWrite(BenA, abs(motor4));
      }
    }
  }

}
//*******************************************************************************************************
