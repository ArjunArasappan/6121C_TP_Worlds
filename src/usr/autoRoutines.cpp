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
	delay(600);
	intakeIn();
	setChassisMaxSpeed(40);
	moveBackwardAsync(18); //17 for rake still under cap
	delay(2500);
	setChassisMaxSpeed(127);
	moveForward(13);
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
	delay(600);
	intakeInSlow();
	chassisWaitUntilSettled();
	turn(-87);
	doubleShot();
	moveForwardAsync(6);
	intakeWholeStop();
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	leftMoveIndividual(10);
	intakeWholeStop();
	setChassisMaxSpeed(40);
	moveForwardAsync(18);
	delay(1500);
	setChassisMaxSpeed(127);
	getBallsOffCapFrontFlagAuto();
	intakeWholeStop();
	delay(300);
	leftMoveIndividual(1);
	doubleShot();
	indexerIn();
	intakeWholeStop();
	moveBackward(13);
	leftMoveIndividual(-11);
	moveForward(46);
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