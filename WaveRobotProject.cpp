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
	drive = new WaveDrive(2,5, driverJoystick);
	drive->configureSolenoids(
			Shift_Default,
			Shift_Active);
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
			Long_Cylinder_Retract_Solenoid,
			Long_Cylinder_Extend_Solenoid, 
			Short_Cylinder_Retract_Solenoid, 
			Short_Cylinder_Extend_Solenoid);
	launcher.setSpeed(400);
	//launcher.stopWheel();
	
	compressor.run();		
	while(IsOperatorControl())
	{		
		delivery.run(operatorJoystick);
		turret.run(operatorJoystick);
		intake.run(driverJoystick);		
		
		if(operatorJoystick->GetRawButton(5))
		{		
			intake.intakeOn();
		}
		else
		{
			intake.intakeOff();
		}
		
		if(driverJoystick->GetRawButton(4))
		{
			if(!buttonControlUpSpeed)
			{
				buttonControlUpSpeed = true;
				launcher.increaseSpeed(10);
			}
		}
		else if(driverJoystick->GetRawButton(1))
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
