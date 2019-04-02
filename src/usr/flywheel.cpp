#include "main.h"

Motor flywheelMotor(PORT_FLYWHEEL, E_MOTOR_GEARSET_06, false);

const float flywheelGain = 0.0075;

static float flywheelCurrentVelocity;
static float flywheelError;
static float flywheelPreviousError;
static float flywheelTargetVelocity;
static float flywheelOutput;
static float flywheelTBH;

bool flywheelEnabled = false;

static int flywheelSlewSpeed = 0;

int flywheelAccelStep = 4;
int flywheelDeccelStep = 256;

void _flywheelSlew(int target)
{
	int step;

	if (abs(flywheelSlewSpeed) < abs(target))
		step = flywheelAccelStep;
	else
		step = flywheelDeccelStep;

	if (target > flywheelSlewSpeed + step)
		flywheelSlewSpeed += step;
	else if (target < flywheelSlewSpeed - step)
		flywheelSlewSpeed -= step;
	else
		flywheelSlewSpeed = target;

	flywheelMotor.move(flywheelSlewSpeed);
}

void flywheelOp(void *parameter)
{
	while (true)
	{
		if (!competition::is_autonomous())
		{
			// lcd::print(1, "Error: %.0f Draw: %d", flywheelError, flywheelMotor.get_current_draw());
			if (master.get_digital(DIGITAL_X))
			{
				flywheelEnabled = true;
				flywheelTargetVelocity = 530;
			}
			else if (master.get_digital(DIGITAL_A))
			{
				flywheelEnabled = true;
				flywheelTargetVelocity = 300; //580
			}

			else if (master.get_digital(DIGITAL_B))

			{
				flywheelEnabled = false;
				flywheelSlewSpeed = 0;
			}
		}
		delay(20);
	}
}

void flywheelTask(void *parameter)
{

	flywheelCurrentVelocity = 0;
	flywheelError = 0;
	flywheelPreviousError = 0;
	flywheelTargetVelocity = 0;
	flywheelOutput = 0;
	flywheelTBH = 0;

	while (true)
	{
		if (flywheelEnabled)
		{
			flywheelCurrentVelocity = flywheelMotor.get_actual_velocity();
			flywheelError = flywheelTargetVelocity - flywheelCurrentVelocity;

			flywheelOutput += flywheelGain * flywheelError;

			if (signbit(flywheelError) != signbit(flywheelPreviousError))
			{							       // if zero crossing,
				flywheelOutput = 0.5 * (flywheelOutput + flywheelTBH); // then Take Back Half
				flywheelTBH = flywheelOutput;			       // update Take Back Half variable
				flywheelPreviousError = flywheelError;		       // and save the previous error
			}
			_flywheelSlew(flywheelOutput);
		}
		else
		{
			flywheelMotor.move(0);
		}
		delay(20);
	}
}