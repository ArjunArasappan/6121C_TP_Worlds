#ifndef _DRIVE_HPP_
#define _DRIVE_HPP_

void chassisTask(void *);

void setChassisLock(bool lock);

void setChassisMaxSpeed(double speed);

void leftWaitUntilSettled();
void rightWaitUntilSettled();

void chassisWaitUntilSettled();

void moveForward(double distance_inches);
void moveForwardAsync(double distance_inches);
void moveBackward(double distance_inches);
void moveBackwardAsync(double distance_inches);

void leftMove(double iTarget);
void leftMoveAsync(double iTarget);
void rightMove(double iTarget);
void rightMoveAsync(double iTarget);

void rightMoveIndividualAsync(double distance_inches);
void rightMoveIndividual(double distance_inches);
void leftMoveIndividualAsync(double distance_inches);
void leftMoveIndividual(double distance_inches);

void turn(double degrees);
void turnAsync(double degrees);

#endif