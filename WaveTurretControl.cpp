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
	
void WaveTurretControl::run(Joystick *joystick)
{
	// left and right analog buttons
	double input = joystick->GetRawAxis(4);
	int sensorCount = turretSensor->GetValue();
	if((input > 0 && sensorCount > 160) ||
 	   (input < 0 && sensorCount < 740))
	{
		if(sensorCount < 200 || sensorCount > 700)
		{
			input = input * .25;
		}
		cout << "Vex: " << (int)(input * 126) + 128 << endl;
		vex1->SetRaw((int)(input * 126) + 128);
		vex2->SetRaw((int)(input * 126) + 128);
	}
	else
	{
		cout << "out of bounds" << endl;
		vex1->SetRaw(128);
		vex2->SetRaw(128);
	}
}



