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

Previous versions:
  v0                     // unedited code from Adafruit and AccelStepper.h library, 4/18/17
  v0.1                   // moved step and speed to loop, 4/18/17
  v1.0                   // added BNO055 sensor input, 4/18/17
  v2.0                   // replaced the Stepper.h library with Accelstepper.h, 4/19/17
  v2.1                   // added setup function components, 4/19/17
  v3.0                   // included pitch control, 4/19/17
  v3.1                   // scaling factor adjustments, 4/19/17
  v3.2                   // removed pitch correction, 4/19/17



Current Version:
  v3.2.1                 // full rotation bug fix, 4/20/17
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

// pins for the L293D for stepper motor
#define motorPin1  2
#define motorPin2  4
#define motorPin3  6
#define motorPin4  7
AccelStepper stepper1 (HALF4WIRE, motorPin1, motorPin2, motorPin3, motorPin4, true);


// variables for sensor-controlled motor motion
int rotSpeed = 0;            // angular velocity value from BNO055 sensor
int speedC = 200;            // a scaling factor for speed

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
}

void loop()
{
  // gyroscope function, angular velocity rads/sec
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  // angular velocity * a scaling factor
  rotSpeed = gyro.z() * -speedC;

  // set the speed for the motor
  stepper1.setSpeed(rotSpeed);

  // start the motor
  stepper1.runSpeed();
}
