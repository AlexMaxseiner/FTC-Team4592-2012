#pragma config(Hubs,  S3, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S1,     irSeek,         sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S2,     light,          sensorLightActive)
#pragma config(Sensor, S4,     liftSafetyTouch, sensorTouch)
#pragma config(Motor,  mtr_S3_C1_1,     leftDrive,     tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C1_2,     rightDrive,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S3_C2_1,     lift,          tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S3_C2_2,     slide,         tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S3_C3_1,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S3_C3_2,    LeftBooster,          tServoStandard)
#pragma config(Servo,  srvo_S3_C3_3,    RightBooster,               tServoNone)
#pragma config(Servo,  srvo_S3_C3_4,    ClawRelease,               tServoNone)
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

const int grabReleasePositionpeg1 = 195;//241 is highest nm
const int grabReleasePositionpeg2 = 190;
const int grabReleasePositionpeg3 = 200;
const int grabDownPosition= 165;

task main()
{
  initializeRobot();
	int countline = 0;
  waitForStart(); // Wait for the beginning of autonomous phase.
  motor[slide] = -20;//slide over
	wait1Msec(750);
	motor[slide] = 0;
	ClearTimer(T1);
	SensorValue[irSeek] = 0;
	motor[leftDrive]  = 70;
	motor[rightDrive] = 70;
	servo[rightgrab] = grabDownPosition;//set to start position
  while(time1[T1] < 9000)
	{
		if(atLine())
		{
			countline++;

			if(SensorValue[irSeek] >= 5 && SensorValue[irSeek] <= 6)//checks if at the ir beacon
			{
				// at Correct Line
				break;
			}
			else if(countline==1)// if hit the 1st line turn slightly
			{
				motor[rightDrive]= 0;
				motor[leftDrive] = 9;
				wait1Msec(500);
			}
			else if(countline == 2){//if hit the 2nd line turn slightly
				motor[rightDrive] = 0;
				motor[leftDrive] = 1;
				wait1Msec(500);
			}
			motor[leftDrive]  = 75;//drive
			motor[rightDrive] = 75;

			wait1Msec(500);

		}
	}
	if(time1[T1] < 9000)//while less thatn 9 seconds
	{
		nMotorEncoder[leftDrive]  = 0;
		nMotorEncoder[rightDrive] = 0;
		if(countline == 1){

			forward(8.9); //Distance after line till stop
			stopDrive();
			wait1Msec(500);

			servo[rightgrab] = grabReleasePositionpeg1;//put grabber in position to place ring
			wait1Msec(500);
			motor[slide] = 40;//move slide over
			wait1Msec(1000);
			motor[slide] = 0;
			wait1Msec(1000);
	    servo[rightgrab] = grabReleasePositionpeg1 + 10;//move slightly to help put ring on
	    wait1Msec(1000);
			forward(7);//go forward to pull ring off
		}
		else if(countline == 2)
		{
<<<<<<< HEAD
			forward(9);//Distance after line till stop
=======
			forward(8.1);//Distance after line till stop
>>>>>>> 7694e91e1b27e7c839e0c65aaa172770d473e9fc
			stopDrive();
			wait1Msec(500);

			servo[rightgrab] = grabReleasePositionpeg2;//put grabber in position to place ring
			wait1Msec(500);
			motor[slide] = 40;//move over to put ring on
			wait1Msec(1000);
			motor[slide] = 0;
			wait1Msec(1000);
	    servo[rightgrab] = grabReleasePositionpeg2 -8;//move slightly to put ring on
	    wait1Msec(1000);
			forward(7);//go forward to pull ring off
		}
		else if(countline == 3){
<<<<<<< HEAD
			forward(9);//Distance after line till stop
=======
			forward(8.97);//Distance after line till stop
>>>>>>> 7694e91e1b27e7c839e0c65aaa172770d473e9fc
			stopDrive();
			wait1Msec(500);

			servo[rightgrab] = grabReleasePositionpeg3;//move grabber to position to place ring on 3 peg
			wait1Msec(500);
			motor[slide] = 40;//move over to place ring on
			wait1Msec(1000);
			motor[slide] = 0;
			wait1Msec(1000);
	    servo[rightgrab] = grabReleasePositionpeg3 +5;//move slightly to help put ring on
	    wait1Msec(1000);
			forward(7);//go forward to pull ring off
		}






	}
	else
		stopDrive();//if not less than 9 seconds stop
	nMotorEncoder[leftDrive]  = 0;//clea encoders
	nMotorEncoder[rightDrive] = 0;
  while (true) {}
}

void initializeRobot()
{
	servo[claw] = 39; // Store Claw
  ClearTimer(T1);
	ClearTimer(T2);
	ClearTimer(T3);
	ClearTimer(T4);
	servo[rightgrab] 			 = grabDownPosition;//put to starting position
  while(ServoValue(rightgrab) != grabDownPosition) {}
	batteryTest();



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

void forward(float distance) {//forward function to pass in a length in inches and then it goes that for
const float CHANGE = 2;
float totalTraveled = 0;
float encoderTarget = (169.92*distance) - 55.875; //calculate the encoder target
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
	if(leftEncoder > rightEncoder)//changes based on which one has traveled farther
	{
		leftPower  -= CHANGE;
		rightPower += CHANGE;
	}
	else if(leftEncoder < rightEncoder)//same thing
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
		if(!((abs(totalTraveled + (leftEncoder + rightEncoder)/ 2.0)/* average*/)/*adds the distance traveled*/ < abs(encoderTarget)))
		{//while all that is not less than the encoder target
			totalTraveled += (nMotorEncoder[leftDrive] + nMotorEncoder[rightDrive])/ 2.0;// add the aveage of the encoders
			break;//exit
		}
	}
}

motor[leftDrive]  = 0;
motor[rightDrive] = 0;
nMotorEncoder[rightDrive] = 0;
nMotorEncoder[leftDrive]  = 0;
}
