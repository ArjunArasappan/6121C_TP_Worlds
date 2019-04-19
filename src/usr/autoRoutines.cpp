#include "main.h"

void getBallsOffCap()
{
	moveRakeDown();
	delay(600);
	intakeIn();
	moveBackwardAsync(20);
	delay(2000);
	moveForwardAsync(10);
	delay(900);
	moveBackwardAsync(10);
	delay(900);
	intakeWholeStop();
}

void getBallsOffCapFrontFlagAuto()
{
	moveRakeDown();
	delay(300);
	intakeIn();
	setChassisMaxSpeed(40);
	moveBackwardAsync(18);
	delay(600);
	setChassisMaxSpeed(127);
	intakeStop();
	delay(200);
	intakeIn();
	delay(400);
	moveForwardAsync(13);
	delay(1000);
	intakeInSlow();
}

void blueFront5Flags()
{
	//2nd full blue from table, 4th full tile from table
	setFlywheelHigh();
	intakeIn();
	moveForward(35);
	moveBackwardAsync(39.5);
	delay(900);
	intakeWholeStop();
	chassisWaitUntilSettled();
	turn(86);
	doubleShot();
	moveForwardAsync(7); //6
	intakeWholeStop();
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	rightMoveIndividual(10);
	intakeWholeStop();
	moveForwardAsync(17.5);
	delay(600);
	setChassisMaxSpeed(40);
	delay(700);
	setChassisMaxSpeed(127);
	getBallsOffCapFrontFlagAuto();
	intakeWholeStop();
	delay(300);
	rightMoveIndividual(2);
	doubleShot();
	intakeWholeStop();
	indexerIn();
	moveBackwardAsync(16);
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	leftMoveIndividual(11);
	moveForward(36);
}

void redFront5Flags()
{
	//2nd full gray from table, 4th full tile from table
	setFlywheelHigh();
	intakeIn();
	moveForward(35);
	moveBackwardAsync(42);
	delay(900);
	intakeWholeStop();
	chassisWaitUntilSettled();
	turn(-87.0);
	doubleShot();
	moveForwardAsync(6);
	intakeWholeStop();
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	leftMoveIndividual(10);
	intakeWholeStop();
	moveForwardAsync(18);
	delay(600);
	setChassisMaxSpeed(40);
	delay(700);
	setChassisMaxSpeed(127);
	getBallsOffCapFrontFlagAuto();
	intakeWholeStop();
	delay(300);
	leftMoveIndividual(2);
	doubleShot();
	intakeWholeStop();
	indexerIn();

	moveBackward(16);

	rightMoveIndividual(12);
	moveForward(30);
}

void redFront3FlagsPark()
{ //2nd full gray from table, 4th full tile from table
	setFlywheelHigh();
	intakeIn();
	moveForward(35);
	moveBackwardAsync(42);
	delay(900);
	intakeWholeStop();
	chassisWaitUntilSettled();
	turn(-87); //86
	doubleShot();
	flywheelStop();
	intakeWholeStop();
	rightMoveIndividual(5);
	intakeOut();
	moveForward(7);
	leftMoveIndividual(4.5);
	moveForward(39);
	intakeWholeStop();
	leftMoveIndividual(-3.5);
	moveBackwardAsync(67);
	delay(2200);
	turnAsync(107);
	moveRakeDown();
	delay(1000);
	setChassisMaxSpeed(75);
	moveForward(40);
	indexerIn();
}

void redBackSnipe(bool park)
{ //3rd red from flags
	setFlywheelHigh();
	intakeIn();
	moveForward(34);
	intakeInSlow();
	moveBackward(9);
	intakeWholeStop();
	turn(-58);
	delay(7000);
	backDoubleShotAuto();
	intakeWholeStop();
	flywheelStop();
	if (park)
	{
		rightMoveIndividual(15);
		delay(100);
		setChassisMaxSpeed(75);
		moveForward(31);
	}
}
