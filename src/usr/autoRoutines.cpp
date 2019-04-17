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
	intakeIn();
	setChassisMaxSpeed(40);
	moveBackwardAsync(18);
	delay(600);
	setChassisMaxSpeed(127);
	delay(600);
	intakeInSlow();
	moveForwardAsync(13);
	delay(1000);
	intakeWholeStop();
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

	moveBackward(13);

	rightMoveIndividual(12.5);
	moveForward(30);
}

void redFront3FlagsPark()
{ //2nd full gray from table, 4th full tile from table
	setFlywheelHigh();
	intakeIn();
	moveForward(35);
	moveBackwardAsync(42);
	delay(1400);
	intakeWholeStop();
	chassisWaitUntilSettled();
	turn(-86);
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
	delay(1000);
	setChassisMaxSpeed(75);
	moveForward(40);
}

void redBack4Flags()
{ //3rd red from flags
	setFlywheelHigh();
	intakeIn();
	moveForward(34);
	intakeInSlow();
	moveBackward(9);
	intakeWholeStop();
	turn(-56);
	delay(3000);
	backDoubleShotAuto();
	intakeWholeStop();
	moveBackward(13);
	turn(-34);
	moveForward(16);
	moveRakeDownAuto();
	intakeIn();
	delay(1000);
	moveBackward(10);
	turn(15);
	indexerIn();
	delay(500);
	intakeWholeStop();
}