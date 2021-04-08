# Lunabotics Github for Backhoe Arm and Wheel Assemblies

4/8/2021
 ROS Odometry control has been given to at least one side of the rover, needs pins for rovers other side of motor control. 
 Wheel Node Teensy will now control hardware interrupts from a hall effect channel of DC motors driving rover to gain an accurate pose.
 

3/25/2021
 Teensy Arm Node is setup now to communicate with multiple encoders, as well as having dualshock4 integration with ROS in order to control it (creds to Nick Schneider)
 Wheel Node idea is being switched to only taking hardware interrupts of hall effect channels as they rise.

3/17/2021
 Teensy Arm Node has been set up and is able to coninually poll AMT-CUI Encoders on RS-485 line
 Currently in middle of creating advertising service for to control motors w.r.t current encoder positions
 and values.

 
 
 
