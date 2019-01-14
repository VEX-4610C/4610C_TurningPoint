#include "okapi/api.hpp"

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

void opcontrol() {
	#include "literals.h"
	int reverseDrive = 1;
	while(true) {
		myChassis.tank(controller.getAnalog(ControllerAnalog::leftY) * reverseDrive,
             				controller.getAnalog(ControllerAnalog::rightY) * reverseDrive);
		if(brakeButton.changedToPressed()) {
			brakeState = !brakeState;
		}
		if(capGrabButton.changedToPressed()) {
			capGrabState = !capGrabState;
		}

		if(resetClaw.isPressed()) {
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
		if(reverseButton.changedToPressed())
			reverseDrive *= -1;

		if(liftUpButton.isPressed()) {
			liftMotor.moveVelocity(200);
		}
		else if(liftDownButton.isPressed()) {
			liftMotor.moveVelocity(-200);
		}
		else {
			liftMotor.moveVelocity(0);
		}

		flooperMotor.moveAbsolute(flooperState, 100);
		brake.set_value(brakeState);
		capGrab.set_value(capGrabState);
		pros::Task::delay(10);
	}

}
