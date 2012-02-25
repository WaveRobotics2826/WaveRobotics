#include "WPILib.h"

class WaveWheelControl : public PIDSource, PIDOutput
{
public:
	WaveWheelControl(DriverStationLCD *display);
	
	double PIDGet();
	
	virtual void PIDWrite(float output);
	
	virtual void setSpeed(int rpms);
	
	void stopWheel();
	
	void startWheel();
	
	void increaseSpeed(int value);
	
	void decreaseSpeed(int value);
	
	void displayWheelSpeed(int speed);
private:
	Counter *input;
	PIDController *pidController;
	Victor *motor1;
	Victor *motor2;
	Victor *motor3;
	Victor *motor4;
	DriverStationLCD *display;
	
	
};
