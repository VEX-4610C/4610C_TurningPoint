bool brakeState = false;
int flooperState = 0;
bool capGrabState = false;

auto myChassis = ChassisControllerFactory::create(
  {19, 20}, {-16, -18},
  AbstractMotor::gearset::green,
  {4_in, 11_in}
);

auto brake = pros::ADIDigitalOut(2, false);
auto liftMotor = Motor(9, false, AbstractMotor::gearset::green);
liftMotor.setBrakeMode(AbstractMotor::brakeMode::brake);
auto flooperMotor = Motor(10, false, AbstractMotor::gearset::green);
flooperMotor.setCurrentLimit(12000);
auto capGrab = pros::ADIDigitalOut(1, true);

auto brakeButton = ControllerButton(ControllerDigital::right);
auto liftUpButton = ControllerButton(ControllerDigital::R1);
auto liftDownButton = ControllerButton(ControllerDigital::L1);
auto flooperButton = ControllerButton(ControllerDigital::L2);
auto capGrabButton = ControllerButton(ControllerDigital::R2);
auto reverseButton = ControllerButton(ControllerDigital::A);
auto resetClaw = ControllerButton(ControllerDigital::left);

Controller controller;
