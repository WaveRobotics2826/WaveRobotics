#include "WPILib.h"
#include "WaveDrive.hpp"
#include "WaveCompressor.hpp"
#include "WaveWheelControl.hpp"
#include "WaveIntakeControl.hpp"
#include "WaveTurretControl.hpp"
#include "WaveDeliverySystem.hpp"
#include "AutonomousCommands.hpp"
#include "WaveIOBoard.hpp"

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
	
	AutonomousCommands *autonomous;
	
	bool buttonControlUpSpeed;
	
	bool buttonControlDownSpeed;	
};


