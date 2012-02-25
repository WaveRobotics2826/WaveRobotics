#include "WaveIntakeControl.hpp"
#include <iostream>
using namespace std;

WaveIntakeControl::WaveIntakeControl(int channel, int slot, double speed):
	motorSpeed(speed)
{
	position = Position_Up;
	intakeMotor = new Victor(slot, channel);
	intakeMotor->SetSafetyEnabled(false);	
}

void WaveIntakeControl::configureSolenoids(int longRe, int LongEx, int shortRe, int shortEx)
{
	longCylinderRetract = new Solenoid(longRe);		
	longCylinderDeploy = new Solenoid(LongEx);
	shortCylinderRetract = new Solenoid(shortRe);
	shortCylinderDeploy = new Solenoid(shortEx);
}

void WaveIntakeControl::run(Joystick *joystick)
{		
	if(joystick->GetRawButton(3))
	{
		if(!lowerButton)
		{			
			lowerButton = true;
			lower();
		}
	}
	else if(joystick->GetRawButton(2))
	{
		if(!raiseButton)
		{
			raiseButton = true;
			raise();
		}
	}
	else
	{
		lowerButton = false;
		raiseButton = false;
	}
	
	activatePosition();
}

void WaveIntakeControl::lower()
{
	switch(position)
	{
	case Position_Up:
		position = Position_Ramp;
		break;
	case Position_Ramp:
		position = Position_Down;
		break;
	default:
		break;
	}
}
	
void WaveIntakeControl::raise()
{
	switch(position)
	{
	case Position_Down:
		position = Position_Ramp;
		break;
	case Position_Ramp:
		position = Position_Up;
		break;
	default:
		break;
	}
}
	
void WaveIntakeControl::activatePosition()
{
	switch(position)
	{
	case Position_Up:
		longCylinderRetract->Set(true);
		shortCylinderRetract->Set(true);
		longCylinderDeploy->Set(false);
		shortCylinderDeploy->Set(false);
		break;	
	case Position_Ramp:
		longCylinderRetract->Set(false);
		shortCylinderRetract->Set(true);
		longCylinderDeploy->Set(true);
		shortCylinderDeploy->Set(false);
		break;
	case Position_Down:
		longCylinderRetract->Set(false);
		shortCylinderRetract->Set(false);
		longCylinderDeploy->Set(true);
		shortCylinderDeploy->Set(true);
		break;
	default:
		break;
	}
}

void WaveIntakeControl::intakeOn()
{
	intakeMotor->Set(motorSpeed);
}

void WaveIntakeControl::intakeOff()
{
	intakeMotor->Set(0);
}
