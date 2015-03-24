#ifndef _ROS_dynamixel_servo_DynamixelJointConfig_h
#define _ROS_dynamixel_servo_DynamixelJointConfig_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_servo
{

  class DynamixelJointConfig : public ros::Msg
  {
    public:
      uint8_t id;
      float goal_position;

    DynamixelJointConfig():
      id(0),
      goal_position(0)
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
      } u_goal_position;
      u_goal_position.real = this->goal_position;
      *(outbuffer + offset + 0) = (u_goal_position.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_goal_position.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_goal_position.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_goal_position.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->goal_position);
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
      } u_goal_position;
      u_goal_position.base = 0;
      u_goal_position.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_goal_position.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_goal_position.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_goal_position.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->goal_position = u_goal_position.real;
      offset += sizeof(this->goal_position);
     return offset;
    }

    const char * getType(){ return "dynamixel_servo/DynamixelJointConfig"; };
    const char * getMD5(){ return "df447e3220d9021d6415f1a9fe74b13d"; };

  };

}
#endif