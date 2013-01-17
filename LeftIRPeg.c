#pragma config(Hubs,  S3, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     irSeek,         sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Sensor, S4,     liftSafetyTouch, sensorTouch)
#pragma config(Motor,  mtr_S3_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     rightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S3_C2_1,     lift,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     slide,         tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S3_C3_1,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S3_C3_2,    clawRelease,          tServoStandard)
#pragma config(Servo,  srvo_S3_C3_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_5,    leftgrab,             tServoNone)
#pragma config(Servo,  srvo_S3_C3_6,    rightgrab,            tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "globalVariables.h"
#include "globalFunctions.c"

void initializeRobot();
bool atLine();
void stopDrive();

void forward(float distance);

const int grabReleasePosition = 40;
const int grabdrivingposition = 0;
const int grabDownPosition= 90;

task main()
{
  initializeRobot();
	int countline = 0;
  //waitForStart(); // Wait for the beginning of autonomous phase.
  motor[slide] = 20;
	wait1Msec(750);
	motor[slide] = 0;
	ClearTimer(T1);
	SensorValue[irSeek] = 0;
	motor[leftDrive]  = 70;
	motor[rightDrive] = 70;
	servo[grab] = grabDownPosition;
  while(time1[T1] < 20000)
	{
		if(atLine())
		{
			countline++;
			//stopDrive();
			if(SensorValue[irSeek] >= 5 && SensorValue[irSeek] <= 6)
			{
				// at Correct Line
				break;
			}
			else if(countline==1)
			{
				motor[rightDrive]= 8;
				motor[leftDrive] = 0;
				wait1Msec(500);
			}
			else if(countline == 2){
				motor[rightDrive] = 4;
				motor[leftDrive] = 0;
				wait1Msec(500);
			}
			motor[leftDrive]  = 70;
			motor[rightDrive] = 70;

			wait1Msec(500);

		}
	}
	nMotorEncoder[leftDrive]  = 0;
	nMotorEncoder[rightDrive] = 0;
	forward(10); //Distance after line till stop
	stopDrive();
	servo[grab] = grabReleasePosition;
	motor[slide] = -40;
	wait1Msec(750);
	motor[slide] = 0;
	wait1Msec(1000);
	forward(7);
  while (true) {}
}

void initializeRobot()
{
  ClearTimer(T1);
	ClearTimer(T2);
	ClearTimer(T3);
	ClearTimer(T4);
	servo[grab] 			 = grabDownPosition;
  while(ServoValue(grab) != grabDownPosition) {}
	batteryTest();
  servo[grab]        = clawStorePosition;
  servo[clawRelease] = clawSlideHoldPosition;
  servoChangeRate[grab] = 2;
  return;
}

bool atLine()
{
	int value = SensorValue[light];
	if(value > 45)
	{
		return true;
	}
	return false;
}

void stopDrive()
{
	motor[leftDrive]  = 0;
	motor[rightDrive] = 0;
}

void forward(float distance) {
const float CHANGE = 2;
float totalTraveled = 0;
float encoderTarget = (169.92*distance) - 55.875; //- 111.75;
nMotorEncoder[rightDrive] = 0;
nMotorEncoder[leftDrive]  = 0;
float leftEncoder;
float rightEncoder;
float leftPower  = 50;
float rightPower = 50;
while(abs(totalTraveled) < abs(encoderTarget))
{
	leftEncoder  = nMotorEncoder[leftDrive];
	rightEncoder = nMotorEncoder[rightDrive];
	if(leftEncoder > rightEncoder)
	{
		leftPower  -= CHANGE;
		rightPower += CHANGE;
	}
	else if(leftEncoder < rightEncoder)
	{
		leftPower  += CHANGE;
		rightPower -= CHANGE;
	}
	motor[leftDrive]  = leftPower;
	motor[rightDrive] = rightPower;
	totalTraveled += (leftEncoder + rightEncoder)/ 2.0;
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive]  = 0;
	ClearTimer(T1);
	while(time1[T1] < 200) {
		leftEncoder  = nMotorEncoder[leftDrive];
		rightEncoder = nMotorEncoder[rightDrive];
		if(!((abs(totalTraveled + (leftEncoder + rightEncoder)/ 2.0)) < abs(encoderTarget)))
		{
			totalTraveled += (nMotorEncoder[leftDrive] + nMotorEncoder[rightDrive])/ 2.0;
			break;
		}
	}
}

motor[leftDrive]  = 0;
motor[rightDrive] = 0;
nMotorEncoder[rightDrive] = 0;
nMotorEncoder[leftDrive]  = 0;
}
