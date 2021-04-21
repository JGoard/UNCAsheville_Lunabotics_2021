#include <excavator_hw_interface/excavator_hw_interface.h>
#include <arm_handler/arm_msg.h>
#include <ros/console.h>
//#include <std_msgs/Int64.h>

    void Excavator::read(void){
        for (int ii = 0; ii <=3; ii++){
            pos[ii] = pos_cmd[ii] + 0.01;
        }

    }

    void Excavator::write(void){
        arm_handler::arm_msg target_pose;
        //std_msgs::Int64 swamp;
        for (int ii = 0; ii <=3; ii++){
            target_pose.joint = joint_hex_id[ii];
            target_pose.data = pose_conversion(pos_cmd[ii]);
            target_pose_publisher.publish(target_pose);
            //target_pose_publisher.publish(swamp);
            //ROS_INFO("published");
        }
    }
    
    void Excavator::pose_callback(const arm_handler::arm_msg& joint_pose){
        for (int ii = 0; ii <=3; ii++){
            if (joint_pose.joint == joint_hex_id[ii]){
                pos[ii] = pose_conversion(joint_pose.data);
                break;
            }
        }
        //ROS_INFO("callback hit");
    }

    uint16_t Excavator::pose_conversion(const double target){

        return (uint16_t)(RMC_encoder_resolution*target/RMC_TwoPi + RMC_shift_zero_position); 
    }

    double Excavator::pose_conversion(const uint16_t pose){

        double tmp_pose =  (double)(pose - RMC_shift_zero_position); 
        return (tmp_pose*RMC_TwoPi/RMC_encoder_resolution);
    }

    uint16_t Excavator::effort_conversion(const double target){
    
        return (uint16_t)(RMC_max_effort*target/RMC_TwoPi); 

    }
