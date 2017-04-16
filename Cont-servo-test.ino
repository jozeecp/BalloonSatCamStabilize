//PWM test for continious motion Servo

int servoPin = 10; // connect servo to pin 10
int pwmVal = 0; // declare pulse width modulation value

void setup(void) {
  pinMode(servoPin, OUTPUT); //set up the servoPin as an output pin
  Serial.begin(9600); // begin serial monitor
}

void loop(void) {
  pwmVal = 0;

  analogWrite(servoPin, pwmVal); //send pulse width modulated value to servo
}
