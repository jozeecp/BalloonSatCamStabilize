/*
Adapted by Jose Catarino from:
Adafruit Arduino - Lesson 16. Stepper

Previous versions:
  v0                     // unedited code from Adafruit, 4/18/17
  v0.1                   // moved step and speed to loop, 4/18/17
  v1.0                   // added BNO055 sensor input, 4/18/17

Current Version:
  v2.0                   // replaced the Stepper.h library with Accelstepper.h, 4/19/17
*/

//set up for the BNO055 sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Servo.h>
Adafruit_BNO055 bno = Adafruit_BNO055();

//set up the stepper motor library
#include <AccelStepper.h>

//set up pins for the L293D
#define motorPin1  2
#define motorPin2  4
#define motorPin3  6
#define motorPin4  7

//set up constants for sensor input
int rotSpeed = 0; //angular velocity value from BNO055 sensor
int speedC = 10; //a scaling factor
int rotDist = 0; //"steps" always either 500, -500, or 0

AccelStepper stepper1 (HALF4WIRE, motorPin1, motorPin2, motorPin3, motorPin4, true);

void setup()
{

  //Initialise the serial monitor
  Serial.begin(9600);

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);
}

void loop()
{
  // set up the get gyroscope function, angular velocity rads/sec
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  // angular velocity * a scaling factor
  rotSpeed = gyro.z() * speedC;

  // write speed value
  stepper1.setSpeed(rotSpeed);

  //run stepper motor
  stepper1.run();
}
