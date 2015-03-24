#ifndef _ROS_SERVICE_SetDisabled_h
#define _ROS_SERVICE_SetDisabled_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace c3_trajectory_generator
{

static const char SETDISABLED[] = "c3_trajectory_generator/SetDisabled";

  class SetDisabledRequest : public ros::Msg
  {
    public:
      bool disabled;

    SetDisabledRequest():
      disabled(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_disabled;
      u_disabled.real = this->disabled;
      *(outbuffer + offset + 0) = (u_disabled.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->disabled);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_disabled;
      u_disabled.base = 0;
      u_disabled.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->disabled = u_disabled.real;
      offset += sizeof(this->disabled);
     return offset;
    }

    const char * getType(){ return SETDISABLED; };
    const char * getMD5(){ return "c21e89d4890f5b82aef31177d9a40521"; };

  };

  class SetDisabledResponse : public ros::Msg
  {
    public:

    SetDisabledResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SETDISABLED; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetDisabled {
    public:
    typedef SetDisabledRequest Request;
    typedef SetDisabledResponse Response;
  };

}
#endif
