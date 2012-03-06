#include "AutonomousCommands.hpp"
#include "ChannelNames.hpp"
#include <iostream>

using namespace std;
using namespace Channels;

AutonomousCommands::AutonomousCommands(WaveDrive *drive)
{
	this->drive = drive;
	bridgeSensor = new DigitalInput(Bridge_Sensor);
}

bool AutonomousCommands::forwardReverseDriveCommand(double speed, double distance)
{
	cout << "traveled " << drive->getDistanceTraveled() << " ";
	if(((distance > 0) && (drive->getDistanceTraveled() > (distance * .75))) ||
			((distance < 0) && (drive->getDistanceTraveled() < (distance * .75))))
	{
		cout << "run slow" << endl;
		drive->setLeftMotor(speed * .55);
		drive->setRightMotor(speed * .5);
	}
	else
	{
		cout << "run fast" << endl;
		drive->setLeftMotor(speed);
		drive->setRightMotor(speed * .95);
	}

	if(((distance > 0) && (drive->getDistanceTraveled() > distance)) ||
			((distance < 0) && (drive->getDistanceTraveled() < distance)))
	{
		cout << " Returnig 1" << endl;
		return 1;
	}
	else
	{
		cout << " Returning 0" << endl;
		return 0;
	}
}

bool AutonomousCommands::turnDriveCommand(double angle)
{
	return false;
}

bool AutonomousCommands::getBridgeSensor()
{
	//Sensors return false when whe sensor is tripped
	return (!bridgeSensor->Get());
}
