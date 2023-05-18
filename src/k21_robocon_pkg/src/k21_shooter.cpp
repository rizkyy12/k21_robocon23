#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Int32.h"

class K21Shooter{
    private:
        ros::Subscriber joy;
        ros::Publisher shooter_pub;
        ros::Publisher relay1_pub;
        ros::Publisher relay2_pub;

    public:
        
        K21Shooter(ros::NodeHandle *nh){
            shooter_pub = nh->advertise<std_msgs::Int32>("/shooter", 10);
            joy = nh->subscribe("/joy", 10, &K21Shooter::lifterCb, this);
            // relay1_pub = nh->advertise<std_msgs::Int64>("/relay_1", 10);
            // relay2_pub = nh->advertise<std_msgs::Int64>("/relay_2", 10);
        }

    void lifterCb(const sensor_msgs::Joy& msg){
        std_msgs::Int32 shooter;
        
        if (msg.buttons[5] == 1){
            shooter.data = 1;
        }
        else{
            shooter.data = 0;
        }
        shooter_pub.publish(shooter);
        // relay1_pub.publish(relay1);
        // relay1_pub.publish(relay2);
    }
};



int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_shooter");
    ros::NodeHandle nh;
    K21Shooter K21_Shooter = K21Shooter(&nh);
    ros::spin();
}
