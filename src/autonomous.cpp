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
extern pros::ADIGyro* turnGyro;

#include "constants.h"
#define GYRO_MULTIPLIER 9

template <typename T> T CLAMP(const T& value, const T& low, const T& high)
{
  return value < low ? low : (value > high ? high : value);
}

void parkFar(int multi) {
  #include "literals.h"

  capGrab.set_value(0);
  indexer.set_value(1);

  liftPosController.flipDisable(true);
  liftMotor.moveVelocity(-200);
  pros::Task::delay(1200);
  liftMotor.moveVelocity(0);
  liftMotor.tarePosition();
  liftMotor.moveAbsolute(0, 25);

  flooperMotor.moveVelocity(125);
  pros::Task::delay(400);
  flooperMotor.moveVelocity(0);
  flooperMotor.tarePosition();
  pros::Task::delay(50);
  flooperMotor.moveAbsolute(0, 25);




  myChassis.setMaxVelocity(125);
  capGrab.set_value(1);
  myChassis.moveDistance(34_in);
  myChassis.turnAngle(90_deg * multi);
  capGrab.set_value(0);

  liftPosController.setTarget(500);
  myChassis.setMaxVelocity(500);
  myChassis.tank(-1, -1);

  gyro->reset();
  while(abs(gyro->get_value()) < 80) {
  }
  while(abs(gyro->get_value()) > 10) {
  }
  pros::Task::delay(125);
  myChassis.tank(0, 0);
}

void capAutoBlue() {
  int multi = -1;
  #include "literals.h"

  capGrab.set_value(0);
  indexer.set_value(1);

  liftPosController.flipDisable(true);
  liftMotor.moveVelocity(-200);
  pros::Task::delay(1200);
  liftMotor.moveVelocity(0);
  liftMotor.tarePosition();
  liftMotor.moveAbsolute(0, 25);

  flooperMotor.moveVelocity(125);
  pros::Task::delay(400);
  flooperMotor.moveVelocity(0);
  flooperMotor.tarePosition();
  pros::Task::delay(50);
  flooperMotor.moveAbsolute(0, 25);




  myChassis.setMaxVelocity(150);
  myChassis.moveDistance(35_in);
  myChassis.turnAngle(75_deg * multi);


  myChassis.setMaxVelocity(100);
  myChassis.moveDistance(8_in);
  myChassis.turnAngle(-25_deg * multi);

  myChassis.setMaxVelocity(60);
  myChassis.moveDistance(6_in);
  capGrab.set_value(1);
  pros::Task::delay(100);
  liftPosController.setTarget(250);


  myChassis.setMaxVelocity(135);
  myChassis.moveDistance(-6_in);
  int gyroAdj = (turnGyro->get_value() - 300*multi) / 20;
  myChassis.turnAngle((135) * multi * degree);
  myChassis.moveDistance(25_in);
  liftPosController.flipDisable(false);
  liftPosController.setTarget(1450);
  while(liftMotor.getPosition() < 500);
  flooperMotor.moveAbsolute(-190, 100);
  while(liftMotor.getPosition() < 1350);
  indexer.set_value(0);
  myChassis.setMaxVelocity(80);
  pros::Task::delay(100);

  myChassis.moveDistance(12_in);
  liftPosController.flipDisable(true);
  indexer.set_value(1);
  liftMotor.moveVelocity(-150);
  pros::Task::delay(500);
  liftMotor.moveVelocity(0);
  capGrab.set_value(0);
  pros::Task::delay(350);
  myChassis.moveDistance(-10_in);




  while(1);



}
void capAutoRed() {
  int multi = 1;
  #include "literals.h"

  capGrab.set_value(0);
  indexer.set_value(1);

  liftPosController.flipDisable(true);
  liftMotor.moveVelocity(-200);
  pros::Task::delay(1200);
  liftMotor.moveVelocity(0);
  liftMotor.tarePosition();
  liftMotor.moveAbsolute(0, 25);

  flooperMotor.moveVelocity(125);
  pros::Task::delay(400);
  flooperMotor.moveVelocity(0);
  flooperMotor.tarePosition();
  pros::Task::delay(50);
  flooperMotor.moveAbsolute(0, 25);




  myChassis.setMaxVelocity(150);
  capGrab.set_value(1);
  myChassis.moveDistance(32_in);
  myChassis.turnAngle(75_deg * multi);
  capGrab.set_value(0);

  pros::Task::delay(350);

  myChassis.setMaxVelocity(100);
  myChassis.moveDistance(10_in);
  myChassis.turnAngle(-25_deg * multi);

  myChassis.setMaxVelocity(60);
  myChassis.moveDistance(8_in);
  capGrab.set_value(1);
  pros::Task::delay(100);
  liftPosController.setTarget(250);


  myChassis.setMaxVelocity(135);
  myChassis.moveDistance(-10_in);
  int gyroAdj = (turnGyro->get_value() - 300*multi) / 20;
  myChassis.turnAngle((124) * multi * degree);
  myChassis.moveDistance(24_in);
  liftPosController.flipDisable(false);
  liftPosController.setTarget(1450);
  while(liftMotor.getPosition() < 500);
  flooperMotor.moveAbsolute(-190, 100);
  while(liftMotor.getPosition() < 1350);
  indexer.set_value(0);
  myChassis.setMaxVelocity(80);
  pros::Task::delay(100);

  myChassis.moveDistance(13_in);
  liftPosController.flipDisable(true);
  indexer.set_value(1);
  liftMotor.moveVelocity(-150);
  pros::Task::delay(500);
  liftMotor.moveVelocity(0);
  capGrab.set_value(0);
  pros::Task::delay(350);
  myChassis.moveDistance(-10_in);




  while(1);




}
void capAuto(int multi) {
  if(multi == RED)
    capAutoRed();
  else if(multi == BLUE)
    capAutoBlue();
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

  gyro->reset();
  myChassis.tank(-1, -1);
  while(abs(gyro->get_value()) < 80) {
  }
  while(abs(gyro->get_value()) > 10) {
  }
  while(abs(gyro->get_value()) < 80) {
  }
  while(abs(gyro->get_value()) > 20) {
  }
  myChassis.tank(0, 0);
}
void autonomous() {
  capAuto(BLUE);
  //parkFar(RED);
  //pSkills();

}
