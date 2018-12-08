#include <AFMotor.h>

// identifying positives & negatives of the motors. 
AF_DCMotor motor4(4);
AF_DCMotor left_motor(1);
void setup()
{  // sending voltage out to the motors
  
// telling arduino to read from these 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  left_motor.setSpeed(255);
  motor4.setSpeed(255);
  
  
}

void loop()

{
  //Sensor 1
  int right = analogRead(A0);
  //Sensor 2
  int center = analogRead(A1);
  // Sensor 3
  int left = analogRead(A2);
  
  

  if (center > 600 )
  {
    // both wheels running
   left_motor.run(FORWARD);
   motor4.run(FORWARD);
   left_motor.setSpeed(255);
   motor4.setSpeed(255);
  }
  if (right >  600)
  {
    // only left is on. so going right
    left_motor.run(FORWARD);
    motor4.run(FORWARD);
    left_motor.setSpeed(255);
    motor4.setSpeed(1);
  }

  if (left > 600 )
  {
    // right is on, so going left.
    left_motor.run(FORWARD);
    motor4.run(FORWARD);
    left_motor.setSpeed(1);
    motor4.setSpeed(255);
  }
}
