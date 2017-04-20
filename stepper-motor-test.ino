/*
Adapted by Jose Catarino from:
  Adafruit Arduino - Lesson 16. Stepper
  Adafruit BNO055 Overview Learning Guie

connections
  L293D and Stepper Motor:
        +5V              1|      |9     +5V
        Pin 2            2|      |10    Pin 7
        Stepper blue     3|      |11    Stepper orange
        GND              4|      |12    GND
        GND              5|      |13    GND
        Stepper yellow   6|      |14    Stepper pink
        Pin 4            7|      |15    Pin 6
        +5V              8|      |16    +5V

  servo to pin 9

Previous versions:
  v0                     // unedited code from Adafruit, 4/18/17
  v0.1                   // moved step and speed to loop, 4/18/17
  v1.0                   // added BNO055 sensor input, 4/18/17
  v2.0                   // replaced the Stepper.h library with Accelstepper.h, 4/19/17
  v2.1                   // added setup function components, 4/19/17
  v3.0                   // included pitch control, 4/19/17

Current Version:
  v3.1                   // scaling factor adjustments, 4/19/17
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
#define HALF4WIRE 8

//set up servo library
#include <Servo.h>

//set up pins for the L293D for stepper motor
#define motorPin1  2
#define motorPin2  4
#define motorPin3  6
#define motorPin4  7
AccelStepper stepper1 (HALF4WIRE, motorPin1, motorPin2, motorPin3, motorPin4, true);

//set up servo
Servo myservo;
float pitRate;

//set up constants for sensor input
int rotSpeed = 0; // angular velocity value from BNO055 sensor
int speedC = 500; // a scaling factor for speed
int pitC = 100; // a scaling factor for pitch

void setup()
{
  //servo pins
  myservo.attach(9);

  //Initialise the serial monitor
  Serial.begin(9600);

  // Initialise the sensor
  if(!bno.begin())
  {
    // There was a problem detecting the BNO055 ... check your connections
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  stepper1.setMaxSpeed(12000.0);
  stepper1.setAcceleration(1000.0);
  stepper1.setSpeed(500);
  stepper1.moveTo(120000);

}

void loop()
{
  stepperLoop();
  pitchLoop();
}

// stepper motor control module
void stepperLoop () {
  // set up the get gyroscope function, angular velocity rads/sec
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  // angular velocity * a scaling factor
  rotSpeed = gyro.z() * -speedC;

  // set the speed for the motor
  stepper1.setSpeed(rotSpeed);

  // start the motor
  stepper1.run();
}

// pitch control module
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
