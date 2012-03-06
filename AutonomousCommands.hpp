#include <limits>
#include "WPILib.h"
#include "WaveDrive.hpp"

using namespace std;

class AutonomousCommands
{
public:
  AutonomousCommands(WaveDrive *drive);
  
  bool forwardReverseDriveCommand(double speed, double distance = 100000000);
  
  /// -1 to 1, 0 is straight
  bool turnDriveCommand(double angle);
  
  /// returns true when the bridge sensor is tripped
  bool getBridgeSensor();
  
private:
  WaveDrive *drive;
  
  DigitalInput *bridgeSensor;
};
