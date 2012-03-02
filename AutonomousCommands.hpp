#include <limits>
#include "WaveDrive.hpp"

using namespace std;

class AutonomousCommands
{
public:
  AutonomousCommands(WaveDrive *drive);
  
  bool forwardReverseDriveCommand(double speed, double distance = 100000000);
  
  /// -1 to 1, 0 is straight
  bool turnDriveCommand(double angle);
  
private:
  WaveDrive *drive;
};
