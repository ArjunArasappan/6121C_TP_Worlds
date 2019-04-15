#include "main.h"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	// setFlywheelHigh();
	// intakeIn();
	// moveForward(33);
	// moveBackwardAsync(39);
	// delay(500);
	// intakeWholeStop();
	// chassisWaitUntilSettled();
	// turn(-85);
	// doubleShot();
	// intakeWholeStop();
	// moveForward(14);
	// turn(55);
	// moveForwardAsync(17);
	// delay(1600);
	// moveRakeDown();
	// intakeIn();
	// moveBackward(19);
	// moveForward(5);
	// moveBackward(5);
	// doubleShot();
	// intakeWholeStop();
	turn(90);
	turn(-90);
	delay(5000);
}