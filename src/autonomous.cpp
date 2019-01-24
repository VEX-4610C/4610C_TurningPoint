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
extern pros::ADIGyro gyro;

#include "constants.h"
#define GYRO_MULTIPLIER 9

template <typename T> T CLAMP(const T& value, const T& low, const T& high)
{
  return value < low ? low : (value > high ? high : value);
}

void gyroturn(pros::ADIGyro* gyro, okapi::ChassisControllerIntegrated* chassis, double ticks) {
  double inital_gyro = gyro->get_value();
  double final_gyro = inital_gyro + ticks;
  double gyro_kp = 0.25;
  double gyro_ki = 0.001;
  double gyro_kd = 0.1;

  bool settled = false;
  double loops_under_30 = 0;
  double error;
  double output;
  double last_error = gyro->get_value() - final_gyro;
  double delta_error;
  long long total_error;

  while(loops_under_30 < 25) {
    error = gyro->get_value() - final_gyro;
    delta_error = error - last_error;
    output = CLAMP(output, -1.0, 1.0);
    output = error*gyro_kp + total_error*gyro_ki + (delta_error)*gyro_kd;
    chassis->tank(output, -output);
    last_error = error;
    total_error += error;
    if(abs(error) < 30)
      loops_under_30 += 1;
    else
      loops_under_30 = 0;
    pros::Task::delay(20);
  }
}

int adjFlooper = 0;
int color = BLUE;
int runDrive = 1;


void closeBlue() {
  #include "literals.h"
  liftMotor.moveVelocity(200);
  pros::Task::delay(200);
  liftMotor.moveVelocity(0);
  pros::Task::delay(200);
  liftMotor.moveVelocity(-200);
  pros::Task::delay(200);
  liftMotor.moveVelocity(0);

  myChassis.moveDistance(42_in);
  pros::Task::delay(500);
  myChassis.moveDistance(-18_in);
  flooperMotor.moveVelocity(125);
  pros::Task::delay(350);
  flooperMotor.moveVelocity(0);
  pros::Task::delay(50);
  flooperMotor.tarePosition();
  flooperMotor.moveAbsolute(0, 100);

  myChassis.turnAngle(90_deg);

};

void parkFar() {
  #include "literals.h"

  liftPosController.flipDisable(true);
  liftMotor.tarePosition();
  liftMotor.moveVelocity(-200);
  pros::Task::delay(1000);
  liftMotor.moveVelocity(0);

  flooperMotor.moveVelocity(125);
  pros::Task::delay(350);
  flooperMotor.moveVelocity(0);
  pros::Task::delay(50);
  flooperMotor.tarePosition();

  pros::Task::delay(500);

  myChassis.setMaxVelocity(125);
  myChassis.moveDistance(38_in);
  myChassis.turnAngle(90_deg);
  myChassis.setMaxVelocity(200);
  myChassis.moveDistance(-36_in);
}
void farAutoA() {
  #include "literals.h"

  // BRING FLOOPER DOWN
  myChassis.setMaxVelocity(125);
  myChassis.moveDistance(36_in);
  myChassis.turnAngle(63_deg);
  myChassis.moveDistance(30_in);

  capGrab.set_value(true);
  pros::Task::delay(100);
  flooperMotor.moveAbsolute(190, 150);
  capGrab.set_value(false);
  myChassis.moveDistance(-30_in);
  myChassis.turnAngle(37_deg);

  myChassis.setMaxVelocity(200);
  myChassis.moveDistance(-31_in);
}
void farAutoB() {
  #include "literals.h"

  liftPosController.flipDisable(true);
  liftMotor.moveAbsolute(-200, 200);
  pros::Task::delay(500);
  liftMotor.moveAbsolute(0, 200);

  flooperMotor.moveVelocity(125);
  pros::Task::delay(350);
  flooperMotor.moveVelocity(0);
  pros::Task::delay(50);
  flooperMotor.tarePosition();
  flooperMotor.moveAbsolute(0, 100);

  myChassis.setMaxVelocity(125);
  myChassis.moveDistance(58_in);

  capGrab.set_value(true);
  pros::Task::delay(100);

  myChassis.moveDistance(-28_in);
  liftPosController.setTarget(LIFT_LOW_HEIGHT);
  myChassis.turnAngle(-127_deg);
  flooperMotor.moveAbsolute(190, 150);

  indexer.set_value(true);
  myChassis.moveDistance(10_in);
  liftPosController.setTarget(LIFT_LOW_HEIGHT - 50);

  capGrab.set_value(false);
  pros::Task::delay(100);
  myChassis.moveDistance(-10_in);
  liftPosController.setTarget(0);
}

void autonomous() {
  /*#include "literals.h"
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
  flooperMotor.tarePosition();*/
  parkFar();

}
