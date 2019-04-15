#ifndef _FLYWHEEL_HPP_
#define _FLYWHEEL_HPP_

void flywheelTask(void *);
void flywheelOp(void *);

void setFlywheelBackMid();
void setFlywheelHigh();

void backWaitForFlywheelSettle();
void flywheelPrintInfoToLCD();
#endif