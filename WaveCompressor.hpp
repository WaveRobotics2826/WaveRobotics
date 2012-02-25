#include "WPILib.h"
#include <pthread.h>

#ifndef WAVE_COMPRESSOR_HPP
#define WAVE_COMPRESSOR_HPP

class WaveCompressor
{
public:
	WaveCompressor(DriverStationLCD *display);
	
	void run();	
	
	void stop();
	
	void Worker();
private:
	
	static void *THREAD_ENTRY(void *object);
	
	DigitalInput *m_compressorSignal;
	
	Relay *m_compressorOn;
	
	bool keepRunning;
	
	pthread_t compThread;
	
	DriverStationLCD *display;
};



#endif
