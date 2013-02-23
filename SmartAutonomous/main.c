#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     HTSMUX,         sensorNone)
#pragma config(Sensor, S3,     HTSMUX,         sensorNone)
#pragma config(Sensor, S4,     touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     rightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     leftDrive,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     slide,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     lift,          tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    rightIRServ,          tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    leftIRServ,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    ring,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C3_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "doLineFollow.c"

void initializeRobot();
task main()
{
  initializeRobot();

  waitForStart(); // Wait for the beginning of autonomous phase.
  //doRidgid();
	//doCyborgVision();
	doLineFollow();
	//doReleaseRing();
  while (true)
  {}
}

void turn(float degrees) {
	const float fullturn = 10498;//encoder value for 360 degrees

	float power = 50;
	float turn = degrees*(10498/360);
	while(abs(nMotorEncoder[leftDrive]) < turn && abs(nMotorEncoder[rightDrive]) < turn) {
		if(degrees > 0) {
			motor[leftDrive] = -1*power;
			motor[rightDrive] = power;
		}
		else {
			motor[leftDrive] = power;
			motor[rightDrive] = -1*power;
		}
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}
void initializeRobot()
{
	LSsetActive(Light1);
  LSsetActive(Light2);
  LSsetActive(Light3);
  LSsetActive(Light4);
  LSsetActive(Light5);
  LSsetActive(Light6);
  StartTask(updateLightSensors); //No robot movement only reads light sensors
  return;
}
