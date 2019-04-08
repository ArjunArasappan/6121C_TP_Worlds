#include "main.h"

Motor adjusterMotor(PORT_ADJUSTER, E_MOTOR_GEARSET_18, true);

void doubleShot()
{

	indexerIn();
	intakeIn();
	delay(100);
	adjusterUp();
	delay(500);
	adjusterDown();
	delay(60);
	intakeWholeStop();
	adjusterMotor.move_velocity(0);
}

void backDoubleShot()
{

	indexerIn();
	intakeIn();
	delay(100);
	intakeWholeStop();

	waitForFlywheelSettle();
	adjusterUp();
	indexerIn();
	intakeIn();
	delay(300);
	adjusterDown();
	delay(300);
	intakeWholeStop();
	adjusterMotor.move_velocity(0);
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

void adjusterOp(void *parameter)
{
	while (true)
	{
		if (!competition::is_autonomous())
		{
		}
		delay(20);
	}
}