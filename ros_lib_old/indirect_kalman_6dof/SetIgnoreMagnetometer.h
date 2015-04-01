#ifndef _ROS_SERVICE_SetIgnoreMagnetometer_h
#define _ROS_SERVICE_SetIgnoreMagnetometer_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace indirect_kalman_6dof
{

static const char SETIGNOREMAGNETOMETER[] = "indirect_kalman_6dof/SetIgnoreMagnetometer";

  class SetIgnoreMagnetometerRequest : public ros::Msg
  {
    public:
      bool ignore;

    SetIgnoreMagnetometerRequest():
      ignore(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ignore;
      u_ignore.real = this->ignore;
      *(outbuffer + offset + 0) = (u_ignore.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ignore);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_ignore;
      u_ignore.base = 0;
      u_ignore.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ignore = u_ignore.real;
      offset += sizeof(this->ignore);
     return offset;
    }

    const char * getType(){ return SETIGNOREMAGNETOMETER; };
    const char * getMD5(){ return "24805c685e7661cfbb5dbdde9c235228"; };

  };

  class SetIgnoreMagnetometerResponse : public ros::Msg
  {
    public:

    SetIgnoreMagnetometerResponse()
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

    const char * getType(){ return SETIGNOREMAGNETOMETER; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetIgnoreMagnetometer {
    public:
    typedef SetIgnoreMagnetometerRequest Request;
    typedef SetIgnoreMagnetometerResponse Response;
  };

}
#endif
