#ifndef _ROS_SERVICE_SetKill_h
#define _ROS_SERVICE_SetKill_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace power_router
{

static const char SETKILL[] = "power_router/SetKill";

  class SetKillRequest : public ros::Msg
  {
    public:
      bool kill;

    SetKillRequest():
      kill(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_kill;
      u_kill.real = this->kill;
      *(outbuffer + offset + 0) = (u_kill.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->kill);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_kill;
      u_kill.base = 0;
      u_kill.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->kill = u_kill.real;
      offset += sizeof(this->kill);
     return offset;
    }

    const char * getType(){ return SETKILL; };
    const char * getMD5(){ return "4557a92c5732dcee9b7fc1c4b73630d5"; };

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
