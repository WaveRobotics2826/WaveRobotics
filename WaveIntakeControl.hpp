#include "WPILib.h"

#ifndef WAVEINTAKECONTROL
#define WAVEINTAKECONTROL

enum Position
{
	Position_Down,	
	Position_Ramp,
	Position_Up,
	Position_Count
};

class WaveIntakeControl
{
public:
	/// \brief Constructor
	/// \param channel - PWM channel for intake motor
	/// \param slot - Slot for digital io card
	WaveIntakeControl(int channel, int slot, double speed);
	
	/// \brief Call for joystick check every loop
	void run(Joystick *joystick);
	
	/// \brief Commands 100% motor speed for intake
	void intakeOn(bool reverse = false);
	
	/// \ brief percent is 0 to 1. Will intake
	void intakePercentage(double percent);
	/// \brief Commands 0% motor speed for intake
	void intakeOff();		
	
	/// \brief resets the intake to the up position
	void resetIntakePosition();
	
	/// \brief Setup solenoids
	void configureSolenoids(int one, int two);

	//Allows Autonomous to set the intake position 
	void activatePosition(Position setPosition);

private:
	void lower();
	
	void raise();
	
	void activatePosition();
	
	Position position;
	
	Victor *intakeMotor;
	
	double motorSpeed;
	
	Solenoid *longCylinder;	
	
	Solenoid *shortCylinder;	
	
	bool lowerButton;
	
	bool raiseButton;
};

#endif
