#ifndef CHANNEL_NAMES
#define CHANNEL_NAMES

// Declarations for use in creating WPI objects
namespace Channels
{
//Notes for operation that isn't obvious
//--------------------------------------------------------------------------------
//Analog Card (slot 1)
const int Turret_Angle_Sensor =     1;
//  2 -
//  3 -
//  4 -
//  5 -
//  6 -
//  7 -
//  8 -
//-------------------------------------------------------
//Digital SideCard 1 (slot 2)
//  PWM
const int Left_Motor_1 =            1;
const int Left_Motor_2 =            2;
const int Right_Motor_1 =           3;
const int Right_Motor_2 =           4;
const int Intake_Motor =            5;
//    6 - 
//    7 -
//    8 -
    
//  D I/O
const int Compressor_Presure_Switch = 1;
const int Lower_Tower_Sensor =        2;
const int Bridge_Sensor =             3;
const int Elevator_Sensor_Rt =        4;
const int Top_Tower_Sensor =          5;
const int Elevator_Sensor_Lt =        6;
//     7
const int Right_Encoder_A =           8;
const int Right_Encoder_B =           9;
//    10
const int Left_Encoder_A =           11;
const int Left_Encoder_B =           12;
  
//  Relay
const int Compressor =              1;
//    2 -
//    3 -
//    4 -
//    5 -
//    6 -
//    7 -
//    8 -
//----------------------------------------------------
//Digital Side Card 2 (slot 4)
//  PWM
const int Shooter_Motor_1 =         10;   
const int Shooter_Motor_2 =         9;
const int Shooter_Motor_3 =         8;
const int Shooter_Motor_4 =         7;
const int Delivery_Motor =          6;
const int Turret_Motor_1 =          5;
const int Turret_Motor_2 =          4;

    
//  D I/O
const int Shooter_Sensor =          1;
//    2 - 
//    3 -
//    4 -
//    5 -
//    6 -
//    7 -
//    8 -
//    9 -
//    10-
//    11-
//    12-
//    13-
//    14-
    
//  Relay
//    1 -
//    2 -
//    3 -
//    4 -
//    5 -

//    6 -
//    7 -
//    8 -
//----------------------------------------------------  
//Digital Output Card (slot 3)
const int Shift_Default =                   1;
const int Short_Cylinder_Solenoid =   		2;
const int Long_Cylinder_Solenoid = 			3;
//  4 -
//  5 - 
//  6 -
//  7 -
//  8 -
}
#endif
