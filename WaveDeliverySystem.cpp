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
	moveToElevator = false;
	
}

void WaveDeliverySystem::run(Joystick *joystick)
{
	if(joystick->GetRawButton(8))
	{
		resetAuto();
		fire();
	}
	else if(joystick->GetRawButton(6))
	{
		resetAuto();
		if(topSensor->Get())
		{
			deliveryMotor->Set(-1.0);
		}
		else
		{
			deliveryMotor->Set(0);
		}
	}
	else if(joystick->GetRawAxis(3) < -.1)
	{
		resetAuto();
		deliveryMotor->Set(1.0);
	}
	else 
	{
		automaticDelivery();
	}	
}

void WaveDeliverySystem::resetAuto()
{
	elevatorSensorReset = false;
	moveToElevator = false;
}

void WaveDeliverySystem::fire()
{
	deliveryMotor->Set(-1.0);
}

void WaveDeliverySystem::slowfire()
{
	deliveryMotor->Set(-.50);
}

void WaveDeliverySystem::automaticDelivery()
{
	if(topSensor->Get())
	{
		if(moveToElevator)
		{
			deliveryMotor->Set(-1.0);
		}
		if(lowerTowerSensor->Get())
		{			
			elevatorSensorReset = true;
			if(elevatorLeft->Get() && elevatorRight->Get())
			{
				if(!moveToElevator)
				{
					deliveryMotor->Set(0);
				}	
				if(elevatorSensorReset && moveToElevator)
				{
					moveToElevator = false;
				}
			}
			else
			{
				moveToElevator = true;
			}			
		}
		else
		{				
			if(elevatorLeft->Get() && elevatorRight->Get())
			{
				if(!moveToElevator)
				{
					deliveryMotor->Set(0);
				}
				if(elevatorSensorReset && moveToElevator)
				{
					moveToElevator = false;
				}
			}			
			else
			{
				moveToElevator = true;
			}	
			elevatorSensorReset = false;
		}
	}
	else
	{
		deliveryMotor->Set(0);
	}	
}
