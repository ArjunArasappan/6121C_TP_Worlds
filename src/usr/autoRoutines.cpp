#include "main.h"

void getBallsOffCap()
{
	moveRakeDownAuto();
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
	moveRakeDownAuto();
	delay(600);
	intakeInSlow();
	setChassisMaxSpeed(40);
	moveBackwardAsync(18); //17 for rake still under cap
	delay(2500);
	intakeIn();
	setChassisMaxSpeed(127);
	moveForward(10);
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
	moveForwardAsync(7);
	intakeWholeStop();
	delay(100);
	intakeOut();
	chassisWaitUntilSettled();
	leftMoveIndividual(10);
	intakeWholeStop();
	setChassisMaxSpeed(80);
	moveForwardAsync(18.75);
	delay(1500);
	setChassisMaxSpeed(127);
	getBallsOffCapFrontFlagAuto();
	intakeWholeStop();
	delay(300);
	leftMoveIndividual(-1);
	doubleShot();
	moveRakeUp();
	intakeWholeStop();
	moveBackward(12);
	leftMoveIndividual(-10);
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

	moveBackward(10);
	intakeOut();
	turn(108);
	moveForward(20);
	moveForward(5);
	intakeWholeStop();
	moveBackward(10);
	leftMoveIndividual(-26);
	moveForward(25);
	moveRakeDownAuto();
	delay(1000);
	intakeIn();
	moveBackward(15);
	turn(21);
	intakeIn();
	indexerIn();
	delay(500);
	intakeWholeStop();

	// turn(29);
	// moveBackwardAsync(38);
	// delay(2500);

	// turn(39);
	// moveForwardAsync(37);
	// delay(2000);
	// getBallsOffCap();
	// turnAsync(15);
	// delay(700);
	// moveBackwardAsync(10);
	// delay(700);
	// turn(-88);
	// moveForwardAsync(13);
	// delay(800);
	// backDoubleShotAuto();

	// moveBackward(27);
	// // delay(2000);
	// // turn(52);
	// leftMoveIndividual(14);
	// moveForwardAsync(20);
	// delay(1500);
	// getBallsOffCap();
	// turnAsync(15);
	// delay(700);
	// moveBackwardAsync(10);
	// delay(700);
	// turn(-84);
	// moveForwardAsync(13);
	// delay(800);
	// backDoubleShotAuto();
	// // turn(60);
	// // moveForward(23.5);
	// // turn(-75);
	// // moveForward(36);
}