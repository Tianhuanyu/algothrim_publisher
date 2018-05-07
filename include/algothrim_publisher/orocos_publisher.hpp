#include "ros/ros.h"
#include "sensor_msgs/JointState.h"


enum OPERATION_MODE{POSITION_MODE,
                    VELOCITY_MODE,
                    TORQUE_MODE};

enum CONTROL_MODE{COMMAND,
                FRAME_BASE_CONTROL,
                SCREW_BASE_CONTROL,
                TWIST_BASE_CONTROL};


struct FRAME{
    float point[3] = {0,0,0};
    float orientation[4] = {0,0,0,0};
};

struct TWIST{
    float linear[3] = {0,0,0};
    float angular[3] = {0,0,0};
};

/*Struct for robot hardware interface*/

struct RGM_ROBOT{

    /*push to CANopen slave*/
    float target_position[6] ={0,0,0,0,0,0};
    float target_velocity[6] ={0,0,0,0,0,0};
    float target_torque[6] ={0,0,0,0,0,0};

    /*pull from CANopen slave*/
    float actual_position[6] ={0,0,0,0,0,0};
    float actual_velocity[6] ={0,0,0,0,0,0};
    float actual_torque[6] ={0,0,0,0,0,0};

    OPERATION_MODE operation_mode = VELOCITY_MODE;
    CONTROL_MODE control_mode = COMMAND;

    /*listen from pc*/
    FRAME target_tcp_frame;
    TWIST target_tcp_twist;

    /*report to pc*/
    FRAME actual_tcp_frame;
    TWIST actual_tcp_twist;
    
};
