#ifndef _ROS_dynamixel_servo_DynamixelStatus_h
#define _ROS_dynamixel_servo_DynamixelStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace dynamixel_servo
{

  class DynamixelStatus : public ros::Msg
  {
    public:
      uint8_t id;
      float goal_position;
      float moving_speed;
      uint16_t torque_limit;
      float present_position;
      float present_speed;
      uint16_t present_load;
      float present_voltage;
      uint8_t present_temp;
      uint8_t registered;
      uint8_t is_moving;

    DynamixelStatus():
      id(0),
      goal_position(0),
      moving_speed(0),
      torque_limit(0),
      present_position(0),
      present_speed(0),
      present_load(0),
      present_voltage(0),
      present_temp(0),
      registered(0),
      is_moving(0)
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
      } u_present_position;
      u_present_position.real = this->present_position;
      *(outbuffer + offset + 0) = (u_present_position.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_present_position.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_present_position.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_present_position.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->present_position);
      union {
        float real;
        uint32_t base;
      } u_present_speed;
      u_present_speed.real = this->present_speed;
      *(outbuffer + offset + 0) = (u_present_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_present_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_present_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_present_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->present_speed);
      *(outbuffer + offset + 0) = (this->present_load >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->present_load >> (8 * 1)) & 0xFF;
      offset += sizeof(this->present_load);
      union {
        float real;
        uint32_t base;
      } u_present_voltage;
      u_present_voltage.real = this->present_voltage;
      *(outbuffer + offset + 0) = (u_present_voltage.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_present_voltage.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_present_voltage.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_present_voltage.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->present_voltage);
      *(outbuffer + offset + 0) = (this->present_temp >> (8 * 0)) & 0xFF;
      offset += sizeof(this->present_temp);
      *(outbuffer + offset + 0) = (this->registered >> (8 * 0)) & 0xFF;
      offset += sizeof(this->registered);
      *(outbuffer + offset + 0) = (this->is_moving >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_moving);
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
      } u_present_position;
      u_present_position.base = 0;
      u_present_position.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_present_position.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_present_position.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_present_position.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->present_position = u_present_position.real;
      offset += sizeof(this->present_position);
      union {
        float real;
        uint32_t base;
      } u_present_speed;
      u_present_speed.base = 0;
      u_present_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_present_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_present_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_present_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->present_speed = u_present_speed.real;
      offset += sizeof(this->present_speed);
      this->present_load =  ((uint16_t) (*(inbuffer + offset)));
      this->present_load |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->present_load);
      union {
        float real;
        uint32_t base;
      } u_present_voltage;
      u_present_voltage.base = 0;
      u_present_voltage.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_present_voltage.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_present_voltage.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_present_voltage.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->present_voltage = u_present_voltage.real;
      offset += sizeof(this->present_voltage);
      this->present_temp =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->present_temp);
      this->registered =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->registered);
      this->is_moving =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->is_moving);
     return offset;
    }

    const char * getType(){ return "dynamixel_servo/DynamixelStatus"; };
    const char * getMD5(){ return "234b437d1e9c542f19df608f6acb8ec6"; };

  };

}
#endif