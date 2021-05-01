#include <excavator_hw_interface/excavator_hw_interface.h>
#include <controller_manager/controller_manager.h>
#include <ros/console.h>
#include <ros/ros.h>
#include <sstream>


int main(int argc, char **argv){
    ros::init(argc, argv, "excavator_hw_interface");
    ros::NodeHandle nh;
    
    Excavator robot(nh);
 
    controller_manager::ControllerManager cm(&robot);

    ros::AsyncSpinner spinner(1);
    spinner.start();
    
    ros::Time prev_time = ros::Time::now();
    ros::Rate rate(10.0); // 10 Hz rate
    
    ROS_INFO("RMC Excavator Hardware Interface Online");

    rate.sleep();

    while (ros::ok()){
        const ros::Time time = ros::Time::now();
        const ros::Duration period = time - prev_time;
        
        //robot.read();
        cm.update(time, period);
        robot.write();
        rate.sleep();
    }
    return 0;
}