//PWM test for continious motion Servo

int servoPin = 9; // connect servo to pin 10
int pwmVal = 0; // declare pulse width modulation value
int joyPin = 0; //connect joystick to pin A0

void setup(void) {
  pinMode(servoPin, OUTPUT); //set up the servoPin as an output pin
  pinMode(joyPin, INPUT);
  Serial.begin(9600); // begin serial monitor
}

void loop(void) {

  /* //for loop that sweeps values from 0 to 255
  for (pwmVal = 0; pwmVal <= 255; pwmVal += 1) {
    analogWrite(servoPin, pwmVal);
    Serial.println(pwmVal);
    delay(100);
  }
  for (pwmVal = 255; pwmVal >= 0; pwmVal -= 1) {
    analogWrite(servoPin, pwmVal);
    Serial.println(pwmVal);
    delay(100);
  } */

  /* //assign a static pwm value
  pwmVal = 0;
  analogWrite(servoPin, pwmVal); */

  pwmVal = analogRead(joyPin);
  pwmVal = map(pwmVal, 0, 100, 5, 253);
  Serial.println(joyPin);
}
