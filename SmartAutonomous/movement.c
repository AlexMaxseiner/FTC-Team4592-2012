#ifndef MOVEMENT_C
#define MOVEMENT_C

void forward(float distance) {   //forward function to pass in a length in inches and then it goes that for
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
	    {
	      //while all that is not less than the encoder target
	      totalTraveled += (abs(nMotorEncoder[leftDrive]) + abs(nMotorEncoder[rightDrive]))/ 2.0;// add the aveage of the encoders
	      break;//exit
	    }
	  }
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}
void turn(float degrees) {

//	const float fullturn = 10498;	//encoder value for 360 degrees

	float requestedturn = abs (degrees*(10300/360.0));
	bool leftturn = false;
	bool rightturn = false;

	nMotorEncoder[leftDrive] = 0;
	nMotorEncoder[rightDrive] = 0;

	// determine if this is a right turn, left turn, or no turn
	if (degrees > 0)
	{
		rightturn = true;
	}
	else if (degrees < 0)
	{
		leftturn = true;
	}

	while (abs(nMotorEncoder[leftDrive]) < requestedturn && abs(nMotorEncoder[rightDrive]) < requestedturn)
	{
		if (rightturn)
		{
			motor[leftDrive] = 100;
			motor[rightDrive] = -100;
		}
		else if (leftturn)
		{
			motor[leftDrive] = -100;
			motor[rightDrive] = 100;
		}
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
	leftturn = false;
	rightturn = false;
}

long long leftVal1298870 = 0;
long long rightVal1298870 = 0;
long long totLe1298870 = 0;
long long totRi1298870 = 0;
void backward(float distance) {   //forward function to pass in a length in inches and then it goes that for
	const float CHANGE = 2;
	float totalTraveled = 0;
	float encoderTarget = (169.92*distance) - 55.875; //calculate the encoder target
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive]  = 0;
	float leftEncoder;
	float rightEncoder;
	float leftPower  = -50;
	float rightPower = -50;
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
	    {
	      //while all that is not less than the encoder target
	      totalTraveled += (abs(nMotorEncoder[leftDrive]) + abs(nMotorEncoder[rightDrive]))/ 2.0;// add the aveage of the encoders
	      break;//exit
	    }
	  }
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
}
#endif
