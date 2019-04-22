#include "main.h"

Motor adjusterMotor(PORT_ADJUSTER, E_MOTOR_GEARSET_18, true);

void doubleShot()
{

	adjusterMotor.tare_position();
	indexerIn();
	intakeIn();
	delay(40);
	adjusterUp();
	delay(280);
	adjusterMotor.move_absolute(0, 200);
	delay(60);
	// intakeWholeStop();
	adjusterMotor.move_velocity(0);
}

void backDoubleShot()
{
	indexerIn();
	intakeIn();
	delay(160);
	intakeWholeStop();
	// setFlywheelBackMid();
	delay(550); //700
	indexerIn();
	intakeIn();
	delay(300);
	intakeWholeStop();
	// setFlywheelHigh();
}

void backDoubleShotAuto()
{
	indexerIn();
	intakeIn();
	delay(100);
	intakeWholeStop();
	setFlywheelBackMid();
	delay(700);
	indexerIn();
	intakeIn();
	delay(500);
	intakeWholeStop();
	setFlywheelHigh();
}

void adjusterUp()
{
	adjusterMotor.move_velocity(200);
}

void adjusterDown()
{
	adjusterMotor.move_velocity(-200);
}

void adjusterStop()
{
	adjusterMotor.move_velocity(0);
}
