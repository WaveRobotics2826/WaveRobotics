#include "AutonomousCommands.hpp"
#include <iostream>

using namespace std;

AutonomousCommands::AutonomousCommands(WaveDrive *drive)
{
	this->drive = drive;
}

bool AutonomousCommands::forwardReverseDriveCommand(double speed, double distance)
{
	cout << "traveled " << drive->getDistanceTraveled() << " ";
	if(drive->getDistanceTraveled() > (distance * .9))
	{
		cout << "run slow" << endl;
		drive->setLeftMotor(speed * .5);
		drive->setRightMotor(speed * .5);
	}
	else
	{
		cout << "run fast" << endl;
		drive->setLeftMotor(speed);
		drive->setRightMotor(speed);
	}
	return (drive->getDistanceTraveled() > distance);
}

bool AutonomousCommands::turnDriveCommand(double angle)
{
	return false;
}
