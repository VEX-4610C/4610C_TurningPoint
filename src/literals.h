bool brakeState = false;
int flooperState = 0;
bool capGrabState = false;
bool indexerState = 0;

auto frontLeft = Motor(19, false, AbstractMotor::gearset::green);
auto backLeft = Motor(20, false, AbstractMotor::gearset::green);
auto frontRight = Motor(16, true, AbstractMotor::gearset::green);
auto backRight = Motor(18, true, AbstractMotor::gearset::green);

frontLeft.setCurrentLimit(12000);
backLeft.setCurrentLimit(12000);
frontRight.setCurrentLimit(12000);
backRight.setCurrentLimit(12000);

auto myChassis = ChassisControllerFactory::create(
  {frontLeft, backLeft}, {frontRight, backRight},
  AbstractMotor::gearset::green,
  {4_in, 11_in}
);


auto brake = pros::ADIDigitalOut(2, false);
auto indexer = pros::ADIDigitalOut(4, false);

auto liftMotor = Motor(9, false, AbstractMotor::gearset::green);
liftMotor.setBrakeMode(AbstractMotor::brakeMode::brake);
liftMotor.setCurrentLimit(12000);
auto liftPosController = AsyncControllerFactory::posIntegrated(liftMotor, 200);


auto flooperMotor = Motor(10, false, AbstractMotor::gearset::green);
flooperMotor.setCurrentLimit(12000);
flooperMotor.setBrakeMode(AbstractMotor::brakeMode::brake);
auto capGrab = pros::ADIDigitalOut(1, true);

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




Controller controller;
