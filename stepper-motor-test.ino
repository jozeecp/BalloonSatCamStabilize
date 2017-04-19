/*
Adapted by Jose Catarino from:
Adafruit Arduino - Lesson 16. Stepper
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
int rotDist = 0; //degrees turned by sensor
int distC = 100;//constant of proportionality for degrees turned

int g1 = 0;
int g2 = 0;
int g3 = 0;
int g4 = 0;


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
//set up for get vector values
  //set up the get quat function
  imu::Quaternion quat = bno.getQuat();

  //set up the get gyroscope function
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);


  rotSpeed = abs(gyro.z() * speedC); // andgular velocity from sensor, gyroscope
  g1 = quat.z() * distC;
  g2 = g1;
  g3 = g2;
  g4 = g3;

  if ((gyro.z() * speedC) > 5) {
    rotDist = 500;
  }
  else if ((gyro.z() * speedC) < -5) {
    rotDist = -500;
  }
  else {
    rotDist = 0;
  }

  //motor.setSpeed(38);
  //motor.step(500);

  Serial.print(rotSpeed);
  Serial.print("   ");
  Serial.println(rotDist);

  delay(10);
}
