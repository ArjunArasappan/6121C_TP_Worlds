#include "main.h"

Motor intakeMotor(PORT_INTAKE, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
Motor indexerMotor(PORT_INDEXER, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

void indexerPower(int power)
{
	indexerMotor.move(power);
}

void intakeOp(void *parameter)
{
	while (true)
	{
		if (!competition::is_autonomous())
		{
			if (master.get_digital(DIGITAL_R1))
			{
				intakeMotor.move(127);
			}
			else if (master.get_digital(DIGITAL_R2))
			{
				intakeMotor.move(-127);
			}
			else
			{
				intakeMotor.move(0);
			}
		}
		delay(20);
	}
}

void indexerOp(void*paramter)
{
	while (true)
	{
		if (!competition::is_autonomous())
		{
			if (master.get_digital(DIGITAL_L1))
			{
				indexerPower(127);
			}

			else if (master.get_digital(DIGITAL_L2))
			{
				indexerPower(-70);
			}

			else
			{
				indexerMotor.move_velocity(0);
				indexerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
		}
		delay(20);
	}
}