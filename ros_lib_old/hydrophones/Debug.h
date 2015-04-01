#ifndef _ROS_hydrophones_Debug_h
#define _ROS_hydrophones_Debug_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace hydrophones
{

  class Debug : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t deltas_length;
      float st_deltas;
      float * deltas;
      uint8_t delta_errors_length;
      float st_delta_errors;
      float * delta_errors;
      float fft_sharpness;
      float heading;
      float declination;

    Debug():
      header(),
      deltas_length(0), deltas(NULL),
      delta_errors_length(0), delta_errors(NULL),
      fft_sharpness(0),
      heading(0),
      declination(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = deltas_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < deltas_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->deltas[i]);
      }
      *(outbuffer + offset++) = delta_errors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < delta_errors_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_errors[i]);
      }
      offset += serializeAvrFloat64(outbuffer + offset, this->fft_sharpness);
      offset += serializeAvrFloat64(outbuffer + offset, this->heading);
      offset += serializeAvrFloat64(outbuffer + offset, this->declination);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t deltas_lengthT = *(inbuffer + offset++);
      if(deltas_lengthT > deltas_length)
        this->deltas = (float*)realloc(this->deltas, deltas_lengthT * sizeof(float));
      offset += 3;
      deltas_length = deltas_lengthT;
      for( uint8_t i = 0; i < deltas_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_deltas));
        memcpy( &(this->deltas[i]), &(this->st_deltas), sizeof(float));
      }
      uint8_t delta_errors_lengthT = *(inbuffer + offset++);
      if(delta_errors_lengthT > delta_errors_length)
        this->delta_errors = (float*)realloc(this->delta_errors, delta_errors_lengthT * sizeof(float));
      offset += 3;
      delta_errors_length = delta_errors_lengthT;
      for( uint8_t i = 0; i < delta_errors_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_delta_errors));
        memcpy( &(this->delta_errors[i]), &(this->st_delta_errors), sizeof(float));
      }
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->fft_sharpness));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->heading));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->declination));
     return offset;
    }

    const char * getType(){ return "hydrophones/Debug"; };
    const char * getMD5(){ return "df913afc8d816766e0901c775e129752"; };

  };

}
#endif