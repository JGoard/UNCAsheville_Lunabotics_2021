#ifndef EXCAVATOR_HARDWARE_INTERFACE_H
#define EXCAVATOR_HARDWARE_INTERFACE_H


#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <arm_handler/arm_msg.h>
#include <ros/ros.h>


class Excavator : public hardware_interface::RobotHW {
    private:
        ros::NodeHandle nh_;
        ros::Publisher target_pose_publisher;
        ros::Subscriber current_pose_subscriber;

        hardware_interface::JointStateInterface     jnt_state_interface;
        hardware_interface::PositionJointInterface  jnt_pos_interface;
        hardware_interface::VelocityJointInterface  jnt_vel_interface;
        hardware_interface::EffortJointInterface    jnt_eff_interface;

        const char   joint_hex_id[4] = {'T','C','P','D'};
        const uint16_t joint_zero[4] = {2000,2000,2000,2000};
        double pos_cmd[4];
        double vel_cmd[4];
        double eff_cmd[4];
        double pos[4];
        double vel[4];
        double eff[4];
        
    public: 

        void pose_callback(const arm_handler::arm_msg&);
        void read(void);
        void write(void);

        Excavator(ros::NodeHandle& nh):nh_(nh) { 

            #define RMC_encoder_resolution  4095
            #define RMC_max_effort           255
            #define RMC_TwoPi      6.28318530718

            current_pose_subscriber = nh_.subscribe("arm_goal", 10, &Excavator::pose_callback, this);
            target_pose_publisher   = nh_.advertise<arm_handler::arm_msg>("arm_goal", 1000);
            
            hardware_interface::JointStateHandle state_handle_waist(    "waist",    &pos[0], &vel[0], &eff[0]);
            hardware_interface::JointStateHandle state_handle_shoulder( "shoulder", &pos[1], &vel[1], &eff[1]);
            hardware_interface::JointStateHandle state_handle_elbow(    "elbow",    &pos[2], &vel[2], &eff[2]);
            hardware_interface::JointStateHandle state_handle_wrist(    "wrist",    &pos[4], &vel[3], &eff[3]);

            jnt_state_interface.registerHandle(state_handle_waist);
            jnt_state_interface.registerHandle(state_handle_shoulder); 
            jnt_state_interface.registerHandle(state_handle_elbow);
            jnt_state_interface.registerHandle(state_handle_wrist);

            registerInterface(&jnt_state_interface);

            hardware_interface::JointHandle pos_handle_waist(   jnt_state_interface.getHandle("waist"),     &pos_cmd[0]);
            hardware_interface::JointHandle pos_handle_shoulder(jnt_state_interface.getHandle("shoulder"),  &pos_cmd[1]);
            hardware_interface::JointHandle pos_handle_elbow(   jnt_state_interface.getHandle("elbow"),     &pos_cmd[2]);
            hardware_interface::JointHandle pos_handle_wrist(   jnt_state_interface.getHandle("wrist"),     &pos_cmd[3]);
                      
            jnt_pos_interface.registerHandle(pos_handle_waist);
            jnt_pos_interface.registerHandle(pos_handle_shoulder);
            jnt_pos_interface.registerHandle(pos_handle_elbow);    
            jnt_pos_interface.registerHandle(pos_handle_wrist);

            registerInterface(&jnt_pos_interface);

            hardware_interface::JointHandle vel_handle_waist(   jnt_state_interface.getHandle("waist"),     &vel_cmd[0]);
            hardware_interface::JointHandle vel_handle_shoulder(jnt_state_interface.getHandle("shoulder"),  &vel_cmd[1]);
            hardware_interface::JointHandle vel_handle_elbow(   jnt_state_interface.getHandle("elbow"),     &vel_cmd[2]);
            hardware_interface::JointHandle vel_handle_wrist(   jnt_state_interface.getHandle("wrist"),     &vel_cmd[3]);

            jnt_vel_interface.registerHandle(pos_handle_waist);
            jnt_vel_interface.registerHandle(pos_handle_shoulder);
            jnt_vel_interface.registerHandle(pos_handle_elbow);    
            jnt_vel_interface.registerHandle(pos_handle_wrist);

            registerInterface(&jnt_vel_interface);

            hardware_interface::JointHandle eff_handle_waist(   jnt_state_interface.getHandle("waist"),     &eff_cmd[0]);
            hardware_interface::JointHandle eff_handle_shoulder(jnt_state_interface.getHandle("shoulder"),  &eff_cmd[1]);
            hardware_interface::JointHandle eff_handle_elbow(   jnt_state_interface.getHandle("elbow"),     &eff_cmd[2]);
            hardware_interface::JointHandle eff_handle_wrist(   jnt_state_interface.getHandle("wrist"),     &eff_cmd[3]);

            jnt_eff_interface.registerHandle(pos_handle_waist);
            jnt_eff_interface.registerHandle(pos_handle_shoulder);
            jnt_eff_interface.registerHandle(pos_handle_elbow);    
            jnt_eff_interface.registerHandle(pos_handle_wrist);

            registerInterface(&jnt_eff_interface);
        }
};


#endif