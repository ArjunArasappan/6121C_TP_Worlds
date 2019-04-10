#include "main.h"

Motor adjusterMotor(PORT_ADJUSTER, E_MOTOR_GEARSET_18, true);

void doubleShot()
{
	setChassisLock(true);
	adjusterMotor.tare_position();
	indexerIn();
	intakeIn();
	delay(95);
	adjusterUp();
	delay(300);
	adjusterMotor.move_absolute(0, 200);
	delay(60);
	intakeWholeStop();
	adjusterMotor.move_velocity(0);
	setChassisLock(false);
}

void backDoubleShot()
{
	setChassisLock(true);
	indexerIn();
	intakeIn();
	delay(160);
	intakeWholeStop();
	adjusterUp();
	delay(1500);
	indexerIn();
	intakeIn();
	delay(200);
	adjusterDown();
	delay(300);
	intakeWholeStop();
	adjusterMotor.move_velocity(0);
	setChassisLock(false);
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