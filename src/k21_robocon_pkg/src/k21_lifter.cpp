#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Pose2D.h"

class K21Lifter{
    private:
        ros::Subscriber joy;
        ros::Publisher lifter_pub;

    public:
        
        K21Lifter(ros::NodeHandle *nh){
            lifter_pub = nh->advertise<geometry_msgs::Pose2D>("/lifter", 10);
            joy = nh->subscribe("/joy", 10, &K21Lifter::lifterCb, this);
        }

    void lifterCb(const sensor_msgs::Joy& msg){
        geometry_msgs::Pose2D lifter;
        if (msg.buttons[5] == 1){
            lifter.x = 0;
            lifter.y = 1;
        }
        else if (msg.buttons[4] == 1){
            lifter.x = 0;
            lifter.y = -1;
        }
        else if (msg.axes[5] == 1){
            lifter.x = 1;
            lifter.y = 0;
        }
        else if (msg.axes[5] == -1){
            lifter.x = -1;
            lifter.y = 0;
        }
        else{
            lifter.x = 0;
            lifter.y = 0;
        }
        lifter_pub.publish(lifter);
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
