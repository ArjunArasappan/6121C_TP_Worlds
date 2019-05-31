#ifndef _INTAKE_HPP_
#define _INTAKE_HPP_

void intakeOp(void *);

void indexerIn();
void intakeIn();
void intakeStop();
void intakeInSlow();
void intakeMove(double target);
void intakeInMedium();
void intakeOutSlow();
void intakeOut();
void intakeWholeStop();

void moveRakeDown();
void moveRakeDownAuto();
void moveRakeUp();

#endif