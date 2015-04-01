#ifndef _ROS_SERVICE_SetValve_h
#define _ROS_SERVICE_SetValve_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace actuator_driver
{

static const char SETVALVE[] = "actuator_driver/SetValve";

  class SetValveRequest : public ros::Msg
  {
    public:
      uint32_t valve;
      bool opened;

    SetValveRequest():
      valve(0),
      opened(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->valve >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->valve >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->valve >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->valve >> (8 * 3)) & 0xFF;
      offset += sizeof(this->valve);
      union {
        bool real;
        uint8_t base;
      } u_opened;
      u_opened.real = this->opened;
      *(outbuffer + offset + 0) = (u_opened.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->opened);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->valve =  ((uint32_t) (*(inbuffer + offset)));
      this->valve |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->valve |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->valve |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->valve);
      union {
        bool real;
        uint8_t base;
      } u_opened;
      u_opened.base = 0;
      u_opened.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->opened = u_opened.real;
      offset += sizeof(this->opened);
     return offset;
    }

    const char * getType(){ return SETVALVE; };
    const char * getMD5(){ return "281eb6902a057d5d7b3d928b4766e164"; };

  };

  class SetValveResponse : public ros::Msg
  {
    public:

    SetValveResponse()
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

    const char * getType(){ return SETVALVE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetValve {
    public:
    typedef SetValveRequest Request;
    typedef SetValveResponse Response;
  };

}
#endif
