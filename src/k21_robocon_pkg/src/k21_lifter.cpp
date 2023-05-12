#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Int64.h"

class K21Lifter{
    private:
        ros::Subscriber joy;
        ros::Publisher lifter_pub;
        ros::Publisher relay1_pub;
        ros::Publisher relay2_pub;

    public:
        
        K21Lifter(ros::NodeHandle *nh){
            lifter_pub = nh->advertise<geometry_msgs::Pose2D>("/lifter", 10);
            joy = nh->subscribe("/joy", 10, &K21Lifter::lifterCb, this);
            // relay1_pub = nh->advertise<std_msgs::Int64>("/relay_1", 10);
            // relay2_pub = nh->advertise<std_msgs::Int64>("/relay_2", 10);
        }

    void lifterCb(const sensor_msgs::Joy& msg){
        geometry_msgs::Pose2D lifter;
        std_msgs::Int64 relay1;
        std_msgs::Int64 relay2;
        
        if (msg.buttons[5] == 1){
            lifter.x = 0;
            lifter.y = 1;
        }
        else if (msg.buttons[4] == 1){
            lifter.x = 0;
            lifter.y = -1;
        }
        // else if (msg.axes[5] == 1){
        //     lifter.x = 1;
        //     lifter.y = 0;
        // }
        // else if (msg.axes[5] == -1){
        //     lifter.x = -1;
        //     lifter.y = 0;
        // }
        // else if (msg.buttons[3] == 1){
        //     relay1.data = 1;
        // }
        // else if (msg.buttons[2] == 1){
        //     relay2.data = 1;
        // }
        else{
            lifter.x = 0;
            lifter.y = 0;
            relay1.data = 0;
            relay2.data = 0;
        }
        lifter_pub.publish(lifter);
        // relay1_pub.publish(relay1);
        // relay1_pub.publish(relay2);
    }
};



int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_lifter");
    ros::NodeHandle nh;
    K21Lifter K21_Lifter = K21Lifter(&nh);
    ros::spin();
}
