#include <AFMotor.h>
#include <QTRSensors.h>

#define NUM_SENSORS   3
#define TIMEOUT       2500
#define EMITTER_PIN   2

AF_DCMotor left_motor(4, MOTOR12_64KHZ);
AF_DCMotor right_motor(1, MOTOR12_64KHZ);


QTRSensorsRC qtrrc((unsigned char[]) {A0, A1, A2}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
  
unsigned int sensorValues[NUM_SENSORS];

void setup()
{ 
  calibrate();
  right_motor.setSpeed(255);
  left_motor.setSpeed(255);
}

void loop()
{
  unsigned int position = qtrrc.readLine(sensorValues);
  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }

  Serial.println(position);
  int left;
  int center;
  int right;
  
  if (sizeof(sensorValues) > 0){
    left = sensorValues[0];
    center = sensorValues[1];
    right = sensorValues[2];

  if (center > 600 )
  {
    // both wheels running
   right_motor.run(FORWARD);
   left_motor.run(FORWARD);
   right_motor.setSpeed(255);
   left_motor.setSpeed(255);
  }
  if (right >  600)
  {
    // only left is on. so going right
    right_motor.run(FORWARD);
    left_motor.run(FORWARD);
    right_motor.setSpeed(255);
    left_motor.setSpeed(1);
  }

  if (left > 600 )
  {
    // right is on, so going left.
    right_motor.run(FORWARD);
    left_motor.run(FORWARD);
    right_motor.setSpeed(1);
    left_motor.setSpeed(255);
  }
    
  }
}


void calibrate(){
  
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 400; i++)
  {
    qtrrc.calibrate();
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on
  Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }

  
  Serial.println();
  Serial.println();
  delay(1000);
  
}
