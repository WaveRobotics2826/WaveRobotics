#include "WPILib.h"

#ifndef WAVEDELIVERYSYSTEM
#define WAVEDELIVERYSYSTEM

class WaveDeliverySystem
{
public:
	WaveDeliverySystem(int channel, int slot);
	
	void run(Joystick *joystick);
	
	void automaticDelivery();
	
private:
	Victor *deliveryMotor;
	
	DigitalInput *topSensor;
	
	DigitalInput *lowerTowerSensor;
	
	DigitalInput *elevatorRight;
	
	DigitalInput *elevatorLeft;
	
	bool moveToElevator;
};

#endif
