#include "WPILib.h"
#include <pthread.h>
#include "WaveTurretControl.hpp"

class AutoAim
{
public:
	AutoAim(WaveTurretControl *turret);
	
	void autoAimOn();
	
	void autoAimOff();
	
	void autoAimRun();
	
private:
	bool useAutoAim;
	
	WaveTurretControl *turret;
	
	pthread_t serverThread;
	
	float accum;
};
