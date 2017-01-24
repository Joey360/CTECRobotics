#include <WPILib.h>
#include <CANTalon.h>

using namespace frc;

class Robot: public frc::SampleRobot {
private:
	// Variables and what not
	RobotDrive *myRobot;
	Joystick *leftJoyStick;
	Joystick *rightJoyStick;
	CANTalon *MotorR1;
	CANTalon *MotorR2;
	CANTalon *MotorL1;
	CANTalon *MotorL2;

public:
	// Function that converts raw input to a number that has more control for the driver
	void normalize(double& input){
		if (input > 0){
			input = std::pow(2, input) - 1;
		}else{
			input = -(std::pow(2, std::abs(input)) - 1);
		}
	}

	Robot(){
		// I don't actually know what this line does
		myRobot = new RobotDrive(1, 2, 3, 4);

		// Initialize the joysticks
		leftJoyStick = new Joystick(1);
		rightJoyStick = new Joystick(2);

		// Initialize the motor to a CANTalon with id number
		MotorR1 = new CANTalon(1);
		MotorR2 = new CANTalon(2);
		MotorL1 = new CANTalon(3);
		MotorL2 = new CANTalon(4);

		// Initialize the motor value to 0 to prevent a couple of things, that I don't really wanna type right now
		// Also you might just have to do this to get them to work
		MotorR1 -> Set(0);
		MotorR2 -> Set(0);
		MotorL1 -> Set(0);
		MotorL2 -> Set(0);

		myRobot -> SetExpiration(0.1);
	}


	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl() {
		while (true) {
			// Variables to store the power in
			double rightPower = 0.0;
			double leftPower = 0.0;

			// Get input from the joystick
			leftPower = leftJoyStick -> GetY();
			rightPower = rightJoyStick -> GetY();

			// Give the input data a curve, so that the driver has more percise control for turns and what not
			normalize(leftPower);
			normalize(rightPower);

			// Set the power for the motor between values -1 and 1
			MotorR1 -> Set(rightPower);
			MotorR1 -> Set(rightPower);
			MotorL1 -> Set(-leftPower);
			MotorL2 -> Set(-leftPower);
			frc::Wait(0.005);			// wait for a motor update time
		}
	}
};

START_ROBOT_CLASS(Robot)
