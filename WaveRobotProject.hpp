#include "WPILib.h"
#include "WaveDrive.hpp"
#include "WaveCompressor.hpp"
#include "WaveWheelControl.hpp"
#include "WaveIntakeControl.hpp"
#include "WaveTurretControl.hpp"
#include "WaveDeliverySystem.hpp"
#include "AutonomousCommands.hpp"
#include "WaveIOBoard.hpp"
#include "WaveDashboardUpdate.hpp"
#include "AutoAim.hpp"

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
	
	AutoAim *autoAim;
	
	WaveIOBoard *ioBoard; 
	
	WaveDashboardUpdate *wavedashboard;
	
	//static AxisCamera &axisCamera;
	
	AutonomousCommands *autonomous;
	bool startedAutonomous;
	int autoState;
	Timer *timer;
	
	bool buttonControlUpSpeed;
	
	bool buttonControlDownSpeed;	
	
	bool buttonControlUpSpeedFast;
	bool buttonControlDownSpeedFast;

};


