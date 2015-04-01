#ifndef _ROS_SERVICE_SetKill_h
#define _ROS_SERVICE_SetKill_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "kill_handling/Kill.h"

namespace kill_handling
{

static const char SETKILL[] = "kill_handling/SetKill";

  class SetKillRequest : public ros::Msg
  {
    public:
      kill_handling::Kill kill;
      bool clear;

    SetKillRequest():
      kill(),
      clear(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->kill.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_clear;
      u_clear.real = this->clear;
      *(outbuffer + offset + 0) = (u_clear.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->clear);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->kill.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_clear;
      u_clear.base = 0;
      u_clear.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->clear = u_clear.real;
      offset += sizeof(this->clear);
     return offset;
    }

    const char * getType(){ return SETKILL; };
    const char * getMD5(){ return "36b3474bb2b588449c666753f6d3a822"; };

  };

  class SetKillResponse : public ros::Msg
  {
    public:

    SetKillResponse()
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

    const char * getType(){ return SETKILL; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetKill {
    public:
    typedef SetKillRequest Request;
    typedef SetKillResponse Response;
  };

}
#endif
