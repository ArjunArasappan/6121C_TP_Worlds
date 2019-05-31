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
	delay(160);
	intakeWholeStop();
	intakeMove(-130);
	delay(550);
	indexerIn();
	intakeIn();
	delay(300);
	intakeWholeStop();
}

void backDoubleShotAuto()
{
	indexerIn();
	delay(85);
	intakeWholeStop();
	intakeMove(-130);
	// setFlywheelBackMid();
	delay(490);
	indexerIn();
	intakeIn();
	delay(800);
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
