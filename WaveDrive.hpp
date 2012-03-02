#include "WPILib.h"

#ifndef WAVEDRIVE
#define WAVEDRIVE

class WaveDrive
{
public:
	WaveDrive(int leftAxisNumber, int rightAxisNumber, Joystick *joystick);
	
	void AutonomousMode(bool value);
	
	void startMeasure();
	
	void resetMeasure();
	
	double getDistanceTraveled();
	
	void run();
	
	void configureSolenoids(int one);
	
	bool isRampSensed();
	
	void setLeftMotor(double value);
	
	void setRightMotor(double value);
	
	void stop();
	
private:
	bool isAutonomousMode;
	
	Joystick *m_joystick;
	
	Victor *rightMotor1;
	
	Victor *rightMotor2;
	
	Victor *leftMotor1;
	
	Victor *leftMotor2;		
	
	Solenoid *shiftSolenoid;
	
	Encoder *leftEncoder;
	
	Encoder *rightEncoder;
	
	DigitalInput *rampSensor;
	
	int rightCounts;
	
	int leftCounts;
	
	int leftAxis;
	
	int rightAxis;
};

#endif
