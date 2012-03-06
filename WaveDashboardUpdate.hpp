#ifndef WAVE_DASHBOARD_UAPDATE_HPP
#define WAVE_DASHBOARD_UAPDATE_HPP


#include "WPILib.h"
class WaveDashboardUpdate
{
public:
	WaveDashboardUpdate();
	
	void run();
	
	void updateTarget(bool systemTargeted);
	void updateSpeed(bool shooterAtSpeed);
	void updateDistance(double distanceToTarget);
	
private:
	
	bool isSystemTargeted;
	bool isShooterAtSpeed;
	double targetDistance;
	
	
};

#endif
