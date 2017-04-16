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
  4/16/17, 2:07 AM: testing values at 10 and 250, mod servo
    expected: the servo will start fast, slow down near 100 and speed up
    to max opposite speed at near 255
    result: the motor went at constant speed at all PWM values,
    and only switched directions at ~40

The next tests will be conducted with the other modded servo

test 10
  4/16/17, 2:17 AM: testing values at 10 and 250, mod servo
  the motor just went at constant speed
