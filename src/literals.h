bool brakeState = false;
int flooperState = 0;
bool manualIndex = 0;
bool capGrabState = false;
bool indexerState = 0;

auto frontLeft = Motor(18, false, AbstractMotor::gearset::green);
auto backLeft = Motor(19, false, AbstractMotor::gearset::green);
auto frontRight = Motor(21, true, AbstractMotor::gearset::green);
auto backRight = Motor(15, true, AbstractMotor::gearset::green);
frontLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
backLeft.setBrakeMode(AbstractMotor::brakeMode::hold);
frontRight.setBrakeMode(AbstractMotor::brakeMode::hold);
backRight.setBrakeMode(AbstractMotor::brakeMode::hold);


auto myChassis = ChassisControllerFactory::create(
  {frontLeft, backLeft}, {frontRight, backRight},
  AbstractMotor::gearset::green,
  {4_in, 15.25_in}
);

auto indexer = pros::ADIDigitalOut(4, false);

auto liftMotor = Motor(6, false, AbstractMotor::gearset::green);
liftMotor.setBrakeMode(AbstractMotor::brakeMode::brake);
auto liftPosController = AsyncControllerFactory::posIntegrated(liftMotor, 200);


auto flooperMotor = Motor(2, false, AbstractMotor::gearset::green);
flooperMotor.setBrakeMode(AbstractMotor::brakeMode::brake);
auto capGrab = pros::ADIDigitalOut(2, true);

auto brakeButton = ControllerButton(ControllerDigital::right);
auto liftUpButton = ControllerButton(ControllerDigital::R1);
auto liftDownButton = ControllerButton(ControllerDigital::L1);
auto flooperButton = ControllerButton(ControllerDigital::L2);
auto capGrabButton = ControllerButton(ControllerDigital::R2);
auto resetClaw = ControllerButton(ControllerDigital::left);
auto reverseButton = ControllerButton(ControllerDigital::A);

auto liftLowButton = ControllerButton(ControllerDigital::Y);
auto liftHighButton =  ControllerButton(ControllerDigital::X);
auto fullScoreButton =  ControllerButton(ControllerDigital::up);
auto manualIndexButton =  ControllerButton(ControllerDigital::down);

/* flooperMotor.setCurrentLimit(12000);
liftMotor.setCurrentLimit(12000);
frontLeft.setCurrentLimit(12000);
backLeft.setCurrentLimit(12000);
frontRight.setCurrentLimit(12000);
backRight.setCurrentLimit(12000); */


Controller controller;
