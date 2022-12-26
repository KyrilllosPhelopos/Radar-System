#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "Math.h"
#include <Servo.h>

//===============================================================================
//for servo 

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
//================================================================================


//=================================================================================
//for ultrasunic

#define echoPin 13 // attach pin D13 Arduino to pin Echo of HC-SR04
#define trigPin 11 //attach pin D11 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
//======================================================================================

//=================================================================================
//for tft
MCUFRIEND_kbv tft;
#define GREEN 0x07E0
#define RED 0xF800

#define PI 3.1415926535897932384626433832795

int j, j2;
int i, i2;
//===========================================================================


void setup() {
// =======================================
//init the tft
  tft.reset();
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.invertDisplay(true);
  tft.setTextSize(2);

//=======================================================
//init servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
//======================================================================
//init ultrasunic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  
}

void loop() {

  pos = 0;
  myservo.write(pos);


  for (int p = 0; p < 2000; p++) {

    j = 120 * (cos(PI * p / 2000));
    i = 120 * (sin(PI * p / 2000));
    j2 = 50 * (cos(PI * p / 2000));
    i2 = 50 * (sin(PI * p / 2000));
    if(p%11 == 0)
    {
      //as 2000/180 ==11
      //update position every p increased by 11
      // read the distance value      
      myservo.write(pos);
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH); 
      distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      pos++;     
    }

    
    if(distance < 20) 
    {
    tft.drawLine(i2 + 160, j2 +200, i +160, j +200, RED);
    } 
    else 
    {
      tft.drawLine(i2 + 160, j2 +200, i +160, j +200, GREEN);
    }
    
  }
  
  tft.reset();
  uint16_t ID = tft.readID();
  tft.begin(ID);
}






