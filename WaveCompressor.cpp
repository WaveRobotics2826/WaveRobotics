#include "WaveCompressor.hpp"
#include "pthread.h"
#include <iostream>

using namespace std;

WaveCompressor::WaveCompressor(DriverStationLCD *display)
{
	this->display = display;
	m_compressorSignal = new DigitalInput(1);
	m_compressorOn = new Relay(2, Relay::kForwardOnly);
	keepRunning = false;
}

void WaveCompressor::run()
{
	keepRunning = true;	
	WaveCompressor foo(display);
	pthread_create(&compThread , NULL, THREAD_ENTRY, this);
}

void WaveCompressor::stop()
{
	keepRunning = false;
	pthread_join(compThread, NULL);
}

void WaveCompressor::Worker()
{
	while(keepRunning)
	{
		bool onOff = !m_compressorSignal->Get();
		display->Printf(DriverStationLCD::kUser_Line1, 1,
						(char *)"Comp. Status: %s", (onOff?"On":"Off"));
		if(onOff)
		{
			m_compressorOn->Set(Relay::kOn);
		}
		else
		{
			m_compressorOn->Set(Relay::kOff);
		}
	}
}

void *WaveCompressor::THREAD_ENTRY(void *object)
{
	((WaveCompressor *)object)->Worker();
	return NULL;
}
