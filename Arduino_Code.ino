/*
Wiring:

From  sensor, yellow goes to SCL and orange goes to SDA
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Servo.h>
Adafruit_BNO055 bno = Adafruit_BNO055();

Servo myservo;
float val;
float pwmVal = 0;
int contAttach = 10;
int z = 0;
int zp = 0;
float za = 0;

void setup(void)
{
  myservo.attach(9); // servo pin
  pinMode(contAttach, OUTPUT);
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


void loop(void)
{
  // Quaternion data
  imu::Quaternion quat = bno.getQuat();

  float x = quat.x();
  float y = quat.y();


  /*Serial.print("qW: ");
  Serial.print(quat.w());
  Serial.print(" qX: ");
  Serial.print(quat.y(), 4);
  Serial.print(" qY: ");
  Serial.print(quat.x(), 4);
  Serial.print(" qZ: ");
  Serial.print(quat.z(), 4);
  Serial.print("\t\t");
  Serial.println(quat.x() - quat.y(), 4); */

  x = x - .1;

  /* Now we take the x compnent of the rotational motion and mep it to control the servo */
  if (z < .45 && z > -.14)
  {
    val = x * 90;
    val = map(val, -70, 70, 0, 180);
  }
  else if (z >= .45)
  {
    y = y + .15;
    val = y * 120;
    val = map(val, 70, -60, 0, 180);
  }
  else if (z <= -.14)
  {
    y = y - .2;
    val = y * 100;
    val = map(val, -70, 70, 0, 180);
  }


  myservo.write(val);




  /* now the z-component */
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);


  z = gyro.z() * 10;
  zp = euler.z();
  za = quat.z() * 100;
  Serial.print("z: ");
  Serial.print(z);
  Serial.print("    ");
  Serial.print("z': ");
  Serial.print(zp);
  Serial.print("    ");
  Serial.print("z.quat: ");
  Serial.print(za);
  Serial.print("    ");
  Serial.print("pwm: ");
  Serial.println(pwmVal);

  pwmVal = map(z, -100, 100, 0, 255);
  analogWrite(contAttach, pwmVal);

  /*val1 = - (quat.z()) * 85;
  val1 = map(val1, -70, 70, 0, 180);
  myservo1.write(val1); */

  delay(10);
}


  myservo.write(val);

  /* now the z-component */
  val1 = - (quat.z()) * 85;
  val1 = map(val1, -70, 70, 0, 180);
  myservo1.write(val1);

  delay(10);
}
