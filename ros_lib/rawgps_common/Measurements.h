#ifndef _ROS_rawgps_common_Measurements_h
#define _ROS_rawgps_common_Measurements_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "rawgps_common/Satellite.h"

namespace rawgps_common
{

  class Measurements : public ros::Msg
  {
    public:
      std_msgs::Header header;
      double sync;
      uint8_t satellites_length;
      rawgps_common::Satellite st_satellites;
      rawgps_common::Satellite * satellites;

    Measurements():
      header(),
      sync(0),
      satellites_length(0), satellites(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_sync;
      u_sync.real = this->sync;
      *(outbuffer + offset + 0) = (u_sync.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sync.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sync.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sync.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_sync.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_sync.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_sync.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_sync.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->sync);
      *(outbuffer + offset++) = satellites_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < satellites_length; i++){
      offset += this->satellites[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_sync;
      u_sync.base = 0;
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_sync.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->sync = u_sync.real;
      offset += sizeof(this->sync);
      uint8_t satellites_lengthT = *(inbuffer + offset++);
      if(satellites_lengthT > satellites_length)
        this->satellites = (rawgps_common::Satellite*)realloc(this->satellites, satellites_lengthT * sizeof(rawgps_common::Satellite));
      offset += 3;
      satellites_length = satellites_lengthT;
      for( uint8_t i = 0; i < satellites_length; i++){
      offset += this->st_satellites.deserialize(inbuffer + offset);
        memcpy( &(this->satellites[i]), &(this->st_satellites), sizeof(rawgps_common::Satellite));
      }
     return offset;
    }

    const char * getType(){ return "rawgps_common/Measurements"; };
    const char * getMD5(){ return "da563d3164f0154b7db4c10d39423440"; };

  };

}
#endif