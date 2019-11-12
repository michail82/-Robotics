#include <Ultrasonic.h>

#include "Ultrasonic.h"

Ultrasonic Ultrasonic_Straight (A0, A1); // Trig - first, Echo - second
Ultrasonic Ultrasonic_Right    (A2, A3);
//Ultrasonic Ultrasonic_Left     (7, 8);

unsigned long time;

void setup()
{
   Serial.begin(9600);           // start the serial port
 }
void loop()
{

  float u_r = Ultrasonic_Right.Ranging(CM);     // get distance
  float u_s = Ultrasonic_Straight.Ranging(CM);     // get distance
//  float u_l = Ultrasonic_Left.Ranging(CM);     // get distance
  
  Serial.print    ("Ultrasonic_Right:");
  Serial.print    (u_r);
  Serial.print    ("     ");
  Serial.print    ("Ultrasonic_Straight:");
  Serial.print    (u_s);
  Serial.print    ("     ");
 // Serial.print    ("Ultrasonic_Left:");
  Serial.println  ();        // print the distance

}
