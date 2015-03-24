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
      float thrust;

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
      offset += serializeAvrFloat64(outbuffer + offset, this->thrust);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->id =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->id);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->thrust));
     return offset;
    }

    const char * getType(){ return "motor_control/thrusterNewtons"; };
    const char * getMD5(){ return "5f85b19e28e8f7e124fb2a35c15d5be5"; };

  };

}
#endif