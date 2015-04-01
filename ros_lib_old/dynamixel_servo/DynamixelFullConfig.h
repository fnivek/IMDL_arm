#ifndef _ROS_dynamixel_servo_DynamixelFullConfig_h
#define _ROS_dynamixel_servo_DynamixelFullConfig_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_servo
{

  class DynamixelFullConfig : public ros::Msg
  {
    public:
      uint8_t id;
      uint8_t led;
      float goal_position;
      float moving_speed;
      uint16_t torque_limit;
      float goal_acceleration;
      uint8_t control_mode;
      float goal_velocity;
      enum { JOINT = 1 };
      enum { WHEEL = 2 };
      enum { MULTI_TURN = 3 };
      enum { CONTINUOUS_ANGLE = 4 };

    DynamixelFullConfig():
      id(0),
      led(0),
      goal_position(0),
      moving_speed(0),
      torque_limit(0),
      goal_acceleration(0),
      control_mode(0),
      goal_velocity(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      *(outbuffer + offset + 0) = (this->led >> (8 * 0)) & 0xFF;
      offset += sizeof(this->led);
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
      } u_moving_speed;
      u_moving_speed.real = this->moving_speed;
      *(outbuffer + offset + 0) = (u_moving_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_moving_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_moving_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_moving_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->moving_speed);
      *(outbuffer + offset + 0) = (this->torque_limit >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->torque_limit >> (8 * 1)) & 0xFF;
      offset += sizeof(this->torque_limit);
      union {
        float real;
        uint32_t base;
      } u_goal_acceleration;
      u_goal_acceleration.real = this->goal_acceleration;
      *(outbuffer + offset + 0) = (u_goal_acceleration.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_goal_acceleration.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_goal_acceleration.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_goal_acceleration.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->goal_acceleration);
      *(outbuffer + offset + 0) = (this->control_mode >> (8 * 0)) & 0xFF;
      offset += sizeof(this->control_mode);
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
      this->led =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->led);
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
      } u_moving_speed;
      u_moving_speed.base = 0;
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_moving_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->moving_speed = u_moving_speed.real;
      offset += sizeof(this->moving_speed);
      this->torque_limit =  ((uint16_t) (*(inbuffer + offset)));
      this->torque_limit |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->torque_limit);
      union {
        float real;
        uint32_t base;
      } u_goal_acceleration;
      u_goal_acceleration.base = 0;
      u_goal_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_goal_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_goal_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_goal_acceleration.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->goal_acceleration = u_goal_acceleration.real;
      offset += sizeof(this->goal_acceleration);
      this->control_mode =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->control_mode);
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

    const char * getType(){ return "dynamixel_servo/DynamixelFullConfig"; };
    const char * getMD5(){ return "07d4788c242d90fba96b7af7c56f6860"; };

  };

}
#endif