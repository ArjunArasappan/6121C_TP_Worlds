#include "main.h"

Motor leftFront(PORT_LEFT_FRONT, MOTOR_GEARSET_18, false, MOTOR_ENCODER_ROTATIONS);
Motor leftBack(PORT_LEFT_BACK, MOTOR_GEARSET_18, false, MOTOR_ENCODER_ROTATIONS);

Motor rightFront(PORT_RIGHT_FRONT, MOTOR_GEARSET_18, true, MOTOR_ENCODER_ROTATIONS);
Motor rightBack(PORT_RIGHT_BACK, MOTOR_GEARSET_18, true, MOTOR_ENCODER_ROTATIONS);

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
	float power = master.get_analog(ANALOG_LEFT_Y);
	float turn = master.get_analog(ANALOG_RIGHT_X);
	float leftPower = power + turn;
	float rightPower = power - turn;
	_left(leftPower);
	_right(rightPower);
}

void chassisTask(void *parameter)
{
	while (true)
	{
		if (!competition::is_autonomous())
		{

			_chassisArcade();
		}
		delay(20);
	}
}