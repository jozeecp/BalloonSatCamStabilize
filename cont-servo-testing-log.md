test 1
  4/16/17, 1:10 AM: PWM value of 0
    remains still in position

test 2
  4/16/17, 1:19 AM: PWM value of 255
    didn't move. Maybe there's an issue with the wiring

test 3
  4/16/17, 1:29 AM: For loop sweeps from 0 to 255 and back down
    moved at fast constant speed then cause an error
    will try a traditional breadboard (as opposed to the mini breadboard used before) to see if that'll fix

test 4
  4/16/17, 1:34 AM: For loop sweeps from 0 to 255 and back down
    Like test 3, but on the normal breadboard
    Still getting the error where the Arduino goes off,
    likely due to some sort of short

test 5
  4/16/17, 1:42 AM: For loop sweeps from 0 to 255 and back down
    like test 4, but with a different servo (not continous)
    works fine, so the problem is happening with the servo

test 6
  4/16/17, 1:34 AM: Like test 5, but with mod cont servo from 0 to 255 slowed down
    fixed a minor error in the for loop
    fast at values near zero then slows down to a craw around 100 then turns the other direction

test 7
  4/16/17, 1:54 AM: testing values at 10 and 250, mod servo
    consistent with observations from previous tests

From this point on, the next tests will be conducted by connecting two of the pins on the modded servo together
I chose to do this because it gives me full speed at PWM value of 253 (~255)

test 8
  4/16/17, 2:03 AM: testing values at 10 and 250, mod servo
    we get full speed at values near 0 and values near 255, this is good

test 9
  4/16/17, 2:07 AM: sweep from 0 to 255
    expected: the servo will start fast, slow down near 100 and speed up
    to max opposite speed at near 255
    result: the motor went at constant speed at all PWM values,
    and only switched directions at ~40

Using the voltage divider modded servo
test 10
  4/16/17, 2:17 AM: sweep from 0 to 255
  the motor just went at constant speed

Using the unconnected modded servo again
test 11
  4/16/17, 2:20 AM: sweep from 0 to 255, all leads touching
    constant speed and short circuit errors like with the unmodded servo
    this means that the short circuit error with the unmodded servo happens when
    potentiometer is "closed"

Using the unmodded servo
test 12
  4/16/17, 2:24 AM: sweep from 0 to 253 to avoid the short circuit error
    avoided short circuit error!
    But the speeding up and slowing down is not smooth
    neither does it follow a clear pattern

test 13
  4/16/17, 2:28 AM: test various values from 0 to 253
    at 0: no motion
    at 10: almost constant motion at high speed, but there is a "dip" in the motion every revolution
    at 90: no motion, just vibration
    at 250: switches from high speed to low speed at constant intervals, opposite direction to 10

Using the no-potentiometer modded servo
test 14
  4/17/17, 6:54 PM: test various values:
    0 (0% duty cycle): no motion, slight vibration
    64 (25% duty cycle): no motion, slight vibration
    127 (50% duty cycle): no motion, slight vibration
    191 (75% duty cycle): no motion, fainter vibration
    255 (100% duty cycle): no motion, no vibration

Using the voltage-divider modded servo
test 14
  4/17/17, 7:02 PM: test various values:
    0 (0% duty cycle): no motion, vibration
    64 (25% duty cycle): full motion, clockwise
    127 (50% duty cycle): full motion, clockwise
    191 (75% duty cycle): no motion, slight vibration
    255 (100% duty cycle): no motion, no vibration
    253 (99% duty cycle): full motion, counterclockwise
    5 (2% duty cycle): full motion, clockwise
    170 (66% duty cycle):

    From this I can tell that if I map the motion from
