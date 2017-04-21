/*
Camera Stabilization System by Jose Catarino
    BNO055 code from Adafruit BNO055 Overview Learning Guide

You need:
       L293D IC Chip: H-Bridge Circuit
       stepper motor: https://www.adafruit.com/product/918
       BNO055 Position Sensor: https://www.adafruit.com/product/2472

Connections:
  L293D and Stepper Motor:
        +5V               1|      |9     +5V
        Pin 2             2|      |10    Pin 7
        Stepper blue      3|      |11    Stepper orange
        GND               4|      |12    GND
        GND               5|      |13    GND
        Stepper yellow    6|      |14    Stepper pink
        Pin 4             7|      |15    Pin 6
        +5V               8|      |16    +5V

  stepper mottor red wire left unconnected

  Connect SDA with orange wire
          SCL with yellow wire

Note: if the pitch or the rotation move too fast/slow/wrong direction, adjust the
speedC and pitC variables

Previous versions:
  v0                     // unedited code from Adafruit and AccelStepper.h library, 4/18/17
  v0.1                   // moved step and speed to loop, 4/18/17
  v1.0                   // added BNO055 sensor input, 4/18/17
  v2.0                   // replaced the Stepper.h library with Accelstepper.h, 4/19/17
  v2.1                   // added setup function components, 4/19/17
  v3.0                   // included pitch control, 4/19/17
  v3.1                   // scaling factor adjustments, 4/19/17
  v3.2                   // removed pitch correction, 4/19/17
  v3.2.1                 // full rotation bug fix, 4/20/17

Current Version:
  v4.0                   // included pitch and rotation control, 4/20/17
*/

// libraries needed for BNO055 position sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h> // https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/overview
#include <utility/imumaths.h>
#include <Servo.h>
Adafruit_BNO055 bno = Adafruit_BNO055();

// libraries needed for stepper motor
#include <AccelStepper.h>    // http://www.airspayce.com/mikem/arduino/AccelStepper/index.html
#define HALF4WIRE 8

// servo library
#include <Servo.h>

// pins for the L293D for stepper motor
#define motorPin1  2
#define motorPin2  4
#define motorPin3  6
#define motorPin4  7
AccelStepper stepper1 (HALF4WIRE, motorPin1, motorPin2, motorPin3, motorPin4, true);

// variables for sensor-controlled motor motion
int rotSpeed = 0;            // angular velocity value from BNO055 sensor
int speedC = -200;            // a scaling factor for speed
Servo myservo;
int pitC = 100;              // a scaling factor for pitch



void setup()
{
  // Initialise the serial monitor
  Serial.begin(9600);

  // Initialise the sensor
  if(!bno.begin())
  {
    // There was a problem detecting the BNO055 ... check your connections
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  // Initialise stepper motor values
  stepper1.setMaxSpeed(1000);
  stepper1.setSpeed(500);

  // servo setup
  myservo.attach(9);         // attach servo to pin 9
}



void loop()
{
  stepperControl();
  pitchControl();
}



// stepper control function
void stepperControl() {
  // gyroscope function, angular velocity rads/sec
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  // angular velocity * a scaling factor
  rotSpeed = gyro.z() * speedC;

  // set the speed for the motor
  stepper1.setSpeed(rotSpeed);

  // start the motor
  stepper1.runSpeed();
}



// pitch control function
void pitchLoop() {
  // get absolute angle position
  imu::Quaternion quat = bno.getQuat();

  // define pitRate in terms of quat data
  if ((abs(quat.x())) > (abs(quat.y())) && quat.x() > 0) {
    pitRate = quat.x() * -pitC;
  }
  else if ((abs(quat.x())) > (abs(quat.y())) && quat.x() < 0) {
    pitRate = quat.x() * pitC;
  }
  else if ((abs(quat.x())) < (abs(quat.y())) && quat.y() > 0) {
    pitRate = quat.y() * -pitC;
  }
  else if ((abs(quat.x())) < (abs(quat.y())) && quat.y() < 0) {
    pitRate = quat.y() * pitC;
  }

  // adjust pitRate to servo values
  pitRate = map(pitRate, -70, 70, 0, 180);

  // write pitRate to servo
  myservo.write(pitRate);
}
