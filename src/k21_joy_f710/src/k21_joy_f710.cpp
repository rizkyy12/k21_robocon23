#include <iostream>
#include <algorithm>
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>

// using namespace std;

class K21_Teleop_Joy{
    public:
        int target_linear_x = 0;
        int target_linear_y = 0;

        // double control_linear_x = 0.0;
        // double control_linear_y = 0.0;

        int MAX_BASE_LINEAR_VEL_X = 120;
        int MAX_BASE_LINEAR_VEL_Y = 120;
        // int MIN_BASE_LINEAR_VEL = -120;

        int status = 0;

        K21_Teleop_Joy();

    private:
        int linear_x_{6}, linear_y_{7}, angular_z_{3}; //from array axes[] joy
        double lin_x_step_{2.0}, lin_y_step_{2.0}, ang_z_step_{2.0};

        ros::NodeHandle nh_;
        ros::Publisher vel_pub_;
        ros::Subscriber joy_sub_;

        void joyCallback(const sensor_msgs::Joy::ConstPtr &joy);

        void vels(int target_linear_y, int target_linear_x){
            std::cout << "currently: linear vel (y) [" << target_linear_y << "] \t" << "linear vel (x) [" << target_linear_x << " ]" <<std::endl;
        }

        int constrain(int input, int low, double high){

            if (input < low){
                // output = std::min(input, output + slop);
                input = low;
            }
            else if (input > high){
                input = high;
            }
            else{
                input = input;
            }
            return input;
        }

        int checkLinearLimitVel_Y(int vel_y){
            vel_y = constrain(vel_y, -MAX_BASE_LINEAR_VEL_Y, MAX_BASE_LINEAR_VEL_Y);
            return vel_y;
        }

        int checkLinearLimitVel_X(int vel_x){
            vel_x = constrain(vel_x, -MAX_BASE_LINEAR_VEL_X, MAX_BASE_LINEAR_VEL_X);
            return vel_x;
        }
};

K21_Teleop_Joy::K21_Teleop_Joy(){
    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 1, &K21_Teleop_Joy::joyCallback, this);
}

void K21_Teleop_Joy::joyCallback(const sensor_msgs::Joy::ConstPtr &joy){
    geometry_msgs::Twist twist;

    if (joy->axes[7] == 1){
        target_linear_y = checkLinearLimitVel_Y(target_linear_y + lin_y_step_);
        status += 1;
        vels(target_linear_y, target_linear_x);
    }
    else if (joy->axes[7] == -1){
        target_linear_y = checkLinearLimitVel_Y(target_linear_y - lin_y_step_);
        status += 1;
        vels(target_linear_y, target_linear_x);
    }
    else if (joy->axes[6] == -1){
        target_linear_x = checkLinearLimitVel_Y(target_linear_x + lin_x_step_);
        status += 1;
        vels(target_linear_y, target_linear_x);
    }
    else if (joy->axes[6] == 1){
        target_linear_x = checkLinearLimitVel_Y(target_linear_x - lin_x_step_);
        status += 1;
        vels(target_linear_y, target_linear_x);
    }
    

    // control_linear_y = simpleProfile(control_linear_y, target_linear_y, (lin_y_step_/0.1));
    twist.linear.x = target_linear_x;
    twist.linear.y = target_linear_y;
    twist.linear.z = 0.0;

    vel_pub_.publish(twist);
}

int main(int argc, char **argv)
{
    // ROS_INFO("init Node");
    ros::init(argc, argv, "k21_teleop_joy_node");
    K21_Teleop_Joy K21_teleop_joy;
    ros::spin();
}
