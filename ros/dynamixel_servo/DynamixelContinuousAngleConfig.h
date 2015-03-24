#ifndef _ROS_dynamixel_servo_DynamixelContinuousAngleConfig_h
#define _ROS_dynamixel_servo_DynamixelContinuousAngleConfig_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_servo
{

  class DynamixelContinuousAngleConfig : public ros::Msg
  {
    public:
      uint8_t id;
      float goal_position;
      float goal_velocity;

    DynamixelContinuousAngleConfig():
      id(0),
      goal_position(0),
      goal_velocity(0)
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
      union {
        float real;
        uint32_t base;
      } u_goal_velocity;
      u_goal_velocity.real = this->goal_velocity;
      *(outbuffer + offset + 0) = (u_goal_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_goal_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_goal_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_goal_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->goal_velocity);
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
      union {
        float real;
        uint32_t base;
      } u_goal_velocity;
      u_goal_velocity.base = 0;
      u_goal_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_goal_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_goal_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_goal_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->goal_velocity = u_goal_velocity.real;
      offset += sizeof(this->goal_velocity);
     return offset;
    }

    const char * getType(){ return "dynamixel_servo/DynamixelContinuousAngleConfig"; };
    const char * getMD5(){ return "57384c08ade8d92b97edd74572ad4ea9"; };

  };

}
#endif