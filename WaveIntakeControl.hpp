#include "WPILib.h"

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
	void intakeOn();
	
	/// \brief Commands 0% motor speed for intake
	void intakeOff();		
	
	/// \brief Setup solenoids
	void configureSolenoids(int one, int two, int three, int four);
private:
	void lower();
	
	void raise();
	
	void activatePosition();
	
	Position position;
	
	Victor *intakeMotor;
	
	double motorSpeed;
	
	Solenoid *longCylinderRetract;
	
	Solenoid *longCylinderDeploy;
	
	Solenoid *shortCylinderRetract;
	
	Solenoid *shortCylinderDeploy;
	
	bool lowerButton;
	
	bool raiseButton;
};
