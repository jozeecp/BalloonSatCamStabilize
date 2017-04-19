/*
Adapted by Jose Catarino from:
Adafruit Arduino - Lesson 16. Stepper

Previous versions:
  v0                     // unedited code from Adafruit
  v0.1                   // moved step and speed to loop

Current Version:
  v1                     // added BNO055 sensor input
*/

//set up for the BNO055 sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Servo.h>
Adafruit_BNO055 bno = Adafruit_BNO055();

//set up for the Stepper
#include <Stepper.h>

//set up pins for the L293D
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

//set up constants for sensor input
int rotSpeed = 0; //angular velocity value from BNO055 sensor
int speedC = 10; //constant of proportionality for angular velocity
int rotDist = 0; //"steps" always either 500, -500, or 0

Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);

void setup()
{
  // set up the pins to L293D
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

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
  //set up the get gyroscope function
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  rotSpeed = abs(gyro.z() * speedC); // absolute value of the angular velocity x a sclaing factor

  //if sensor is spinning cw, turn stepper in cw direction
  if ((gyro.z() * speedC) > 5) {
    rotDist = 500;
  }
  //if sensor is spinning ccw, turn stepper in ccw direction
  else if ((gyro.z() * speedC) < -5) {
    rotDist = -500;
  }
  //is sensor is relatively still, don't turn
  else {
    rotDist = 0;
  }

  motor.setSpeed(rotSpeed); //set speed proportional to angular velocity of sensor
  motor.step(rotDist); //control cw vs ccw direction

  Serial.print(rotSpeed);
  Serial.print("   ");
  Serial.println(rotDist);

  delay(10);
}
