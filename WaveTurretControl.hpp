#include "WPILib.h"
#include "ChannelNames.hpp"

#ifndef WAVETURRETCONTROL
#define WAVETURRETCONTROL

class WaveTurretControl
{
public:
	WaveTurretControl();
		
	void run(Joystick *joystick);
	//-1 to 1
	void moveTurret(float speed);
	
private:	
	void toggleVision();
	
	PWM *vex1;
	
	PWM *vex2;
	
	bool hasVisionInput;
	
	double visionInput;
	
	AnalogChannel *turretSensor;
	
	bool overrideVision;
	
	bool overridePressRelease;
	
};

#endif
