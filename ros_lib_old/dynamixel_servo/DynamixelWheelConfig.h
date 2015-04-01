#ifndef _ROS_dynamixel_servo_DynamixelWheelConfig_h
#define _ROS_dynamixel_servo_DynamixelWheelConfig_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_servo
{

  class DynamixelWheelConfig : public ros::Msg
  {
    public:
      uint8_t id;
      float moving_speed;

    DynamixelWheelConfig():
      id(0),
      moving_speed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      union {
        float real;
        uint32_t base;
      } u_moving_speed;
      u_moving_speed.real = this->moving_speed;
      *(outbuffer + offset + 0) = (u_moving_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_moving_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_moving_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_moving_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->moving_speed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      union {
        float real;
        uint32_t base;
      } u_moving_speed;
      u_moving_speed.base = 0;
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->moving_speed = u_moving_speed.real;
      offset += sizeof(this->moving_speed);
     return offset;
    }

    const char * getType(){ return "dynamixel_servo/DynamixelWheelConfig"; };
    const char * getMD5(){ return "b6049b70fb06ed4bff3a0aea3dcf2849"; };

  };

}
#endif