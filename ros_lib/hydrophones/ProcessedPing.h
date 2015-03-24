#ifndef _ROS_hydrophones_ProcessedPing_h
#define _ROS_hydrophones_ProcessedPing_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Point.h"

namespace hydrophones
{

  class ProcessedPing : public ros::Msg
  {
    public:
      std_msgs::Header header;
      geometry_msgs::Point position;
      float freq;
      float amplitude;
      bool valid;

    ProcessedPing():
      header(),
      position(),
      freq(0),
      amplitude(0),
      valid(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->position.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->freq);
      offset += serializeAvrFloat64(outbuffer + offset, this->amplitude);
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.real = this->valid;
      *(outbuffer + offset + 0) = (u_valid.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->valid);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->position.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->freq));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->amplitude));
      union {
        bool real;
        uint8_t base;
      } u_valid;
      u_valid.base = 0;
      u_valid.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->valid = u_valid.real;
      offset += sizeof(this->valid);
     return offset;
    }

    const char * getType(){ return "hydrophones/ProcessedPing"; };
    const char * getMD5(){ return "7274b91d913400a06daf68d85f949e7c"; };

  };

}
#endif