#include "WPILib.h"
#include "WaveDrive.hpp"
#include "WaveCompressor.hpp"
#include "WaveWheelControl.hpp"
#include "WaveIntakeControl.hpp"
#include "WaveTurretControl.hpp"
#include "WaveDeliverySystem.hpp"
#include "WaveIOBoard.hpp"


/**
 * This is a demo program showing the use of the RobotBase class.
 * The SimpleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 */ 
class WaveRobotProject : public SimpleRobot
{
public:
	/// Constructor
	WaveRobotProject(void);
	
	/// Autonomous Mode
	void Autonomous(void);	

	/// Operator Mode
	void OperatorControl(void);
private:
	WaveDrive *drive;
	
	Joystick *driverJoystick;
	
	Joystick *operatorJoystick;
	
	DriverStationLCD *display;
	
	WaveDeliverySystem *delivery;
	
	WaveTurretControl *turret;
	
	WaveCompressor *compressor;
	
	WaveWheelControl *launcher;
	
	WaveIntakeControl *intake;

	WaveIOBoard *ioBoard; 
	
	bool buttonControlUpSpeed;
	
	bool buttonControlDownSpeed;	
};


