#ifndef _ROS_arm_subscriber_arm_msg_h
#define _ROS_arm_subscriber_arm_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace arm_subscriber
{

  class arm_msg : public ros::Msg
  {
    public:
      typedef uint8_t _joint_type;
      _joint_type joint;
      typedef uint16_t _data_type;
      _data_type data;

    arm_msg():
      joint(0),
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->joint >> (8 * 0)) & 0xFF;
      offset += sizeof(this->joint);
      *(outbuffer + offset + 0) = (this->data >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data >> (8 * 1)) & 0xFF;
      offset += sizeof(this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->joint =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->joint);
      this->data =  ((uint16_t) (*(inbuffer + offset)));
      this->data |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->data);
     return offset;
    }

    const char * getType(){ return "arm_subscriber/arm_msg"; };
    const char * getMD5(){ return "43dc75f8dbe81d216f7a006d646aaaf6"; };

  };

}
#endif