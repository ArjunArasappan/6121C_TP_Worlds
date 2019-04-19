#include "main.h"

Motor intakeMotor(PORT_INTAKE, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
Motor indexerMotor(PORT_INDEXER, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

const int RAKE_DOWN = -140;

bool rakeDown = false;

const int indexer_accel_step = 256; //3
const int indexer_deccel_step = 256;

static int indexerSlewSpeed = 0;

double rakeError = 0;
double rakeTarget = 0;
double rake_kP = 1;
double rakePower = 0;
double rakePosition = 0;

void _indexerSlew(int target)
{
	int step;

	if (abs(indexerSlewSpeed) < abs(target))
		step = indexer_accel_step;
	else
		step = indexer_deccel_step;

	if (target > indexerSlewSpeed + step)
		indexerSlewSpeed += step;
	else if (target < indexerSlewSpeed - step)
		indexerSlewSpeed -= step;
	else
		indexerSlewSpeed = target;

	indexerMotor.move(indexerSlewSpeed);
}

void indexerPower(int power)
{
	indexerMotor.move(power);
}

void indexerIn()
{
	rakeDown = false;
	indexerMotor.move_velocity(200);
}

void intakeStop()
{
	intakeMotor.move(0);
}

void intakeWholeStop()
{
	indexerMotor.move(0);
	intakeMotor.move(0);
}

void intakeOut()
{
	intakeMotor.move_velocity(-200);
}

void moveRakeDown()
{
	indexerMotor.tare_position();
	while (indexerMotor.get_position() > RAKE_DOWN)
	{
		_indexerSlew(-127);
		pros::delay(20);
	}
	rakeDown = true;
	indexerMotor.move_velocity(0);
	indexerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
}

void moveRakeDownAuto()
{
	rakeDown = true;
}

void moveRakeUp()
{
	rakeDown = false;
	while (indexerMotor.get_position() < -RAKE_DOWN + 1000)
	{
		indexerPower(127);
		pros::delay(20);
	}
	indexerPower(0);
}

void intakeIn()
{
	intakeMotor.move_velocity(200);
}

void intakeInSlow()
{
	intakeMotor.move_velocity(100);
}

void intakeOutSlow()
{
	intakeMotor.move_velocity(-100);
}
void intakeOp(void *parameter)
{
	while (true)
	{
		lcd::print(3, "%.0f", indexerMotor.get_position());
		if (competition::is_autonomous())
		{
			if (rakeDown)
			{
				indexerMotor.move(-50);
			}
		}
		else
		{
			lcd::print(3, "%.0f", indexerMotor.get_position());
			//FRONT INTAKE and ADJUSTER
			if (master.get_digital(DIGITAL_R1))
			{
				intakeMotor.move(127);
			}
			else if (master.get_digital(DIGITAL_R2))
			{
				intakeMotor.move(-127);
			}
			else if (master.get_digital(DIGITAL_L2))
			{
				doubleShot();
			}
			else if (master.get_digital(DIGITAL_UP))
			{
				backDoubleShot();
			}

			else if (master.get_digital(DIGITAL_LEFT))
			{

				adjusterDown();
			}

			else if (master.get_digital(DIGITAL_Y))
			{
				adjusterUp();
			}

			else
			{
				intakeMotor.move(0);
				// intakeIn();
				adjusterStop();
			}
			//INDEXER
			if (master.get_digital(DIGITAL_L1))
			{
				if (rakeDown)
				{
					moveRakeUp();
				}
				else
				{
					indexerPower(127);
				}
			}

			else if (master.get_digital(DIGITAL_RIGHT))
			{
				moveRakeDown();
			}

			else
			{
				if (rakeDown)
				{
					indexerMotor.move(-30);
				}
				else
				{
					indexerMotor.move_velocity(0);
					indexerSlewSpeed = 0;
					indexerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
				}
				// indexerIn();
			}
		}
		delay(20);
	}
}
