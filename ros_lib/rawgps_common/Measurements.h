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
      float sync;
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
      offset += serializeAvrFloat64(outbuffer + offset, this->sync);
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
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->sync));
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