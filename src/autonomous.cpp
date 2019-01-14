#include "main.h"
#include "okapi/api.hpp"

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

#define RED 1
#define BLUE 0

using namespace okapi;

int adjFlooper = 0;
int color = BLUE;
int runDrive = 1;

void autonomous() {
  #include "literals.h"
  if(color == 0 && runDrive) {
    // fire then release flooper
    liftMotor.moveVelocity(200);
    pros::Task::delay(400);
    liftMotor.moveVelocity(0);
    pros::Task::delay(200);
    liftMotor.moveVelocity(-200);
    pros::Task::delay(500);
    liftMotor.moveVelocity(0);
    myChassis.moveDistance(30_in);
    myChassis.tank(1, 1);
    pros::Task::delay(350);
    myChassis.tank(-1, -1);
    pros::Task::delay(350);
    myChassis.tank(0, 0);
  }
  else if (runDrive) {
    // move drive to align, fire, release flooper
    liftMotor.moveVelocity(200);
    pros::Task::delay(400);
    liftMotor.moveVelocity(0);
    pros::Task::delay(200);
    liftMotor.moveVelocity(-200);
    pros::Task::delay(500);
    liftMotor.moveVelocity(0);
    myChassis.moveDistance(-20_in);
    myChassis.tank(1, 1);
    pros::Task::delay(350);
    myChassis.tank(-1, -1);
    pros::Task::delay(350);
    myChassis.tank(0, 0);
  }
  else {
    myChassis.tank(1, 1);
    pros::Task::delay(800);
    myChassis.tank(-1, -1);
    pros::Task::delay(350);
    myChassis.tank(0, 0);
  }

  // find adj for flooper
  flooperMotor.moveVelocity(125);
  pros::Task::delay(350);
  flooperMotor.moveVelocity(0);
  pros::Task::delay(50);
  flooperMotor.tarePosition();

}
