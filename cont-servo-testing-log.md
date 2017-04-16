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
    
