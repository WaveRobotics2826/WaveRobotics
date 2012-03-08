#include "WaveTurretControl.hpp"
#include <iostream>
using namespace std;
using namespace Channels;

WaveTurretControl::WaveTurretControl()
{
	vex1 = new PWM(2, Turret_Motor_1);
	vex2 = new PWM(2, Turret_Motor_2);
	turretSensor = new AnalogChannel(Turret_Angle_Sensor);
}
	

void WaveTurretControl::moveTurret(float input)
{
	visionInput = input;
	hasVisionInput = true;
}

void WaveTurretControl::toggleVision()
{
	overrideVision = !overrideVision;
}

void WaveTurretControl::run(Joystick *joystick)
{
	// left and right analog buttons
	double input = -joystick->GetRawAxis(4);
	if(joystick->GetRawAxis(7) && joystick->GetRawAxis(8))
	{
		if(!overridePressRelease)
		{
			toggleVision();
			overridePressRelease = true;
		}
	}
	else
	{
		overridePressRelease = false;
	}
	
	int sensorCount = turretSensor->GetValue();	
		
	if(input > 1)
		input = 1;
	if(input < -1)
		input = -1;
	
	if(input > -.1 && input < .1)
	{
		input = 0;
	}
	if(input == 0)
	{
		if(hasVisionInput && !overrideVision)
		{
			input = visionInput;
			hasVisionInput = false;
		}
	}
	input = (input * 127) + 128;
	if(input > 253)
	{
		input = 253;
	}
	if(input < 2)
	{
		input = 2;
	}
	vex1->SetRaw((int)(input));
	vex2->SetRaw((int)(input));
}
	




