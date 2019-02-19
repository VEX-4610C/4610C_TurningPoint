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
#define BLUE -1

using namespace okapi;
extern pros::ADIGyro* gyro;

#include "constants.h"
#define GYRO_MULTIPLIER 9

template <typename T> T CLAMP(const T& value, const T& low, const T& high)
{
  return value < low ? low : (value > high ? high : value);
}

void parkFar(int multi) {
  #include "literals.h"

  liftPosController.flipDisable(true);
  liftMotor.moveVelocity(-200);
  pros::Task::delay(1200);
  liftMotor.moveVelocity(0);
  liftMotor.tarePosition();

  flooperMotor.moveVelocity(125);
  pros::Task::delay(350);
  flooperMotor.moveVelocity(0);
  pros::Task::delay(50);
  flooperMotor.tarePosition();

  liftMotor.moveVelocity(200);
  pros::Task::delay(500);
  liftMotor.moveVelocity(0);
  liftMotor.moveVelocity(-200);
  pros::Task::delay(300);
  liftMotor.moveVelocity(0);

  pros::Task::delay(500);

  myChassis.setMaxVelocity(125);
  myChassis.moveDistance(39_in);
  myChassis.turnAngle(90_deg * multi);

  liftPosController.setTarget(200);
  myChassis.setMaxVelocity(500);
  myChassis.tank(-1, -1);

  gyro->reset();
  while(abs(gyro->get_value()) < 80) {
  }
  while(abs(gyro->get_value()) > 10) {
  }

  myChassis.tank(0, 0);
}

void capAuto(int multi) {
  #include "literals.h"

  capGrab.set_value(0);
  liftPosController.flipDisable(true);
  liftMotor.moveVelocity(-200);
  pros::Task::delay(1200);
  liftMotor.moveVelocity(0);
  liftMotor.tarePosition();

  flooperMotor.moveVelocity(125);
  pros::Task::delay(350);
  flooperMotor.moveVelocity(0);
  pros::Task::delay(50);
  flooperMotor.tarePosition();



  myChassis.setMaxVelocity(125);

  myChassis.moveDistance(10_in);
  myChassis.turnAngle(-45_deg);
  myChassis.turnAngle(45_deg);
  myChassis.moveDistance(30_in);
  myChassis.turnAngle(-45_deg);
  myChassis.turnAngle(45_deg);
  myChassis.moveDistance(-10_in);
  myChassis.turnAngle(90_deg);

  myChassis.moveDistance(10_in);
  myChassis.turnAngle(-45_deg);


  flooperMotor.moveVelocity(125);
  pros::Task::delay(350);
  flooperMotor.moveVelocity(0);
  pros::Task::delay(50);
  flooperMotor.tarePosition();

  liftMotor.moveVelocity(-200);
  pros::Task::delay(1200);
  liftMotor.moveVelocity(0);
  liftMotor.tarePosition();


  pros::Task::delay(200);
  capGrab.set_value(1);
  myChassis.moveDistance(12_in);
  pros::Task::delay(300);



}
void pSkills() {
  #include "literals.h"

  myChassis.setMaxVelocity(100);
  myChassis.moveDistance(-24_in);
  pros::Task::delay(500);
  myChassis.turnAngle(85_deg);
  liftPosController.setTarget(150);
  myChassis.moveDistance(-12_in);
  myChassis.setMaxVelocity(125);
  myChassis.moveDistance(-57_in);
}
void autonomous() {
  capAuto(BLUE);
  //pSkills();

}
