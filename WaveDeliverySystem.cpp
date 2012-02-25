#include "WaveDeliverySystem.hpp"
#include "ChannelNames.hpp"

using namespace Channels;
WaveDeliverySystem::WaveDeliverySystem(int channel, int slot)
{
	deliveryMotor = new Victor(slot, channel);
	deliveryMotor->SetSafetyEnabled(false);
	topSensor = new DigitalInput(Top_Tower_Sensor);
	lowerTowerSensor = new DigitalInput(Lower_Tower_Sensor);
	elevatorRight = new DigitalInput(Elevator_Sensor_Rt);
	elevatorLeft = new DigitalInput(Elevator_Sensor_Lt);
}

void WaveDeliverySystem::run(Joystick *joystick)
{
	if(joystick->GetRawButton(1))
	{
		deliveryMotor->Set(-1.0);
	}
	else if(joystick->GetRawButton(6))
	{
		if(topSensor->Get())
		{
			deliveryMotor->Set(-1.0);
		}
		else
		{
			deliveryMotor->Set(0);
		}
	}
	else 
	{
		deliveryMotor->Set(0);
	}
	
	cout << "Lower Tower Sensor: " << lowerTowerSensor->Get() << endl;
	cout << "Elevator Right    : " << elevatorRight->Get() << endl;
	cout << "Elevator Left     : " << elevatorLeft->Get() << endl;
}
