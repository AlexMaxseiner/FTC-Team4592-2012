#ifndef RIGID_C
#define RIGID_C

#include "Cyborggoodstuff.c"

bool linefound();
bool findline();
const float dist2rack = 75;
float inches2encoder(float distance);
void doRidgid() {
	forward(32);
	wait1Msec(1000);
	doCyborgVision();
	if(column == 1){
		turn(-90);
		forward(20.5);
		turn(90);
		findline();
	}
	else if(column == 2){
		findline();
	}
	else if(column == 3){
		turn(90);
		forward(20.5);
		turn(-90);
		findline();
	}
}
bool findline() {

	nMotorEncoder[rightDrive] = 0;	// reset encoder values on drive motors to zero
	nMotorEncoder[leftDrive]  = 0;

	float leftEncoder;
	float rightEncoder;
	float leftPower = 50.0;	// set speed of drive motors
	float rightPower = 50.0;

//	const float powerchange = 2;
	float totalTraveled = 0;
//	float distanceleft = (inches2encoder(distance2rack) - distancetraveled); //calculate the distance left to reach the rack

//	bool forward = true;
	bool maxdistance = false;

	ClearTimer(T1);

	// turn on drive motors to start moving forward
	motor[leftDrive]  = leftPower;
	motor[rightDrive] = rightPower;

	// do until a white line is hit or maximum distance is reached
	while((!linefound()) & (!maxdistance) & (time1[T1] < 2000))
	{
	  // get new encoder values and reset encoders to zero
		leftEncoder  = nMotorEncoder[leftDrive];
	  nMotorEncoder[leftDrive]  = 0;
	  rightEncoder = nMotorEncoder[rightDrive];
	  nMotorEncoder[rightDrive] = 0;

	  // get total distance traveled
	  totalTraveled += (leftEncoder + rightEncoder)/ 2.0;

	  // if total distance traveled is more than the distance to the rack, stop!!
	  if (totalTraveled > inches2encoder (dist2rack))
	  {
		  motor[leftDrive]  = 0;
		  motor[rightDrive] = 0;
		  maxdistance = true;
		}

		// make minor power changes to drive motors, based on which motor has traveled farther
	  if (leftEncoder > rightEncoder)
	  {
	    leftPower  -= POWERCHANGE;
	   	rightPower += POWERCHANGE;
	  }
	  else if(leftEncoder < rightEncoder) //same thing
	  {
	    leftPower  += POWERCHANGE;
	   	rightPower -= POWERCHANGE;
	  }

	  // adjust power on drive motors to account for variations
	  motor[leftDrive]  = leftPower;
	  motor[rightDrive] = rightPower;
	}
	motor[leftDrive]  = 0;
	motor[rightDrive] = 0;
	if (linefound())
	{
		return true;
	}
	else
		return false;
}

//check for any light sensor to detect a white line

bool linefound() {
	for(unsigned int i = 0; i < 6; i++)
	{
		if(LightSensors[i] < LINE_TOLERANCE)
			return true;
	}
	return false;
}
float inches2encoder(float distance)
{
	float encodervalue = 0;
  encodervalue = ((169.92*distance) - 55.875); //calculate the encoder value based on distance (in inches)
  return (encodervalue);
}
#endif
