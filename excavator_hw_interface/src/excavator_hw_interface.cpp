#include <excavator_hw_interface/excavator_hw_interface.h>
#include <arm_handler/arm_msg.h>
#include <ros/console.h>

    void Excavator::read(void){ // not called in main, used as passthrough to debug compile errors in node
        for (int ii = 0; ii <=3; ii++){
            pos[ii] = pos_cmd[ii] + 0.01;
        }
    }

    void Excavator::write(void){
        arm_handler::arm_msg target_pose;
        uint16_t tmp_goal;
        for (int ii = 0; ii <=3; ii++){
            target_pose.data = 50*vel_cmd[ii] + 256;
            target_pose.joint = joint_hex_id[ii];
            target_pose_publisher.publish(target_pose);
        }
    }
    
    void Excavator::pose_callback(const arm_handler::arm_msg& joint_pose){
        double tmp_pose;
        for (int ii = 0; ii <=3; ii++){
            if (joint_pose.joint == joint_hex_id[ii]){
                tmp_pose = joint_pose.data - joint_zero[ii];
                pos[ii] = ((tmp_pose*RMC_TwoPi)/RMC_encoder_resolution);
                break;
            }
        }
    }

