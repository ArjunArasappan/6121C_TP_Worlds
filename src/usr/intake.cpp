#include "main.h"

Motor intakeMotor(PORT_INTAKE, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
Motor indexerMotor(PORT_INDEXER, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

const int RAKE_DOWN = -240;

bool rakeDown = false;

const int indexer_accel_step = 7;
const int indexer_deccel_step = 7;

static int indexerSlewSpeed = 0;

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
	indexerMotor.move_velocity(200);
}

void intakeWholeStop()
{
	indexerMotor.move(0);
	intakeMotor.move(0);
}

void intakeIn()
{
	intakeMotor.move_velocity(200);
}
void intakeOp(void *parameter)
{
	while (true)
	{
		if (!competition::is_autonomous())
		{
			lcd::print(1, "%.0f", indexerMotor.get_position());
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

			else
			{
				intakeMotor.move(0);
				adjusterStop();
			}
			//INDEXER
			if (master.get_digital(DIGITAL_L1))
			{
				if (rakeDown)
				{
					indexerMotor.tare_position();
					while (indexerMotor.get_position() < -RAKE_DOWN + 100)
					{
						indexerPower(127);
						pros::delay(20);
					}
					rakeDown = false;
				}
				else
				{
					indexerPower(127);
				}
			}

			else if (master.get_digital(DIGITAL_RIGHT))
			{
				indexerMotor.tare_position();
				while (indexerMotor.get_position() > RAKE_DOWN)
				{
					_indexerSlew(-127);
					pros::delay(20);
				}
				rakeDown = true;
				indexerMotor.move_velocity(0);
			}

			else
			{

				indexerMotor.move_velocity(0);
				indexerSlewSpeed = 0;
				indexerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
		}
		delay(20);
	}
}

// void indexerOp(void *paramter)
// {
// 	while (true)
// 	{
// 		if (!competition::is_autonomous())
// 		{
// 			if (master.get_digital(DIGITAL_L1))
// 			{
// 				if (rakeDown)
// 				{
// 					indexerMotor.tare_position();
// 					while (indexerMotor.get_position() < -RAKE_DOWN)
// 					{
// 						indexerPower(127);
// 						pros::delay(20);
// 					}
// 					rakeDown = false;
// 				}
// 				else
// 				{
// 					indexerPower(127);
// 				}
// 			}

// 			else if (master.get_digital(DIGITAL_RIGHT))
// 			{
// 				indexerMotor.tare_position();
// 				while (indexerMotor.get_position() > RAKE_DOWN)
// 				{
// 					_indexerSlew(-127);
// 					pros::delay(20);
// 				}
// 				rakeDown = true;
// 				indexerMotor.move_velocity(0);
// 			}

// 			else
// 			{

// 				indexerMotor.move_velocity(0);
// 				indexerSlewSpeed = 0;
// 				indexerMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
// 			}
// 		}
// 		delay(20);
// 	}
// }