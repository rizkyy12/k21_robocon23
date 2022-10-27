#!/usr/bin/env python3
from numpy import rate
import rospy
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Pose2D

# dir1 = 0
# dir2 = 0
# dir3 = 0
# dir4 = 0
# rpm_m1 = 0.0
# rpm_m2 = 0.0
# rpm_m3 = 0.0
# rpm_m4 = 0.0
# m_1 = 0 
# m_2 = 0 
# m_3 = 0 
# m_4 = 0

def getSpeed(data):
    global Vx, Vy, w
    Vx = data.linear.x
    Vy = data.linear.y
    if data.angular.x == 1:
        w = -20
    elif data.angular.y == 1:
        w = 20
    else:
        w = 0

    if Vy == 1:
        Vx = 0
        Vy = 20
        w = 0
    elif Vy == -1:
        Vx = 0
        Vy = -20
        w = 0
    elif Vx == 1:
        Vx = 20
        Vy = 0
        w = 0
    elif Vx == -1:
        Vx = -20
        Vy = 0
        w = 0
    elif w == 1:
        Vx = 0
        Vy = 0
        w = 20
    elif w == -1:
        Vx = 0
        Vy = 0
        w = -20
    elif Vx == 1 and Vy == 1:
        Vx = 20
        Vy = 20
        w = 0
    elif Vx == -1 and Vy == -1:
        Vx = -20
        Vy = -20
        w = 0
    elif Vx == -1 and Vy == 1:
        Vx = -20
        Vy = 20
        w = 0
    elif Vx == 1 and Vy == -1:
        Vx = 20
        Vy = -20
        w = 0
    elif Vx == 0 and Vy == 0 and w == 0:
        Vx = 0
        Vy = 0
        w = 0
    
    vx = Vx
    vy = Vy
    # 0.471 = R dari pusat ke roda
    motor1 = 0.7071 * (vy - vx) + (w * 0.471)
    # Convert from cm/s to rpm
    # rpm = m/s * (60/2*phi*r(cm)(keliling Lingkaran))
    rpm_m1 = motor1 * 1.504050
    if rpm_m1 > 0:
        dir1 = 1
    elif rpm_m1 < 0:
        dir1 = -1
    else:
        rpm_m1 = 0
        dir1 = 0

    # 0.471 = R dari pusat ke roda
    motor2 = 0.7071 * -(vy + vx) + (w * 0.471)
    # Convert from cm/s to rpm
    # rpm = m/s * (60/2*phi*r(cm)(keliling Lingkaran))
    rpm_m2 = motor2 * 1.504050
    if rpm_m2 > 0:
        dir2 = 1
    elif rpm_m2 < 0:
        dir2 = -1
    else:
        rpm_m2 = 0
        dir2 = 0

    # 0.471 = R dari pusat ke roda
    motor3 = 0.7071 * (vx - vy) + (w * 0.471)
    # Convert from cm/s to rpm
    # rpm = m/s * (60/2*phi*r(cm)(keliling Lingkaran))
    rpm_m3 = motor3 * 1.504050
    if rpm_m3 > 0:
        dir3 = 1
    elif rpm_m3 < 0:
        dir3 = -1
    else:
        rpm_m3 = 0
        dir3 = 0

    # 0.471 = R dari pusat ke roda
    motor4 = 0.7071 * (vx + vy) + (w * 0.471)
    # Convert from cm/s to rpm
    # rpm = m/s * (60/2*phi*r(cm)(keliling Lingkaran))
    rpm_m4 = motor4 * 1.504050
    if rpm_m4 > 0:
        dir4 = 1
    elif rpm_m4 < 0:
        dir4 = -1
    else:
        rpm_m4 = 0
        dir4 = 0
    
    m_1 = Pose2D()
    m_2 = Pose2D()
    m_3 = Pose2D()
    m_4 = Pose2D()
    
    # Motor 1
    m_1.x = rpm_m1
    m_1.y = dir1 
    # Motor 2
    m_2.x = rpm_m2
    m_2.y = dir2
    # Motor 3
    m_3.x = rpm_m3
    m_3.y = dir3
    # Motor 4
    m_4.x = rpm_m4
    m_4.y = dir4

    m1.publish(m_1)
    m2.publish(m_2)
    m3.publish(m_3)
    m4.publish(m_4)
    rate.sleep()

def rosStart():
    global m1, m2, m3, m4, rate
    rospy.init_node('Kinematics', anonymous = False)
    rate = rospy.Rate(20)
    m1 = rospy.Publisher('/motorRPM1', Pose2D, queue_size=1)
    m2 = rospy.Publisher('/motorRPM2', Pose2D, queue_size=1)
    m3 = rospy.Publisher('/motorRPM3', Pose2D, queue_size=1)
    m4 = rospy.Publisher('/motorRPM4', Pose2D, queue_size=1)
    rospy.Subscriber("/cmd_vel", Twist, getSpeed)
    rospy.spin()
    # while not rospy.is_shutdown():
    #     kine(Vx, Vy, w)

if __name__ == '__main__':
    try:
        rosStart()
    except rospy.ROSInterruptException:
        pass