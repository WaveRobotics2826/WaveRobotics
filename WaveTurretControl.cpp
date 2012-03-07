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

void WaveTurretControl::run(Joystick *joystick)
{
	// left and right analog buttons
	double input = -joystick->GetRawAxis(4);
	int sensorCount = turretSensor->GetValue();
	
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


//	// left and right analog buttons
//	double input2 = -joystick->GetRawAxis(6);
//	int sensorCount2 = turretSensor->GetValue();
//	//cout << sensorCount << endl;
//	//{
////		if(sensorCount < 200 || sensorCount > 700)
////		{
////			input = input * .25;
////		}
//		input = (input * 127) + 128;
//		if(input > 253)
//		{
//			input = 253;
//		}
//		if(input < 2)
//		{
//			input = 2;
//		}
//		vex1->SetRaw((int)(input * .5));
//		vex2->SetRaw((int)(input * .5));


}
	




