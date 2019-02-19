#include "okapi/api.hpp"
#include <iostream>

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

using namespace okapi;

#include "constants.h"

void parkFar(int multi);

bool inScoreMode = 0;


int* flooperStatePointer;
Motor* flooperPointer;
Motor* liftPointer;
AsyncPosIntegratedController* liftControlPointer;
ChassisControllerIntegrated* chassisPointer;
pros::ADIDigitalOut* capGrabPointer;

void scoreCap(void *param) {
	pros::Task::delay(5);
	int currentState = 0;
	int lastScoreState = 0;
	while(1) {
		if(inScoreMode && lastScoreState == 0) {
			currentState = 0;
		}
		if(inScoreMode) {
			if(currentState == 0) {
				liftControlPointer->flipDisable(false);
				liftControlPointer->setTarget( LIFT_MIN_INDEX - 50 );
				if(liftControlPointer->isSettled()) {
					currentState = 1;
				}
			}
			else if(currentState == 1) {
				capGrabPointer->set_value(false);
				pros::Task::delay(150);
				currentState = 2;
			}
			else if(currentState == 3) {
				chassisPointer->moveDistance(-10_in);
				currentState = 4;
			}
			else if(currentState == 4 ) {
				if(*flooperStatePointer > 100) {
					*flooperStatePointer = 0;
				}
				currentState = 5;
			}
			else if(currentState == 6) {
				liftControlPointer->flipDisable(false);
				liftControlPointer->setTarget( 0 );
				if(liftControlPointer->isSettled()) {
					currentState = 0;
					inScoreMode = false;
				}
			}
		}
		lastScoreState = inScoreMode;
		pros::Task::delay(10);
	}
}

void opcontrol() {
	#include "literals.h"
	char* strPlay = (char*) malloc(64);
	double lastLift = 0;
	int manualLift = 1;
	flooperPointer = &flooperMotor;
	liftPointer = &liftMotor;
	liftControlPointer = &liftPosController;
	chassisPointer = &myChassis;
	flooperStatePointer = &flooperState;
	capGrabPointer = &capGrab;

	/* pros::Task score_task (scoreCap, (void*)0, TASK_PRIORITY_DEFAULT,
							TASK_STACK_DEPTH_DEFAULT, "SCORE");
	score_task.resume(); */


	int reverseDrive = 1;
	int needToFlipFlooper = 0;
	// liftMotor.moveVelocity(-200);
	pros::Task::delay(500);
	liftMotor.tarePosition();
	liftMotor.moveVelocity(0);
	while(true) {
		if(reverseDrive == -1) {
				myChassis.tank(-controller.getAnalog(ControllerAnalog::rightY),
             						-controller.getAnalog(ControllerAnalog::leftY));
		}
		else {
			myChassis.tank(controller.getAnalog(ControllerAnalog::leftY),
											controller.getAnalog(ControllerAnalog::rightY));
		}

		if(brakeButton.changedToPressed() && !inScoreMode) {
			brakeState = !brakeState;
		}
		if(capGrabButton.changedToPressed() && !inScoreMode) {
			capGrabState = !capGrabState;
		}

		if(resetClaw.isPressed() && !inScoreMode) {
			myChassis.tank(0,0);
			liftMotor.moveVelocity(0);
			flooperMotor.moveVelocity(125);
			pros::Task::delay(350);
			flooperMotor.moveVelocity(0);
			pros::Task::delay(50);
			flooperMotor.tarePosition();
		}

		if(flooperButton.changedToPressed()) {
				if(flooperState == 0) {
					flooperState = -190;
				}
				else {
					flooperState = 0;
				}
		}
		if(reverseButton.changedToPressed()) {
			reverseDrive *= -1;
		}


		if(liftLowButton.changedToPressed() && !inScoreMode) {
			manualIndex = 0;
			manualLift = 0;
			indexerState = false;
			liftPosController.flipDisable(false);
			liftPosController.setTarget(LIFT_LOW_HEIGHT);
		}
		else if(liftHighButton.changedToPressed() && !inScoreMode) {
			manualIndex = 0;
			manualLift = 0;
			indexerState = false;
			liftPosController.flipDisable(false);
			liftPosController.setTarget(LIFT_HIGH_HEIGHT);

		}
		else if(liftUpButton.isPressed() && !inScoreMode) {
			manualIndex = 0;
			liftPosController.flipDisable(true);
			liftMotor.moveVelocity(200);
			manualLift = 1;
		}
		else if(liftDownButton.isPressed() && !inScoreMode) {
			manualIndex = 0;
			if(liftMotor.getPosition() < (LIFT_MIN_INDEX + 250)) {
				indexerState = 1;
			}
			liftPosController.flipDisable(true);
			liftMotor.moveVelocity(-200);
			manualLift = 1;
		}
		else if(!inScoreMode && manualLift){
			liftPosController.flipDisable(false);
			liftPosController.setTarget(liftMotor.getPosition());
		}

		if(liftMotor.getPosition() > LIFT_MIN_INDEX && lastLift < LIFT_MIN_INDEX && manualIndex == 0 && !liftDownButton.isPressed()) {
			indexerState = 0;
		}
		else if(liftMotor.getPosition() < LIFT_MIN_INDEX && lastLift > LIFT_MIN_INDEX && manualIndex == 0) {
			indexerState = 1;
		}

		if(manualIndexButton.changedToPressed()) {
			indexerState = !indexerState;
			manualIndex = 1;
		}


		flooperMotor.moveAbsolute(flooperState, 100);
		capGrab.set_value(capGrabState);
		indexer.set_value(indexerState);

		sprintf(strPlay, "%d %9.7f", LIFT_MIN_INDEX, liftMotor.getPosition());
		pros::lcd::set_text(3, strPlay);
		lastLift = liftMotor.getPosition();
		pros::Task::delay(10);
	}

}
