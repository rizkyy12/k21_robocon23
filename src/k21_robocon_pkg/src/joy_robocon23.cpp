#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

class K21Main{
    private:
        ros::Subscriber joy;
        ros::Publisher vel_pub;

    public:
        K21Main(ros::NodeHandle *nh){
            vel_pub = nh->advertise<geometry_msgs::Twist>("/cmd_vel", 10);
            joy = nh->subscribe("/joy", 10, &K21Main::joyCb, this);


            // v_right_f_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/right_f_motor/command", 1);
            // v_left_f_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/left_f_motor/command", 1);
            // v_left_b_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/left_b_motor/command", 1);
            // v_right_b_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/right_b_motor/command", 1);
        }
        void joyCb(const sensor_msgs::Joy& msg){

            geometry_msgs::Twist vel;

            // Base Command ====================================================
            // Y Axis
            if (msg.axes[7] == 1){
                for (int i = 0; i < msg.axes[7]; i++){
                    vel.linear.y = i;
                }
            }
            else if(msg.axes[7] == -1){
                for (int i = -255; i < msg.axes[7]; i--){
                    vel.linear.y = i;
                }
            }

            vel_pub.publish(vel);
        }
        

};
