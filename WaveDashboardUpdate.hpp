#ifndef WAVE_DASHBOARD_UAPDATE_HPP
#define WAVE_DASHBOARD_UAPDATE_HPP


#include "WPILib.h"
#include "WaveWheelControl.hpp"


class WaveDashboardUpdate
{
public:
	WaveDashboardUpdate(WaveWheelControl *wheelControl);
	
	void run();
	
	void updateTarget(bool systemTargeted);
	void updateSpeed(bool shooterAtSpeed);
	void updateDistance(double distanceToTarget);
	
private:
	
	bool isSystemTargeted;
	bool isShooterAtSpeed;
	double targetDistance;
	WaveWheelControl *launcher;
	
};

#endif
