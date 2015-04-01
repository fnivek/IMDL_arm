#ifndef _ROS_SERVICE_PulseValve_h
#define _ROS_SERVICE_PulseValve_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/duration.h"

namespace actuator_driver
{

static const char PULSEVALVE[] = "actuator_driver/PulseValve";

  class PulseValveRequest : public ros::Msg
  {
    public:
      uint32_t valve;
      ros::Duration duration;

    PulseValveRequest():
      valve(0),
      duration()
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
      *(outbuffer + offset + 0) = (this->duration.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration.sec);
      *(outbuffer + offset + 0) = (this->duration.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->duration.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->duration.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->duration.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->duration.nsec);
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
      this->duration.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->duration.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->duration.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->duration.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->duration.sec);
      this->duration.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->duration.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->duration.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->duration.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->duration.nsec);
     return offset;
    }

    const char * getType(){ return PULSEVALVE; };
    const char * getMD5(){ return "76dd182cead54b41e714aba31c0bdc11"; };

  };

  class PulseValveResponse : public ros::Msg
  {
    public:

    PulseValveResponse()
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

    const char * getType(){ return PULSEVALVE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class PulseValve {
    public:
    typedef PulseValveRequest Request;
    typedef PulseValveResponse Response;
  };

}
#endif
