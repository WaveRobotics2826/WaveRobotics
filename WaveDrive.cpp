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
	
	leftEncoder = new Encoder(Left_Encoder_A, Left_Encoder_B);
	rightEncoder = new Encoder(Right_Encoder_A, Right_Encoder_B);
	
	leftEncoder->Start();
	rightEncoder->Start();
	
	isAutonomousMode = false;
	
	leftMotor1->SetSafetyEnabled(false);
	leftMotor2->SetSafetyEnabled(false);
	rightMotor1->SetSafetyEnabled(false);
	rightMotor2->SetSafetyEnabled(false);	
}

void WaveDrive::configureSolenoids(int one)
{
	shiftSolenoid = new Solenoid(one);	
}

void WaveDrive::run()
{
	if(!isAutonomousMode)
	{
		double forwardReverse =  m_joystick->GetRawAxis(leftAxis);
		double leftRight = m_joystick->GetRawAxis(rightAxis);
		
		if(forwardReverse  <= .1 && forwardReverse >= 0)
		{
			forwardReverse = 0;
		}
		
		if(leftRight <= .05 && leftRight >= -.05)
		{
			leftRight = 0;
		}	
		
		double leftValue;
		double rightValue;
		
		bool shifter = !(m_joystick->GetRawButton(6));
		
		bool leftNeg = leftValue < 0;
		bool rightNeg = rightValue < 0;
		
		if(forwardReverse >= 0)
		{
			forwardReverse *= forwardReverse;
		}
		else
		{
			forwardReverse *=forwardReverse;
			forwardReverse = 0 - forwardReverse;
		}	
		if(leftRight >= 0)
		{
			leftRight *= leftRight;
		}
		else 
		{
			leftRight *= leftRight;
			leftRight = 0 - leftRight;
		}		
		
		leftValue = forwardReverse;
		rightValue = forwardReverse;
		
		double temp = leftRight;
		//cout << forwardReverse << " " << leftRight << endl;
		if(forwardReverse > 0)
		{
			//backward
			leftValue = leftValue + temp;
			rightValue = rightValue - temp;
		}
		else
		{
			//forward
			leftValue = leftValue - temp;
			rightValue = rightValue + temp;
		}
		
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
		
		shiftSolenoid->Set(shifter);
	}
}

void WaveDrive::resetMeasure()
{
	startMeasure();
}

void WaveDrive::startMeasure()
{
	//resets the encoder counts
	leftEncoder->Reset();
	rightEncoder->Reset();
}

double WaveDrive::getDistanceTraveled()
{
	return leftEncoder->Get() * (15.1189 / 500); //5inch wheel
}

void WaveDrive::stop()
{
	setLeftMotor(0);
	setRightMotor(0);
}

bool WaveDrive::isRampSensed()
{
	return !rampSensor->Get();
}

void WaveDrive::AutonomousMode(bool value)
{
	isAutonomousMode = value;
}

void WaveDrive::setLeftMotor(double value)
{		
	leftMotor1->Set(value);
	leftMotor2->Set(value);	
}
	
void WaveDrive::setRightMotor(double value)
{
	rightMotor1->Set(-value);
	rightMotor2->Set(-value);
}
