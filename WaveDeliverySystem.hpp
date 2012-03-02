#include "WPILib.h"

#ifndef WAVEDELIVERYSYSTEM
#define WAVEDELIVERYSYSTEM

class WaveDeliverySystem
{
public:
	WaveDeliverySystem(int channel, int slot);
	
	void run(Joystick *joystick);
	
	void automaticDelivery();
	
	void resetAuto();
	
	void fire();
	
private:
	Victor *deliveryMotor;
	
	DigitalInput *topSensor;
	
	DigitalInput *lowerTowerSensor;
	
	DigitalInput *elevatorRight;
	
	DigitalInput *elevatorLeft;
	
	bool moveToElevator;
	
	bool elevatorSensorReset;
};

#endif
