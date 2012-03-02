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
	display = DriverStationLCD::GetInstance();
	driverJoystick = new Joystick(2);
	operatorJoystick = new Joystick(3);
	drive = new WaveDrive(2,4, driverJoystick);		
	delivery = new WaveDeliverySystem(Delivery_Motor, 2);
	turret = new WaveTurretControl();
	compressor = new WaveCompressor(display);
	launcher = new WaveWheelControl(display);
	intake = new WaveIntakeControl(5, 1, 1.0);	
	ioBoard = new WaveIOBoard();
	
	drive->configureSolenoids(Shift_Default);
	intake->configureSolenoids(
		Long_Cylinder_Solenoid,
		Short_Cylinder_Solenoid);
	launcher->setSpeed(850);
	autonomous = new AutonomousCommands(drive);
}


void WaveRobotProject::Autonomous(void)
{
	launcher->setSpeed(1370);
	drive->resetMeasure();
	while(!autonomous->forwardReverseDriveCommand(-.5,120))
	{
		
	}
	while(1)
	{		
		delivery->fire();
	}
}


void WaveRobotProject::OperatorControl(void)
{	
	compressor->run();	
	drive->startMeasure();
	while(IsOperatorControl())
	{		
		//cout << drive->getDistanceTraveled() << endl;
		drive->getDistanceTraveled();
		delivery->run(operatorJoystick);
		turret->run(operatorJoystick);
		intake->run(driverJoystick);	
		ioBoard->run();
		
		if(operatorJoystick->GetRawButton(5))
		{		
			intake->intakeOn(true);
		}
		else if(operatorJoystick->GetRawAxis(3) > .01)
		{
			intake->intakeOn(false);
		}
		else
		{
			intake->intakeOff();
		}		
		if(operatorJoystick->GetRawButton(4))
		{
			if(!buttonControlUpSpeed)
			{
				buttonControlUpSpeed = true;
				launcher->increaseSpeed(10);
			}
		}
		else if(operatorJoystick->GetRawButton(2))
		{
			if(!buttonControlDownSpeed)
			{
				buttonControlDownSpeed = true;
				launcher->decreaseSpeed(10);
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
	compressor->stop();
	intake->resetIntakePosition();
}

START_ROBOT_CLASS(WaveRobotProject);
