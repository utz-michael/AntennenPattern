
/*
 Stepper Motor Control - one step at a time

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor will step one step at a time, very slowly.  You can use this to
 test that you've got the four wires of your stepper wired to the correct
 pins. If wired correctly, all steps should be in the same direction.

 Use this also to count the number of steps per revolution of your motor,
 if you don't know it.  Then plug that number into the oneRevolution
 example to see if you got it right.

 Created 30 Nov. 2009
 by Tom Igoe

 */
#include <AFMotor.h>
#include <math.h> 
const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor
int EN = 7;  // enables den stepmotor
// initialize the stepper library on pins 8 through 11:

AF_Stepper motor(200, 2);
int stepCount = 0;         // number of steps the motor has taken
int analogPin = 3;       // messpin für den anschluss der Powermeters       
int val = 0;
float power = 0;
float uW=0;
float powerCal = 0;
float CalibrationWert = 0;
float MessAntenne = 2.15;








void setup() {
  // initialize the serial port:
  Serial.begin(9600);
  motor.setSpeed(60);  // 60 rpm   
}

void loop() {
  Serial.println("Press Enter for Start calibration Powermeter muss -25dBm anzeigen" );
while (Serial.available() == 0);
Serial.println(" Calibrierung - bitte warten" );
for (int i=0; i <= 50 ; i++){
      val =  val + analogRead(analogPin); 
      delay(100);
   } 
powerCal = val / 51.0 ;
Serial.print("Power Calibrierung " );
uW=((powerCal*0.0049+0.010)*100.00); // umrechnung analog read in spannung bzw uWatt
CalibrationWert = (10*log10(uW/1000.00))-10.0;
Serial.println(CalibrationWert); // umrechnung uW in dBm und normalisieren
  val = 0;
 Serial.println("");
 Serial.println("");
 Serial.end() ;
 Serial.begin(9600);
 delay(500);

  Serial.println("Messantenne montieren - Press Enter for Start " );
while (Serial.available() == 0);
Serial.println("Dergee;Power" ); 
  do
  {
  Serial.print(roundf (stepCount*5));
  Serial.print(";" );
  delay(2000);
  for (int i=0; i <= 2 ; i++){
      val =  val + analogRead(analogPin); 
      delay(10);
   } 
 power = val / 3.0 ;
uW=((power*0.0049+0.010)*100.00); // umrechnung analog read in spannung bzw uWatt

Serial.println(((10*log10(uW/1000.00))-10.0)-CalibrationWert+MessAntenne); // umrechnung uW in dBm und normalisieren

  power = 0;
  val = 0;
  stepCount++;
 motor.step(18, FORWARD, INTERLEAVE);
  } 
  while (stepCount < 74); // 74 x 5° schritte für 360° drehung
  stepCount=0;
 Serial.println("");
 Serial.println("");
 Serial.end() ;
 Serial.begin(9600);
 delay(500);
}


