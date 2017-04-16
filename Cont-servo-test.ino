//PWM test for continious motion Servo

int servoPin = 9; // connect servo to pin 10
int pwmVal = 0; // declare pulse width modulation value

void setup(void) {
  pinMode(servoPin, OUTPUT); //set up the servoPin as an output pin
  Serial.begin(9600); // begin serial monitor
}

void loop(void) {
  //for loop that sweeps values from 0 to 255
  for (pwmVal = 0; pwmVal <= 255; pwmVal += 1) {
    analogWrite(servoPin, pwmVal);
    Serial.println(pwmVal);
    delay(100);
  }
  for (pwmVal = 255; pwmVal >= 0; pwmVal -= 1) {
    analogWrite(servoPin, pwmVal);
    Serial.println(pwmVal);
    delay(100);
  }

  analogWrite(servoPin, pwmVal); //send pulse width modulated value to servo
}
