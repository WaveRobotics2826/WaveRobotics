#include "WPILib.h"

class WaveDeliverySystem
{
public:
	WaveDeliverySystem(int channel, int slot);
	
	void run(Joystick *joystick);
	
private:
	Victor *deliveryMotor;
	
	DigitalInput *topSensor;
	
	DigitalInput *lowerTowerSensor;
	
	DigitalInput *elevatorRight;
	
	DigitalInput *elevatorLeft;
};
