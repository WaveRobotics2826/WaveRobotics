#ifndef WAVE_IO_BOARD_HPP
#define WAVE_IO_BOARD_HPP

#include "WPILib.h"


class WaveIOBoard
{
    public:
	    WaveIOBoard();
	    
	    void run();

	    
    private:
	    
	    DriverStation *m_driverStation;
	
};





#endif
