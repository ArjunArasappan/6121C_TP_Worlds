#include "main.h"

Motor leftFront(PORT_LEFT_FRONT, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
Motor leftBack(PORT_LEFT_BACK, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

Motor rightFront(PORT_RIGHT_FRONT, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
Motor rightBack(PORT_RIGHT_BACK, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

const double vel_kP = 0;
const double vel_kI = 0;
const double vel_kD = 0;

template <typename T>
int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

bool chassisLock = false;

const double CHASSIS_DISTANCE_KP = .4; //.4
const double CHASSIS_DISTANCE_KI = 0;
const double CHASSIS_DISTANCE_KD = 3; //3

const int TURN_MAX_SPEED = 200;
const int TURN_ERROR_MIN = 10;

static int errorMax = 0;

const double CHASSIS_TURN_KP = .6; //1  .8
const double CHASSIS_TURN_KI = 0.00001;
const double CHASSIS_TURN_KD = 0; //2 2

static double P = 0;
static double I = 0;
static double D = 0;

const int MOVING_THRESH = 10;
const int IS_DRIVING_LIMIT = 2;

const double CHASSIS_SLANT_KP = 3.5; //2.5
const double CHASSIS_SLANT_KD = 1;

const double CHASSIS_DRIVE_ERROR_MIN = 28;

static double leftTarget = 0;
static double rightTarget = 0;

static bool isTurning = false;

static double difference = 0;

static int leftSpeed = 0;
static int rightSpeed = 0;

const int CHASSIS_ACCEL_STEP = 4;
const int CHASSIS_DECEL_STEP = 256; //no decel slew

const int CHASSIS_MAX_SPEED = 127;

const int CHASSIS_INTEGRAL_ERROR_BOUND = 300;
const double CHASSIS_INTEGRAL_CAP = 0 / CHASSIS_DISTANCE_KI;

const double WHEEL_DIAMETER = 4.125;
const double WHEELBASE_WIDTH = 10.75;

double leftPos = 0;
double leftError = 0;
double leftPrevError = 0;
double leftDerivative = 0;
double leftIntegral = 0;
double leftPower = 0;

double rightPos = 0;
double rightError = 0;
double rightPrevError = 0;
double rightDerivative = 0;
double rightIntegral = 0;
double rightPower = 0;

static double slantDifference = 0;
double slantModifier = 0;
double lastSlantDifference = 0;
double slantDerivative = 0;

void chassisInit()
{
	pros::motor_pid_s_t pid = pros::Motor::convert_pid(0, vel_kP, vel_kI, vel_kD);
	leftFront.set_vel_pid(pid);
	leftBack.set_vel_pid(pid);

	rightFront.set_vel_pid(pid);
	rightBack.set_vel_pid(pid);
}

double _getLeftPos()
{
	return leftFront.get_position();
}

double _getRightPos()
{
	return rightFront.get_position();
}

void _leftReset()
{
	leftFront.tare_position();
	leftBack.tare_position();
	leftSpeed = 0;
}

void _rightReset()
{
	rightFront.tare_position();
	rightBack.tare_position();
	rightSpeed = 0;
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
void _leftAuto(int power)
{
	if (false)
	{
		leftFront.move_velocity(power);
		leftBack.move_velocity(power);
	}
	else
	{
		_left(power);
	}
}

void _rightAuto(int power)
{
	if (false)
	{
		rightFront.move_velocity(power);
		rightBack.move_velocity(power);
	}
	else
	{
		_right(power);
	}
}

void _leftSlew(double leftTarget)
{
	int step;

	if (abs(leftSpeed) < abs(leftTarget))
		step = CHASSIS_ACCEL_STEP;
	else
		step = CHASSIS_DECEL_STEP;

	if (leftTarget > leftSpeed + step)
		leftSpeed += step;
	else if (leftTarget < leftSpeed - step)
		leftSpeed -= step;
	else
		leftSpeed = leftTarget;

	_leftAuto((int)leftSpeed);
}

void _rightSlew(double rightTarget)
{
	int step;

	if (abs(rightSpeed) < abs(rightTarget))
		step = CHASSIS_ACCEL_STEP;
	else
		step = CHASSIS_DECEL_STEP;

	if (rightTarget > rightSpeed + step)
		rightSpeed += step;
	else if (rightTarget < rightSpeed - step)
		rightSpeed -= step;
	else
		rightSpeed = rightTarget;

	_rightAuto((int)rightSpeed);
}

bool _isLeftDriving()
{
	if (isTurning)
	{
		return (fabs(leftError) > TURN_ERROR_MIN);
	}
	return (fabs(leftError) > CHASSIS_DRIVE_ERROR_MIN);
}

bool _isRightDriving()
{
	if (isTurning)
	{
		return (fabs(rightError) > TURN_ERROR_MIN);
	}

	return (fabs(rightError) > CHASSIS_DRIVE_ERROR_MIN);
}

void leftWaitUntilSettled()
{

	delay(300);
	while (_isLeftDriving())
	{
		delay(20);
	}
	pros::delay(250 + 400 * isTurning);
}

void rightWaitUntilSettled()
{
	delay(300);
	while (_isRightDriving())
	{
		delay(20);
	}
	pros::delay(250 + 400 * isTurning);
}

void chassisWaitUntilSettled()
{
	leftWaitUntilSettled();
	rightWaitUntilSettled();
}

double inchesToTicks(double inches)
{
	double revolutions = inches / (WHEEL_DIAMETER * PI);
	return revolutions * 360;
}

double degreesToTicks(double degrees)
{
	double distance_inches = (PI * WHEELBASE_WIDTH) / (360 / degrees);
	double revolutions = distance_inches / (WHEEL_DIAMETER * PI);
	return revolutions * 360;
}

void setChassisLock(bool lock)
{
	chassisLock = lock;
}

void leftMoveAsync(double iTarget)
{
	_leftReset();

	double target = iTarget;
	if (!isTurning)
	{
		target = inchesToTicks(iTarget);
	}
	leftTarget = target;
}

void leftMove(double iTarget)
{
	leftMoveAsync(iTarget);

	leftWaitUntilSettled();
}

void rightMoveAsync(double iTarget)
{
	_rightReset();
	double target = iTarget;
	if (!isTurning)
	{
		target = inchesToTicks(iTarget);
	}
	rightTarget = target;
}

void rightMove(double iTarget)
{
	rightMoveAsync(iTarget);
	rightWaitUntilSettled();
}

void moveForwardAsync(double distance_inches)
{
	isTurning = false;
	leftMoveAsync(distance_inches);
	rightMoveAsync(distance_inches);
}

void rightMoveIndividualAsync(double distance_inches)
{
}

void rightMoveIndividual(double distance_inches)
{
}

void leftMoveIndividualAsync(double distance_inches)
{
}

void leftMoveIndividual(double distance_inches)
{
}

void moveForward(double distance_inches)
{

	moveForwardAsync(distance_inches);
	chassisWaitUntilSettled();
}

void moveBackwardAsync(double distance_inches)
{
	moveForwardAsync(-distance_inches);
}

void moveBackward(double distance_inches)
{
	moveBackwardAsync(distance_inches);
	chassisWaitUntilSettled();
}

void turnAsync(double degrees)
{
	isTurning = true;
	leftMoveAsync(degreesToTicks(degrees));
	rightMoveAsync(-degreesToTicks(degrees));
}

void turn(double degrees)
{
	turnAsync(degrees);
	rightWaitUntilSettled();
}

void _chassisArcade()
{
	chassisLock = false;
	int power = master.get_analog(ANALOG_LEFT_Y);
	int turn = master.get_analog(ANALOG_RIGHT_X);
	int leftPower = power + turn;
	int rightPower = power - turn;
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
	_leftReset();
	_rightReset();
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
		else
		{

			if (isTurning)
			{
				P = CHASSIS_TURN_KP;
				I = CHASSIS_TURN_KI;
				D = CHASSIS_TURN_KD;
			}
			else
			{
				P = CHASSIS_DISTANCE_KP;
				I = CHASSIS_DISTANCE_KI;
				D = CHASSIS_DISTANCE_KD;
			}

			//LEFT CALCULATIONS
			leftPos = _getLeftPos();
			leftError = leftTarget - leftPos;
			leftDerivative = leftError - leftPrevError;
			leftPrevError = leftError;

			if (abs(leftError) < CHASSIS_INTEGRAL_ERROR_BOUND || abs(leftError) > 20)
			{
				leftIntegral += leftError;
			}
			else
			{
				leftIntegral = 0;
			}

			if (leftIntegral > CHASSIS_INTEGRAL_CAP)
			{
				leftIntegral = CHASSIS_INTEGRAL_CAP;
			}
			else if (leftIntegral < -CHASSIS_INTEGRAL_CAP)
			{
				leftIntegral = -CHASSIS_INTEGRAL_CAP;
			}

			leftIntegral *= sgn(leftError);

			leftPower = leftError * P + leftIntegral * I + leftDerivative * D;

			if (leftPower > 127)
			{
				leftPower = 127;
			}
			else if (leftPower < -127)
			{
				leftPower = -127;
			}

			//RIGHT CALCULATIONS
			rightPos = _getRightPos();
			rightError = rightTarget - rightPos;
			rightDerivative = rightError - rightPrevError;
			rightPrevError = rightError;

			if (abs(rightError) < CHASSIS_INTEGRAL_ERROR_BOUND || abs(rightError) > 20)
			{
				rightIntegral += rightError;
			}
			else
			{
				rightIntegral = 0;
			}

			if (rightIntegral > CHASSIS_INTEGRAL_CAP)
			{
				rightIntegral = CHASSIS_INTEGRAL_CAP;
			}
			else if (rightIntegral < -CHASSIS_INTEGRAL_CAP)
			{
				rightIntegral = -CHASSIS_INTEGRAL_CAP;
			}

			rightIntegral *= sgn(rightError);

			rightPower = rightError * P + rightIntegral * I + rightDerivative * D;

			if (rightPower > 127)
			{
				rightPower = 127;
			}
			else if (rightPower < -127)
			{
				rightPower = -127;
			}

			//OUTPUT

			if (isTurning)
			{
				if (rightPower > TURN_MAX_SPEED)
					rightPower = TURN_MAX_SPEED;
				else if (rightPower < -TURN_MAX_SPEED)
					rightPower = -TURN_MAX_SPEED;

				_leftSlew(-rightPower);
				_rightSlew(rightPower);
			}

			//SLANT
			else
			{
				slantDifference = leftPos - rightPos;
				slantDerivative = slantDifference - lastSlantDifference;
				slantDifference = lastSlantDifference;
				slantModifier = slantDifference * CHASSIS_SLANT_KP + slantDerivative * CHASSIS_SLANT_KD;

				leftPower -= slantModifier;
				rightPower += slantModifier;

				_leftSlew(leftPower);
				_rightSlew(rightPower);
			}
			// lcd::print(1, "%.2f %.2f %s", rightPower, rightError, strerror(errno));
		}
		lcd::print(1, "%.0f %.0f %.0f %.0f", leftFront.get_actual_velocity(), leftBack.get_actual_velocity(), rightFront.get_actual_velocity(), rightBack.get_actual_velocity());
		delay(20);
	}
}