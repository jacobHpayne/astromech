#include <SpeedyStepper.h>

const float LATITUDE = 41.662013938945336; // Van Allen location
const float LONGITUDE = -91.53219935314317; // Van Allen location
const int MOTOR_X_STEP_PIN = 2;
const int MOTOR_Y_STEP_PIN = 3;
const int MOTOR_X_DIR_PIN = 5;
const int MOTOR_Y_DIR_PIN = 6;
const int STEPPERS_ENABLE_PIN = 8;
int rotSpeed = 1600;
const int microStep = 8; // 8 microsteps per 1 step
                         // 200*8 = 1600 steps per revolution
const float gearRatioHa = 10; 
const float gearRatioDec = 10;
const double stepsPerDegHa = 200*microStep*gearRatioHa / 360;
const double stepsPerDegDec = 200*microStep*gearRatioDec / 360;
const long homePositionDec = 90 * stepsPerDegDec; // 90 deg * steps/deg
const long homePositionHa  = 0 * stepsPerDegHa;   // 0 deg * steps/deg

//
// create the stepper motor objects
//
SpeedyStepper stepperHa;
SpeedyStepper stepperDec;

long targetHa, targetDec; // Steps number
double ha, dec, haMin;

void setup() {
  // put your setup code here, to run once:
    // connect to stepper motors
  stepperHa.connectToPins(MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN);
  stepperDec.connectToPins(MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN);
  stepperHa.setAccelerationInStepsPerSecondPerSecond(50000);
  stepperDec.setAccelerationInStepsPerSecondPerSecond(50000);
  stepperHa.setSpeedInStepsPerSecond(rotSpeed);
  stepperDec.setSpeedInStepsPerSecond(rotSpeed);
  Serial.begin(9600);

  //
  // enable the stepper motors
  //
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);     // be sure to do this
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    double newHa = Serial.parseFloat();
    double newDec = Serial.parseFloat();
    Serial.println(newHa);    
    if (Serial.read() == "\n") {
      break;
    }
    targetHa = long(newHa * stepsPerDegHa);
    targetDec = long(newDec * stepsPerDegDec);
    slewToHa(targetHa);
    slewToDec(targetDec);
    
  }

  

  //Serial.println("Running just the X stepper");
  //runJustTheHaStepper();

}

void runJustTheHaStepper() 
{
  //
  // set the speed and acceleration rates for the stepper motor
  //
  //stepperX.setSpeedInStepsPerSecond(100);
  //stepperX.setAccelerationInStepsPerSecondPerSecond(100);

  //
  // Rotate the motor in the forward direction one revolution (200 steps). 
  // This function call will not return until the motion is complete.
  //
  //stepperX.moveRelativeInSteps(200);

  //
  // now that the rotation has finished, delay 1 second before starting 
  // the next move
  //
  //delay(1000);

  //
  // rotate backward 1 rotation, then wait 1 second
  //
  //stepperX.moveRelativeInSteps(-200);
  //delay(1000);

  //
  // This time speedup the motor, turning 10 revolutions.  Note if you
  // tell a stepper motor to go faster than it can, it just stops.
  //
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);
  stepperHa.setSpeedInStepsPerSecond(rotSpeed);
  stepperHa.setAccelerationInStepsPerSecondPerSecond(50000);
  stepperHa.moveRelativeInSteps(200 * 32);
  digitalWrite(STEPPERS_ENABLE_PIN, HIGH);
  delay(2000);
}

void slewToTarget() {
  slewToHa(targetHa);
  slewToDec(targetDec);
}

void slewToHa(long targetHa) {
    stepperHa.moveToPositionInSteps(targetHa);
}

void slewToDec(long targetDec) {
    stepperDec.moveToPositionInSteps(targetDec);
}
