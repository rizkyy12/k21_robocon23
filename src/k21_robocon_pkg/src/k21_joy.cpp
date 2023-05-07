#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"

class K21Joy{
    private:
        ros::Subscriber joy;
        ros::Publisher vel_pub;

    public:
        K21Joy(ros::NodeHandle *nh){
            vel_pub = nh->advertise<geometry_msgs::Twist>("/cmd_vel", 10);
            joy = nh->subscribe("/joy", 10, &K21Joy::joyCb, this);

            // v_right_f_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/right_f_motor/command", 1);
            // v_left_f_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/left_f_motor/command", 1);
            // v_left_b_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/left_b_motor/command", 1);
            // v_right_b_Command = nh->advertise<std_msgs::Float64>("/k21_robocon/right_b_motor/command", 1);
        }
        void joyCb(const sensor_msgs::Joy& msg){

            geometry_msgs::Twist vel;

            // Base Command ====================================================
            // X - Right
            if (msg.axes[0] == -1){
                vel.linear.x = 1;
                vel.linear.y = 0;
                vel.linear.z = 0;
            }
            // X - Left
            else if(msg.axes[0] == 1){
                vel.linear.x = -1;
                vel.linear.y = 0;
                vel.linear.z = 0;
            }
    
            // Y - Forward
            if (msg.axes[1] == 1){
                vel.linear.x = 0;
                vel.linear.y = 1;
                vel.linear.z = 0;
            }
            // Y - Back
            else if(msg.axes[1] == -1){
                vel.linear.x = 0;
                vel.linear.y = -1;
                vel.linear.z = 0;
            }

            // Z - Rotate right 
            if (msg.axes[2] == -1){
                vel.linear.x = 0;
                vel.linear.y = 0;
                vel.angular.z = 1;
            }
            // Z - Rotate left
            else if(msg.axes[2] == 1){
                vel.linear.x = 0;
                vel.linear.y = 0;
                vel.angular.z = -1;
            }

            vel_pub.publish(vel);
        }
        

};

int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_joy_node");
    ros::NodeHandle nh;
    K21Joy K21_Joy = K21Joy(&nh);
    ros::spin();
}
