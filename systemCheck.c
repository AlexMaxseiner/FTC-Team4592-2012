#pragma config(Hubs,  S3, HTMotor,  HTMotor,  HTServo,  HTMotor)
#pragma config(Sensor, S1,     irSeek,         sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Sensor, S3,     ,               sensorI2CMuxController)
#pragma config(Sensor, S4,     liftSafetyTouch, sensorTouch)
#pragma config(Motor,  mtr_S3_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     rightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S3_C2_1,     lift,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     slide,         tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C4_1,     greenlight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S3_C4_2,     redlight,      tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S3_C3_1,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S3_C3_2,    LeftBooster,          tServoStandard)
#pragma config(Servo,  srvo_S3_C3_3,    RightBooster,         tServoStandard)
#pragma config(Servo,  srvo_S3_C3_4,    ClawRelease,          tServoNone)
#pragma config(Servo,  srvo_S3_C3_5,    leftgrab,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_6,    rightgrab,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "globalVariables.h"
#include "globalFunctions.c"
bool goingToTarget = false;
int targetLiftPos = 0;
const int liftUpPower              = 80;
const int liftDownPower            = 80;
task btnLiftControl();
task main()
{
	nMotorEncoder[lift] = 0;
	/*   Testing order
	*1. batteryTest
	*2. Lift up
	*3. Claw Close
	*4. Claw Open
	*5. Lift Down
	*6. leftDrive forward
	*7. rightDrive forward
	*8. leftDrive backward
	*9. rightDrive backward
	*10. both sides stop
	*11. autonomous claw left and right move
	*/
	batteryTest();
	wait10Msec(200);
	targetLiftPos = 4;
	StartTask(btnLiftControl);
	while(goingToTarget)
	{}
	StopTask(btnLiftControl);
	motor[lift] = 0;
	wait1Msec(2000);
	//claw open - claw close
	servo[claw] = 200;
	wait1Msec(1000);
	servo[claw] = 255;
	wait1Msec(1000);
	servo[claw] = 200;
	wait1Msec(2000);
	while(nMotorEncoder[lift] > 0)
	{
		liftAssignSafety(-80);
	}
	wait1Msec(30000);
	/*
	motor[leftDrive] = 100;
	motor[rightDrive] = 100;
	wait1Msec(5000);
	motor[leftDrive] = -100;
	motor[rightDrive] = -100;
	wait1Msec(5000);
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
	wait1Msec(2000);
	servo[leftgrab] = 150;
	servo[rightgrab] = 150;
	wait10Msec(200);*/
}
task btnLiftControl() {
	int pos = targetLiftPos;
	const int TOLERANCE = 100;
	goingToTarget = true;
	int targetPosition;
	switch (pos)
	{
		case 1:
		targetPosition = 50;
		break;
		case 2:
		targetPosition = 175;
		break;
		case 3:
		targetPosition = 2200;
		break;
		case 4:
		targetPosition = 7600;
		break;
	}
	while(abs(nMotorEncoder[lift] - targetPosition) > TOLERANCE)
	{
		if(nMotorEncoder[lift] > targetPosition)
			liftAssignSafety(-1*liftDownPower);
		else
			liftAssignSafety(liftUpPower);
	}
	liftAssignSafety(0);
	goingToTarget = false;
}
