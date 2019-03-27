#include "main.h"

Motor leftFront(PORT_LEFT_FRONT, false, AbstractMotor::gearset::green);
Motor leftBack(PORT_LEFT_BACK, false, AbstractMotor::gearset::green);

Motor rightFront(PORT_RIGHT_FRONT, true, AbstractMotor::gearset::green);
Motor rightBack(PORT_RIGHT_BACK, true, AbstractMotor::gearset::green);

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
	Controller master;
	float power = master.getAnalog(ControllerAnalog::leftY);
	float turn = master.getAnalog(ControllerAnalog::rightX);
	float leftPower = power + turn;
	float rightPower = power - turn;
	_left(leftPower * 127);
	_right(rightPower * 127);
}

void chassisTask(void *parameter)
{
	while (true)
	{
		_chassisArcade();
		pros::delay(20);
	}
}