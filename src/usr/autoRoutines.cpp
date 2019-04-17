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

void redFront5FlagsBallOffPlatform()
{
	setFlywheelHigh();
	turn(35);
	moveForward(13);
	moveRakeDownAuto();
	delay(1300);
	intakeIn();
	moveBackward(18);
	intakeWholeStop();
	leftMoveIndividual(-8);
	intakeIn();
	turn(-80);
	doubleShot();
	intakeWholeStop();
	delay(100);
	intakeOut();
	moveForward(5);
	leftMoveIndividual(10);
	intakeWholeStop();
	moveForward(20); //17.75 //17.5
	// getBallsOffCap();
	getBallsOffCapFrontFlagAuto();
	intakeWholeStop();
	delay(300);
	// intakeIn();
	// moveForward(10);
	// leftMoveIndividual(3);
	doubleShot();
	intakeWholeStop();
	moveBackward(3);
	leftMoveIndividual(-13);
	moveRakeUp();
	moveForward(38);
}
void redFront5Flags()
{
	//2nd full gray from table
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