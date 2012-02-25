#include "WaveDrive.hpp"
#include "ChannelNames.hpp"

using namespace Channels;

WaveDrive::WaveDrive(int leftAxisNumber, int rightAxisNumber, Joystick *joystick)
{
	leftAxis = leftAxisNumber;
	rightAxis = rightAxisNumber;
	
	m_joystick = joystick;
	
	leftMotor1 = new Victor(Left_Motor_1);
	leftMotor2 = new Victor(Left_Motor_2);
	rightMotor1 = new Victor(Right_Motor_1);
	rightMotor2 = new Victor(Right_Motor_2);	
	
	leftMotor1->SetSafetyEnabled(false);
	leftMotor2->SetSafetyEnabled(false);
	rightMotor1->SetSafetyEnabled(false);
	rightMotor2->SetSafetyEnabled(false);	
}

void WaveDrive::configureSolenoids(int one, int two)
{
	activeShiftSolenoid = new Solenoid(one);
	inactiveShiftSolenoid = new Solenoid(two);
}

void WaveDrive::enableDrive()
{
	
}

void WaveDrive::disableDrive()
{
	
}

void WaveDrive::run()
{
	double leftValue = m_joystick->GetRawAxis(leftAxis);
	double rightValue = m_joystick->GetRawAxis(rightAxis);
	
	bool shifter = m_joystick->GetRawButton(6);
	
	bool leftNeg = leftValue < 0;
	bool rightNeg = rightValue < 0;
	
	leftValue *= leftValue;
	rightValue *= rightValue;
	
	if(!leftNeg)
		leftValue = 0 - leftValue;
	if(rightNeg)
		rightValue = 0 - rightValue;
	
	if(leftValue > 1.0)
		leftValue = 1.0;
	if(rightValue > 1.0)
		rightValue = 1.0;
	if(leftValue < -1.0)
		leftValue = -1.0;
	if(rightValue < -1.0)
		rightValue = -1.0;
	
	//set motors
	rightMotor1->Set(rightValue);
	rightMotor2->Set(rightValue);
	
	leftMotor1->Set(leftValue);
	leftMotor2->Set(leftValue);
	
	
	activeShiftSolenoid->Set(shifter);
	inactiveShiftSolenoid->Set(!shifter);
}
