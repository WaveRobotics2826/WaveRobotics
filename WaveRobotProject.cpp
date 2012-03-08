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

const char *cameraIP = "10.28.26.11";

//static AxisCamera &axisCamera = AxisCamera::GetInstance(cameraIP);


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
	timer = new Timer();
	wavedashboard = new WaveDashboardUpdate(launcher);
	autoAim = new AutoAim(turret);
	
	drive->configureSolenoids(Shift_Default);
	intake->configureSolenoids(
		Long_Cylinder_Solenoid,
		Short_Cylinder_Solenoid);
	launcher->setSpeed(850);
	autonomous = new AutonomousCommands(drive);
	startedAutonomous = false;
	autoState = 1;
}


void WaveRobotProject::Autonomous(void)
{
		cout << "entering auto mode" << endl;
	
//	if(!startedAutonomous)
//	{
//		//only reset the encoders if Autonomous has not started yet
		//drive->resetMeasure();
//	}
	while(IsAutonomous()) //if(IsAutonomous())
	{
		//drive->resetMeasure();
		cout << "is auto mode" << endl;
		startedAutonomous = true;
		
		cout << "Cypress board = " << ioBoard->getCypressDial() << endl;
		
		int switchMode = ioBoard->getCypressDial();
		
		display->Printf(DriverStationLCD::kUser_Line3, 1,
			(char *)"Autonomous Mode: %i",switchMode);
		display->UpdateLCD();		
		
		switch(switchMode)
		{
			case 0: //sit at top of key and shoot at top hoop
			{
				while(IsAutonomous())
				{
					//timer->Reset(); 
					launcher->setSpeed(2150);
					while(launcher->PIDGet() < 2150)
					{
						//wait for wheel to speed up
					}
					Wait(6.0);
					delivery->slowfire();
				}
								
				break;
			}
			case 1: //sit at side of key and shoot at middle hoop
			{	
				while(IsAutonomous())
				{
					launcher->setSpeed(1650);
					while(launcher->PIDGet() < 1650)
					{
						//wait for wheel to speed up
					}
					Wait(6);
					delivery->slowfire();
				}
							
							
				break;
			}
			case 2:  //Drive to bridge then shoot
			{   //Drive 120 inches or until bridge sensor is tripped. Start firing balls
			    //Lower the Intake to the floor position. Start Intake rollers. Wait 4 seconds.
			    //Raise the Intake to the bridge position.
				autoState=1;
				drive->resetMeasure();
				while(IsAutonomous())
				{
					launcher->setSpeed(2450); //set speed
					switch(autoState)
					{
				    	case 1: //get to bridge
				    		compressor->run();	
				    		intake->activatePosition(Position_Ramp);
				    		if(autonomous->forwardReverseDriveCommand(.40, 50)|| autonomous->getBridgeSensor() )
				    		{
				    			autoState = 2;
				    			drive->resetMeasure();
				    		}
				    		break;
				    		
				    	case 2: //sensor
				    		if(autonomous->forwardReverseDriveCommand(-.4, -1) )
				    		{
				    			drive->stop();
				    			autoState = 3;
				    		}
				    		break;
				    		
				    	case 3: //lower bridge
				    		delivery->fire(); //shooting
				    		intake->activatePosition(Position_Down);
				    	//	intake->intakeOn(true);
				    		intake->intakeOff();
				    		Wait(3);
				    		
				    			autoState = 4;
				    		
				    		break;
				    	case 4: //Raise intake to bridge position
				    		intake->activatePosition(Position_Ramp);
				    		intake->intakePercentage(0.62);	
				    		Wait(2);
				    		autoState = 5;
				    		break;
				    	case 5:
				    		intake->activatePosition(Position_Ramp);
				    		//intake->activatePosition(Position_Down);
				    		intake->intakeOff();
				    		autoState = 0;
				    		break;
				    	default:
				    	case 0:
				    		//do nothing, or continue what it was doing
				    		break;
					} //switch(autoState)
				} //while(IsAutonomous())
				break;
			}
			case 3: //Shoot after manipulating bridge 
			{
				while(IsAutonomous())
				{
					launcher->setSpeed(2000); //set speed
					switch(autoState)
					{
				    	case 1: //get to bridge
				    		compressor->run();	
				    		intake->activatePosition(Position_Ramp);
				    		if(autonomous->forwardReverseDriveCommand(.31, -32) || autonomous->getBridgeSensor())
				    		{
				    			drive->stop();
				    			autoState = 2;
				    			timer->Start();
				    		}
				    		break;
				    	case 2: //lower bridge
				    		intake->activatePosition(Position_Down);
				    		intake->intakeOn(true);
				    		if(timer->HasPeriodPassed(4))
				    		{
				    			autoState = 3;
				    		}
				    		break;
				    	case 3: //Raise intake to bridge position
				    		intake->activatePosition(Position_Ramp);
				    		autoState = 4;
				    		break;
				    	case 4: //shoot
				    		delivery->fire(); //shooting
				    		autoState = 0;
				    		break;
				    	default:
				    	case 0:
				    		//do nothing, or continue what it was doing
				    		break;
					} //switch(autoState)
				} //while(IsAutonomous())
				break;
			}
			case 4: //do nothing
			case 5: //do nothing
			case 6: //do nothing
			case 7: //do nothing
			{
				while(IsAutonomous())
				{}
				break;
			}
			default:
				break;
		} //switch(switchMode)
	} //if(IsAutonomous())
	cout << "exiting auto mode" << endl;
}


void WaveRobotProject::OperatorControl(void)
{	
	compressor->run();	
	drive->startMeasure();
	autoAim->autoAimOn();
	while(IsOperatorControl())
	{	
		//cout << drive->getDistanceTraveled() << endl;
		drive->getDistanceTraveled();
		delivery->run(operatorJoystick);
		turret->run(operatorJoystick);
		intake->run(driverJoystick);
		wavedashboard->run();
		autoAim->autoAimRun();
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
		else if(operatorJoystick->GetRawButton(3))
		{
			if(!buttonControlUpSpeedFast)
			{
				buttonControlUpSpeedFast = true;
				launcher->increaseSpeed(100);
			}
		}
		else if(operatorJoystick->GetRawButton(1))
	    {
			if(!buttonControlDownSpeedFast)
			{
				buttonControlDownSpeedFast = true;
				launcher->decreaseSpeed(100);
			}
		}
		else
		{
			buttonControlUpSpeed = false;
			buttonControlDownSpeed = false;
			buttonControlUpSpeedFast = false;
			buttonControlDownSpeedFast = false;
		}
		
		
		//Updates LED on Dashboard
		if((launcher->PIDGet() > (launcher->getSpeedSet() - 15)) &&
	       (launcher->PIDGet() < (launcher->getSpeedSet() + 15)))
		{
			//within range
			wavedashboard->updateSpeed(true);			
		}
		else
		{
			//not within range
			wavedashboard->updateSpeed(false);
		}
		
		drive->run();
		display->UpdateLCD();
	}
	autoAim->autoAimOff();
	compressor->stop();
	intake->resetIntakePosition();
}


START_ROBOT_CLASS(WaveRobotProject);
