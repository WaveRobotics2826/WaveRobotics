#include "WPILib.h"

class WaveDrive
{
public:
	WaveDrive(int leftAxisNumber, int rightAxisNumber, Joystick *joystick);
	
	void enableDrive();
	
	void disableDrive();
	
	void run();
	
	void configureSolenoids(int one);
private:
	//Left joystick
	Joystick *m_joystick;
		
	Victor *rightMotor1;
	
	Victor *rightMotor2;
	
	Victor *leftMotor1;
	
	Victor *leftMotor2;		
	
	Solenoid *shiftSolenoid;
	
	int leftAxis;
	
	int rightAxis;
};
