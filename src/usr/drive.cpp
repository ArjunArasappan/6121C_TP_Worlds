#include "main.h"

Motor leftFront(PORT_LEFT_FRONT, MOTOR_GEARSET_18, false, MOTOR_ENCODER_ROTATIONS);
Motor leftBack(PORT_LEFT_BACK, MOTOR_GEARSET_18, false, MOTOR_ENCODER_ROTATIONS);

Motor rightFront(PORT_RIGHT_FRONT, MOTOR_GEARSET_18, true, MOTOR_ENCODER_ROTATIONS);
Motor rightBack(PORT_RIGHT_BACK, MOTOR_GEARSET_18, true, MOTOR_ENCODER_ROTATIONS);

bool chassisLock = false;

void setChassisLock(bool lock)
{
	chassisLock = lock;
}

void _left(int power)
{
	leftFront.move(power);
	leftBack.move(power);
}

void _right(int power)
{
	rightFront.move(power);
	rightBack.move(power);
}

void _chassisArcade()
{
	chassisLock = false;
	float power = master.get_analog(ANALOG_LEFT_Y);
	float turn = master.get_analog(ANALOG_RIGHT_X);
	float leftPower = power + turn;
	float rightPower = power - turn;
	_left(leftPower);
	_right(rightPower);
}

void _chassisLock()
{
	leftFront.move_velocity(0);
	leftBack.move_velocity(0);
	rightFront.move_velocity(0);
	rightBack.move_velocity(0);

	leftFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	leftBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	rightFront.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	rightBack.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void chassisTask(void *parameter)
{
	while (true)
	{
		if (!competition::is_autonomous())
		{

			if (chassisLock)
			{
				// _chassisLock();
			}
			else
			{
				_chassisArcade();
			}

			if (master.get_digital(DIGITAL_DOWN))
			{
				// _chassisLock();
			}
		}
		delay(20);
	}
}