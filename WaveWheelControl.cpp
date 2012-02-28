#include "WaveWheelControl.hpp"
#include "ChannelNames.hpp"
#include <iostream>
using namespace std;
using namespace Channels;



WaveWheelControl::WaveWheelControl(DriverStationLCD *display)
{
	this->display = display;
	input = new Counter(2, Shooter_Sensor);
	pidController = new PIDController(.9,0.1,0.1,this,this);
	pidController->SetInputRange(0,3000);
	pidController->SetOutputRange(100,1000);
	pidController->SetTolerance(.1);
	startWheel();
	motor1 = new Victor(2, Shooter_Motor_1);
	motor2 = new Victor(2, Shooter_Motor_2);
	motor3 = new Victor(2, Shooter_Motor_3);
	motor4 = new Victor(2, Shooter_Motor_4);
	motor1->SetSafetyEnabled(false);
	motor2->SetSafetyEnabled(false);
	motor3->SetSafetyEnabled(false);
	motor4->SetSafetyEnabled(false);
	input->SetMaxPeriod(100000000);
	input->SetUpdateWhenEmpty(true);
	input->Start();
	input->Reset();
}
	
double WaveWheelControl::PIDGet()
{
	#ifdef DEBUG
		cout << "attempting to get" << endl;
	#endif
	float value = input->GetPeriod();
	displayWheelSpeed((int)(60/value));
	cout << (int)(60/value) << endl;
	return 60/value;
}

void WaveWheelControl::PIDWrite(float output)
{
	#ifdef DEBUG
		cout << "output: " << output << endl;
	#endif
	output = 0 - (output/1000);
	motor1->Set(output);
	motor2->Set(output);
	motor3->Set(output);
	motor4->Set(output);
}
	
void WaveWheelControl::setSpeed(int rpms)
{
	pidController->SetSetpoint(rpms);
}

void WaveWheelControl::stopWheel()
{
	pidController->Disable();
}
	
void WaveWheelControl::startWheel()
{
	pidController->Enable();
}
	
void WaveWheelControl::increaseSpeed(int value)
{
	pidController->SetSetpoint(pidController->GetSetpoint() + value);
}

void WaveWheelControl::decreaseSpeed(int value)
{
	pidController->SetSetpoint(pidController->GetSetpoint() - value);
}

void WaveWheelControl::displayWheelSpeed(int speed)
{
	display->Printf(DriverStationLCD::kUser_Line2, 1,
	  (char *)"Wheel RPM: %i-%i", (int)pidController->GetSetpoint(), speed);	
}
