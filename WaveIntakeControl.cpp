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

void WaveIntakeControl::configureSolenoids(int longCyl, int shortCyl)
{
	
	longCylinder = new Solenoid(longCyl);
	shortCylinder = new Solenoid(shortCyl);
	
}

void WaveIntakeControl::run(Joystick *joystick)
{		
	if(joystick->GetRawButton(4))
	{
		position = Position_Up;
	}
	else if(joystick->GetRawButton(2))
	{
		position = Position_Ramp;
	}
	else if(joystick->GetRawButton(1))
	{
		position = Position_Down;
	}
	
	activatePosition();
}
	
void WaveIntakeControl::activatePosition()
{
	switch(position)
	{
	case Position_Up:
		longCylinder->Set(false);
		shortCylinder->Set(false);		
		break;	
	case Position_Ramp:
		longCylinder->Set(true);
		shortCylinder->Set(false);
		break;
	case Position_Down:
		longCylinder->Set(true);
		shortCylinder->Set(true);
		break;
	default:
		break;
	}
}

void WaveIntakeControl::activatePosition(Position setPosition)
{
	position = setPosition;
	activatePosition();
}

void WaveIntakeControl::resetIntakePosition()
{
	position = Position_Up;
}

void WaveIntakeControl::intakeOn(bool reverse)
{
	if(reverse)
	{
		intakeMotor->Set(motorSpeed);
	}
	else
	{
		intakeMotor->Set(-motorSpeed);
	}
		
}

void WaveIntakeControl::intakeOff()
{
	intakeMotor->Set(0);
}
