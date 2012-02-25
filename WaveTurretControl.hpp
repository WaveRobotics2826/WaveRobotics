#include "WPILib.h"
#include "ChannelNames.hpp"

class WaveTurretControl
{
public:
	WaveTurretControl();
	
	void run(Joystick *joystick);
private:
	PWM *vex1;
	
	PWM *vex2;
	
	AnalogChannel *turretSensor;
	
};
