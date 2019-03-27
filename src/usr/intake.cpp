#include "main.h"

Motor intakeMotor(PORT_INTAKE, false, AbstractMotor::gearset::green);
Motor indexerMotor(PORT_INDEXER, false, AbstractMotor::gearset::green);

void indexerPower(int power)
{
	indexerMotor.move(power);
}

void intakeOp()
{

	pros::lcd::print(1, "%.0f", indexerMotor.getPosition());

	if (master.getDigital(ControllerDigital::R1))
	{
		intakeMotor.move(127);
	}
	else if (master.getDigital(ControllerDigital::R2))
	{
		intakeMotor.move(-127);
	}
	else
	{
		intakeMotor.move(0);
	}
}

void indexerOp()
{
	if (master.getDigital(ControllerDigital::L1))
	{
		indexerPower(127);
	}

	else if (master.getDigital(ControllerDigital::L2))
	{
		indexerPower(-70);
	}

	else
	{
		indexerMotor.moveVelocity(0);
		indexerMotor.setBrakeMode(AbstractMotor::brakeMode::hold);
	}
}