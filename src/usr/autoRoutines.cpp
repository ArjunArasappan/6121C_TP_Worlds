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
	setChassisAccelStep(256);
	moveBackwardAsync(18);
	delay(700);
	setChassisMaxSpeed(127);
	delay(600);
	setChassisAccelStep(4);
	moveForward(16);
}

void blueFront5Flags()
{
	//2nd full blue from table, 4th full tile from table
	setFlywheelHigh();
	moveForwardAsync(34);
	delay(1800);
	intakeIn();
	moveBackwardAsync(39);
	delay(900);
	intakeWholeStop();
	chassisWaitUntilSettled();
	turn(88);
	doubleShot();
	moveForwardAsync(8); //7
	intakeWholeStop();
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	rightMoveIndividual(10);
	intakeWholeStop();
	moveForwardAsync(16);
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
	moveBackwardAsync(22);
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	leftMoveIndividual(10);
	moveForward(40);
}

void redFront5Flags()
{
	//2nd full gray from table, 4th full tile from table
	setFlywheelHigh();
	moveForward(35);
	intakeIn();
	moveBackwardAsync(42);
	delay(900);
	intakeWholeStop();
	chassisWaitUntilSettled();
	turn(-87);
	moveForwardAsync(6);
	doubleShot();
	intakeWholeStop();
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	leftMoveIndividual(10);
	intakeWholeStop();
	moveForwardAsync(18.7);
	delay(600);
	setChassisMaxSpeed(40);
	delay(600);
	setChassisMaxSpeed(127);
	getBallsOffCapFrontFlagAuto();
	leftMoveIndividual(4);
	doubleShot();
	intakeWholeStop();
	indexerIn();

	moveBackward(13);
	intakeWholeStop();
	rightMoveIndividual(14);
	moveForward(30);
	// moveBackward(16);

	// rightMoveIndividual(12);
	// moveForward(30);
}

void blueFront3FlagsPark()
{ //2nd full blue from table, 4th full tile from table
	setFlywheelHigh();
	moveForward(35);
	intakeIn();
	moveBackwardAsync(39.5);
	delay(900);
	intakeWholeStop();
	chassisWaitUntilSettled();
	turn(86);
	doubleShot();
	flywheelStop();
	intakeWholeStop();
	leftMoveIndividual(7);
	intakeOut();
	moveForward(15);
	rightMoveIndividual(4.5);
	moveForward(37);
	intakeWholeStop();
	rightMoveIndividual(-2.5);
	moveBackwardAsync(74);
	delay(2200);
	turnAsync(-101);
	moveRakeDown();
	delay(1000);
	setChassisMaxSpeed(75);
	moveForward(40);
	indexerIn();
}

void redFront3FlagsPark()
{ //2nd full gray from table, 4th full tile from table
	setFlywheelHigh();
	moveForward(35);
	intakeIn();
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
{ //2nd full red from flags, 4th full tab from flags
	setFlywheelHigh();
	moveForward(35);
	intakeIn();
	moveBackward(11);
	intakeWholeStop();
	turn(-56);
	if (park)
	{
		delay(6500);
	}
	else
	{
		delay(3000);
	}
	backDoubleShotAuto();
	intakeWholeStop();
	flywheelStop();
	if (park)
	{
		rightMoveIndividual(15);
		delay(100);
		setChassisMaxSpeed(75);
		moveForward(31);
		return;
	}
	moveBackward(10);
	turn(100);
	intakeOut();
	moveForward(22);
	moveForward(7);
}

void blueBackSnipe(bool park)

{ //2nd full gray from flags, 4th full tab from flags
	setFlywheelHigh();
	moveForward(35);
	intakeIn();
	moveBackward(11);
	intakeWholeStop();
	turn(56);
	if (park)
	{
		delay(6500);
	}
	else
	{
		delay(3000);
	}

	backDoubleShotAuto();
	intakeWholeStop();
	flywheelStop();
	if (park)
	{
		moveRakeDown();
		leftMoveIndividual(15);
		delay(100);
		setChassisMaxSpeed(75);
		moveForward(36);
		return;
	}
	moveBackward(10);
	turn(-100);
	intakeOut();
	moveForward(22);
	moveForward(7);
}
