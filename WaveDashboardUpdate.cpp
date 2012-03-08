#include "WPILib.h"
#include "WaveDashboardUpdate.hpp"





WaveDashboardUpdate::WaveDashboardUpdate(WaveWheelControl *wheelControl)
{
	isSystemTargeted = false;
	isShooterAtSpeed = false;
	targetDistance = 0;
	launcher = wheelControl;
}

void WaveDashboardUpdate::updateDistance(double distanceToTarget)
{
	targetDistance = distanceToTarget;	
}

void WaveDashboardUpdate::updateTarget(bool systemTargeted)
{
	isSystemTargeted = systemTargeted; 
}

void WaveDashboardUpdate::updateSpeed (bool shooterAtSpeed)
{
	isShooterAtSpeed = shooterAtSpeed;
}


void WaveDashboardUpdate::run() 
{
	Dashboard &d = DriverStation::GetInstance()->GetLowPriorityDashboardPacker();
	d.AddCluster(); {
		d.AddBoolean(isSystemTargeted);
		d.AddBoolean(isShooterAtSpeed);
		d.AddDouble(targetDistance);
		d.AddDouble(launcher->getSpeedSet());
		d.AddDouble(launcher->PIDGet());
	}
    d.FinalizeCluster();
    d.Finalize();
}
//void RectangleTracker::SendVisionData() {
//    Dashboard &d = DriverStation::GetInstance()->GetHighPriorityDashboardPacker();
//    int n = (numCurrentMatches <= 10) ? numCurrentMatches : 10;
//    d.AddCluster(); {
//        d.AddArray(); {
//        for (int i = 0; i < n; i++) {
//                d.AddCluster(); {
//                    d.AddI16((INT16)matches[i].corner[0].y);
//                    d.AddI16((INT16)matches[i].corner[0].x);
//                    d.AddI16((INT16)matches[i].corner[2].y);
//                    d.AddI16((INT16)matches[i].corner[2].x);
//                }9
//                d.FinalizeCluster();
//            }
//        }
//        d.FinalizeArray();
//    }
//    d.FinalizeCluster();
//    d.Finalize();
//}
