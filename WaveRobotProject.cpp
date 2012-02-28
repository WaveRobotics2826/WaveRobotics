#include "SimpleRobot.h"
#include "WPILib.h"
#include "WaveRobotProject.hpp"
#include "WaveCompressor.hpp"
#include "WaveWheelControl.hpp"
#include "WaveIntakeControl.hpp"
#include "WaveTurretControl.hpp"
#include "WaveDeliverySystem.hpp"
#include "ChannelNames.hpp"
#include <iostream>

using namespace Channels;
using namespace std;

WaveRobotProject::WaveRobotProject(void)
{
	driverJoystick = new Joystick(2);
	operatorJoystick = new Joystick(3);
	drive = new WaveDrive(2,4, driverJoystick);
	drive->configureSolenoids(Shift_Default);
	display = DriverStationLCD::GetInstance();
}


void WaveRobotProject::Autonomous(void)
{

}


void WaveRobotProject::OperatorControl(void)
{
	WaveDeliverySystem delivery(Delivery_Motor, 2);
	WaveTurretControl turret;
	WaveCompressor compressor(display);
	WaveWheelControl launcher(display);
	WaveIntakeControl intake(5, 1, 1.0);
	intake.configureSolenoids(
			Long_Cylinder_Solenoid,
			Short_Cylinder_Solenoid);
	launcher.setSpeed(850);
	
	compressor.run();		
	while(IsOperatorControl())
	{		
		delivery.run(operatorJoystick);
		turret.run(operatorJoystick);
		intake.run(driverJoystick);		
		
		if(operatorJoystick->GetRawButton(5))
		{		
			intake.intakeOn(true);
		}
		else if(operatorJoystick->GetRawAxis(3) > .01)
		{
			intake.intakeOn(false);
		}
		else
		{
			intake.intakeOff();
		}
		cout << driverJoystick->GetRawButton(7);
		cout << driverJoystick->GetRawButton(8);
		cout << driverJoystick->GetRawButton(9);
		cout << driverJoystick->GetRawButton(10);
		cout << driverJoystick->GetRawButton(11);
		cout << driverJoystick->GetRawButton(12) << endl;
		cout << driverJoystick->GetRawAxis(6) << endl;
		
		
		if(operatorJoystick->GetRawButton(4))
		{
			if(!buttonControlUpSpeed)
			{
				buttonControlUpSpeed = true;
				launcher.increaseSpeed(10);
			}
		}
		else if(operatorJoystick->GetRawButton(2))
		{
			if(!buttonControlDownSpeed)
			{
				buttonControlDownSpeed = true;
				launcher.decreaseSpeed(10);
			}
		}
		else
		{
			buttonControlUpSpeed = false;
			buttonControlDownSpeed = false;
		}
		
		drive->run();
		display->UpdateLCD();
	}
	compressor.stop();
}

START_ROBOT_CLASS(WaveRobotProject);
