#include "WPILib.h"
#include "ChannelNames.hpp"

#ifndef WAVETURRETCONTROL
#define WAVETURRETCONTROL

class WaveTurretControl
{
public:
	WaveTurretControl();
	
	void moveTurret(double input);
	
	void run(Joystick *joystick);
private:
	PWM *vex1;
	
	PWM *vex2;
	
	bool hasVisionInput;
	
	double visionInput;
	
	AnalogChannel *turretSensor;
	
};

#endif
