#ifndef _ROS_motor_control_thrusterPWM_h
#define _ROS_motor_control_thrusterPWM_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace motor_control
{

  class thrusterPWM : public ros::Msg
  {
    public:
      uint8_t id;
      int32_t pulse_width;

    thrusterPWM():
      id(0),
      pulse_width(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_pulse_width;
      u_pulse_width.real = this->pulse_width;
      *(outbuffer + offset + 0) = (u_pulse_width.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pulse_width.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pulse_width.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pulse_width.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pulse_width);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      union {
        int32_t real;
        uint32_t base;
      } u_pulse_width;
      u_pulse_width.base = 0;
      u_pulse_width.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pulse_width.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pulse_width.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pulse_width.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pulse_width = u_pulse_width.real;
      offset += sizeof(this->pulse_width);
     return offset;
    }

    const char * getType(){ return "motor_control/thrusterPWM"; };
    const char * getMD5(){ return "02a186353581fef1ea1ee9f9a1321c55"; };

  };

}
#endif