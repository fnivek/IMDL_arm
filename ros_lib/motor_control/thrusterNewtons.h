#ifndef _ROS_motor_control_thrusterNewtons_h
#define _ROS_motor_control_thrusterNewtons_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace motor_control
{

  class thrusterNewtons : public ros::Msg
  {
    public:
      uint8_t id;
      double thrust;

    thrusterNewtons():
      id(0),
      thrust(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      union {
        double real;
        uint64_t base;
      } u_thrust;
      u_thrust.real = this->thrust;
      *(outbuffer + offset + 0) = (u_thrust.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_thrust.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_thrust.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_thrust.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_thrust.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_thrust.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_thrust.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_thrust.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->thrust);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      union {
        double real;
        uint64_t base;
      } u_thrust;
      u_thrust.base = 0;
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_thrust.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->thrust = u_thrust.real;
      offset += sizeof(this->thrust);
     return offset;
    }

    const char * getType(){ return "motor_control/thrusterNewtons"; };
    const char * getMD5(){ return "5f85b19e28e8f7e124fb2a35c15d5be5"; };

  };

}
#endif