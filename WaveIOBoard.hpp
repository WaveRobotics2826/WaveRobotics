#ifndef WAVE_IO_BOARD_HPP
#define WAVE_IO_BOARD_HPP

#include "WPILib.h"


class WaveIOBoard
{
    public:
	    WaveIOBoard();
	    
	    void run();
	    int getCypressDial();
	    void printCypressDial();
	    
    private:
	    
	    DriverStation *m_driverStation;
	
};





#endif
