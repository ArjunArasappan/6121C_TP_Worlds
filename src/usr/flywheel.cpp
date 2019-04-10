#include "main.h"

Motor flywheelMotor(PORT_FLYWHEEL, E_MOTOR_GEARSET_06, false);

const float flywheelGain = 0.01;

const int FLYWHEEL_HIGH = 595; //560

bool flywheelEnabled = false;

static int flywheelSlewSpeed = 0;

int flywheelAccelStep = 4;
int flywheelDeccelStep = 256;

template <typename T>
int sgn(T val)
{
	return (T(0) < val) - (val < T(0));
}

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

// Update inteval (in mS) for the flywheel control loop
#define FW_LOOP_SPEED 25
// Maximum power we want to send to the flywheel motors
#define FW_MAX_POWER 127

// Structure to gather all the flywheel ralated data
typedef struct _fw_controller
{
	long counter; ///< loop counter used for debug
	// encoder tick per revolution
	float ticks_per_rev; ///< encoder ticks per revolution

	// velocity measurement
	float v_current; ///< current velocity in rpm
	long v_time;     ///< Time of last velocity calculation
	// TBH control algorithm variables
	long target;	 ///< target velocity
	long current;	///< current velocity
	long last;	   ///< last velocity
	float error;	 ///< error between actual and target velocities
	float last_error;    ///< error last time update called
	float gain;	  ///< gain
	float drive;	 ///< final drive out of TBH (0.0 to 1.0)
	float drive_at_zero; ///< drive at last zero crossing
	long first_cross;    ///< flag indicating first zero crossing
	// final motor drive
	long motor_drive; ///< final motor control value
} fw_controller;
// Make the controller global for easy debugging
static fw_controller flywheel;
/*-----------------------------------------------------------------------------*/
/** @brief      Set the flywheen motors                                        */
/** @param[in]  value motor control value                                      */
/*-----------------------------------------------------------------------------*/
void FwMotorSet(int value)
{
	_flywheelSlew(value);
}

/*-----------------------------------------------------------------------------*/
/** @brief      Set the controller position                                    */
/** @param[in]  fw pointer to flywheel controller structure                    */
/** @param[in]  desired velocity                                               */
/** @param[in]  predicted_drive estimated open loop motor drive                */
/*-----------------------------------------------------------------------------*/
void FwVelocitySet(fw_controller *fw, int velocity)
{
	// set target velocity (motor rpm)
	fw->target = velocity;
	// Set error so zero crossing is correctly detected
	fw->error = fw->target - fw->current;
	fw->last_error = fw->error;

	// Set flag to detect first zero crossing
	fw->first_cross = 1;
	// clear tbh variable
	fw->drive_at_zero = 0;
}
/*-----------------------------------------------------------------------------*/
/** @brief      Calculate the current flywheel motor velocity                  */
/** @param[in]  fw pointer to flywheel controller structure                    */
/*-----------------------------------------------------------------------------*/
void FwCalculateSpeed(fw_controller *fw)
{
	int delta_ms;
	int delta_enc;
	// This is just used so we don't need to know how often we are called
	// how many mS since we were last here
	delta_ms = millis() - fw->v_time;
	fw->v_time = millis();
	fw->v_current = flywheelMotor.get_actual_velocity();
}
/*-----------------------------------------------------------------------------*/
/** @brief      Update the velocity tbh controller variables                   */
/** @param[in]  fw pointer to flywheel controller structure                    */
/*-----------------------------------------------------------------------------*/
void FwControlUpdateVelocityTbh(fw_controller *fw)
{
	// calculate error in velocity
	// target is desired velocity
	// current is measured velocity
	fw->error = fw->target - fw->current;
	// Use Kp as gain
	fw->drive = fw->drive + (fw->error * fw->gain);
	// Clip - we are only going forwards
	if (fw->drive > 1)
		fw->drive = 1;
	if (fw->drive < 0)
		fw->drive = 0;
	// Check for zero crossing
	if (sgn(fw->error) != sgn(fw->last_error))
	{
		// First zero crossing after a new set velocity command
		if (fw->first_cross)
		{
			fw->drive = 0.5 * (fw->drive + fw->drive);
			fw->first_cross = 0;
		}
		else
		{
			fw->drive = 0.5 * (fw->drive + fw->drive_at_zero);
		}
		// Save this drive value in the "tbh" variable
		fw->drive_at_zero = fw->drive;
	}
	// Save last error
	fw->last_error = fw->error;
}

void flywheelOp(void *parameter)
{
	while (true)
	{
		printf("%.0f %.0f %d\n\n", flywheelMotor.get_actual_velocity(), flywheelMotor.get_power(), flywheel.motor_drive);
		if (!competition::is_autonomous())
		{

			if (master.get_digital(DIGITAL_X))
			{
				flywheelEnabled = true;
				FwVelocitySet(&flywheel, FLYWHEEL_HIGH);
			}
			else if (master.get_digital(DIGITAL_A))
			{
				flywheelEnabled = true;
				FwVelocitySet(&flywheel, 600);
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

/*-----------------------------------------------------------------------------*/
/** @brief     Task to control the velocity of the flywheel                    */
/*-----------------------------------------------------------------------------*/

void flywheelTask(void *parameter)
{
	fw_controller *fw = &flywheel;
	// Set the gain
	fw->gain = 0.0003;

	fw->v_time = millis();
	while (true)
	{
		if (flywheelEnabled)
		{ // debug counter
			fw->counter++;
			// Calculate velocity
			FwCalculateSpeed(fw);
			// Set current speed for the tbh calculation code
			fw->current = fw->v_current;
			// Do the velocity TBH calculations
			FwControlUpdateVelocityTbh(fw);
			// Scale drive into the range the motors need
			fw->motor_drive = (fw->drive * FW_MAX_POWER) + 0.5;
			// Final Limit of motor values - don't really need this
			if (fw->motor_drive > 127)
				fw->motor_drive = 127;
			if (fw->motor_drive < -127)
				fw->motor_drive = -127;
			// and finally set the motor control value
			FwMotorSet(fw->motor_drive);
			// Run at somewhere between 20 and 50mS
		}
		else
		{
			flywheelMotor.move(0);
		}
		delay(FW_LOOP_SPEED);
	}
}

void waitForFlywheelSettle()
{
	while (sgn(flywheel.error) == sgn(flywheel.last_error))
	{
		delay(20);
	}
}