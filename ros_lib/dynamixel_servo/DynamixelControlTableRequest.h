#ifndef _ROS_dynamixel_servo_DynamixelControlTableRequest_h
#define _ROS_dynamixel_servo_DynamixelControlTableRequest_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_servo
{

  class DynamixelControlTableRequest : public ros::Msg
  {
    public:
      uint8_t id;

    DynamixelControlTableRequest():
      id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
     return offset;
    }

    const char * getType(){ return "dynamixel_servo/DynamixelControlTableRequest"; };
    const char * getMD5(){ return "541b98e964705918fa8eb206b65347b3"; };

  };

}
#endif