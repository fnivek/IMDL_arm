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
      double freq;
      double amplitude;
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
      union {
        double real;
        uint64_t base;
      } u_freq;
      u_freq.real = this->freq;
      *(outbuffer + offset + 0) = (u_freq.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_freq.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_freq.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_freq.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_freq.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_freq.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_freq.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_freq.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->freq);
      union {
        double real;
        uint64_t base;
      } u_amplitude;
      u_amplitude.real = this->amplitude;
      *(outbuffer + offset + 0) = (u_amplitude.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_amplitude.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_amplitude.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_amplitude.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_amplitude.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_amplitude.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_amplitude.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_amplitude.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->amplitude);
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
      union {
        double real;
        uint64_t base;
      } u_freq;
      u_freq.base = 0;
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_freq.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->freq = u_freq.real;
      offset += sizeof(this->freq);
      union {
        double real;
        uint64_t base;
      } u_amplitude;
      u_amplitude.base = 0;
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_amplitude.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->amplitude = u_amplitude.real;
      offset += sizeof(this->amplitude);
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