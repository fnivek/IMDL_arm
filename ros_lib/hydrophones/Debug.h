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
      double st_deltas;
      double * deltas;
      uint8_t delta_errors_length;
      double st_delta_errors;
      double * delta_errors;
      double fft_sharpness;
      double heading;
      double declination;

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
      union {
        double real;
        uint64_t base;
      } u_deltasi;
      u_deltasi.real = this->deltas[i];
      *(outbuffer + offset + 0) = (u_deltasi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_deltasi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_deltasi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_deltasi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_deltasi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_deltasi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_deltasi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_deltasi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->deltas[i]);
      }
      *(outbuffer + offset++) = delta_errors_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < delta_errors_length; i++){
      union {
        double real;
        uint64_t base;
      } u_delta_errorsi;
      u_delta_errorsi.real = this->delta_errors[i];
      *(outbuffer + offset + 0) = (u_delta_errorsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_delta_errorsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_delta_errorsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_delta_errorsi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_delta_errorsi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_delta_errorsi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_delta_errorsi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_delta_errorsi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->delta_errors[i]);
      }
      union {
        double real;
        uint64_t base;
      } u_fft_sharpness;
      u_fft_sharpness.real = this->fft_sharpness;
      *(outbuffer + offset + 0) = (u_fft_sharpness.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fft_sharpness.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fft_sharpness.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fft_sharpness.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_fft_sharpness.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_fft_sharpness.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_fft_sharpness.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_fft_sharpness.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->fft_sharpness);
      union {
        double real;
        uint64_t base;
      } u_heading;
      u_heading.real = this->heading;
      *(outbuffer + offset + 0) = (u_heading.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_heading.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_heading.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_heading.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_heading.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_heading.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_heading.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_heading.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->heading);
      union {
        double real;
        uint64_t base;
      } u_declination;
      u_declination.real = this->declination;
      *(outbuffer + offset + 0) = (u_declination.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_declination.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_declination.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_declination.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_declination.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_declination.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_declination.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_declination.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->declination);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t deltas_lengthT = *(inbuffer + offset++);
      if(deltas_lengthT > deltas_length)
        this->deltas = (double*)realloc(this->deltas, deltas_lengthT * sizeof(double));
      offset += 3;
      deltas_length = deltas_lengthT;
      for( uint8_t i = 0; i < deltas_length; i++){
      union {
        double real;
        uint64_t base;
      } u_st_deltas;
      u_st_deltas.base = 0;
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_st_deltas.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->st_deltas = u_st_deltas.real;
      offset += sizeof(this->st_deltas);
        memcpy( &(this->deltas[i]), &(this->st_deltas), sizeof(double));
      }
      uint8_t delta_errors_lengthT = *(inbuffer + offset++);
      if(delta_errors_lengthT > delta_errors_length)
        this->delta_errors = (double*)realloc(this->delta_errors, delta_errors_lengthT * sizeof(double));
      offset += 3;
      delta_errors_length = delta_errors_lengthT;
      for( uint8_t i = 0; i < delta_errors_length; i++){
      union {
        double real;
        uint64_t base;
      } u_st_delta_errors;
      u_st_delta_errors.base = 0;
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_st_delta_errors.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->st_delta_errors = u_st_delta_errors.real;
      offset += sizeof(this->st_delta_errors);
        memcpy( &(this->delta_errors[i]), &(this->st_delta_errors), sizeof(double));
      }
      union {
        double real;
        uint64_t base;
      } u_fft_sharpness;
      u_fft_sharpness.base = 0;
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_fft_sharpness.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->fft_sharpness = u_fft_sharpness.real;
      offset += sizeof(this->fft_sharpness);
      union {
        double real;
        uint64_t base;
      } u_heading;
      u_heading.base = 0;
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_heading.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->heading = u_heading.real;
      offset += sizeof(this->heading);
      union {
        double real;
        uint64_t base;
      } u_declination;
      u_declination.base = 0;
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_declination.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->declination = u_declination.real;
      offset += sizeof(this->declination);
     return offset;
    }

    const char * getType(){ return "hydrophones/Debug"; };
    const char * getMD5(){ return "df913afc8d816766e0901c775e129752"; };

  };

}
#endif