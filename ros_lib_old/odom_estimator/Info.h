#ifndef _ROS_odom_estimator_Info_h
#define _ROS_odom_estimator_Info_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace odom_estimator
{

  class Info : public ros::Msg
  {
    public:
      std_msgs::Header header;
      geometry_msgs::Vector3 gyro_bias;
      geometry_msgs::Vector3 gyro_bias_stddev;
      geometry_msgs::Vector3 accel_bias;
      geometry_msgs::Vector3 accel_bias_stddev;
      uint8_t gps_bias_prns_length;
      int32_t st_gps_bias_prns;
      int32_t * gps_bias_prns;
      uint8_t gps_bias_biases_length;
      float st_gps_bias_biases;
      float * gps_bias_biases;
      uint8_t gps_bias_stddevs_length;
      float st_gps_bias_stddevs;
      float * gps_bias_stddevs;

    Info():
      header(),
      gyro_bias(),
      gyro_bias_stddev(),
      accel_bias(),
      accel_bias_stddev(),
      gps_bias_prns_length(0), gps_bias_prns(NULL),
      gps_bias_biases_length(0), gps_bias_biases(NULL),
      gps_bias_stddevs_length(0), gps_bias_stddevs(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->gyro_bias.serialize(outbuffer + offset);
      offset += this->gyro_bias_stddev.serialize(outbuffer + offset);
      offset += this->accel_bias.serialize(outbuffer + offset);
      offset += this->accel_bias_stddev.serialize(outbuffer + offset);
      *(outbuffer + offset++) = gps_bias_prns_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < gps_bias_prns_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_gps_bias_prnsi;
      u_gps_bias_prnsi.real = this->gps_bias_prns[i];
      *(outbuffer + offset + 0) = (u_gps_bias_prnsi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_gps_bias_prnsi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_gps_bias_prnsi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_gps_bias_prnsi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->gps_bias_prns[i]);
      }
      *(outbuffer + offset++) = gps_bias_biases_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < gps_bias_biases_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->gps_bias_biases[i]);
      }
      *(outbuffer + offset++) = gps_bias_stddevs_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < gps_bias_stddevs_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->gps_bias_stddevs[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->gyro_bias.deserialize(inbuffer + offset);
      offset += this->gyro_bias_stddev.deserialize(inbuffer + offset);
      offset += this->accel_bias.deserialize(inbuffer + offset);
      offset += this->accel_bias_stddev.deserialize(inbuffer + offset);
      uint8_t gps_bias_prns_lengthT = *(inbuffer + offset++);
      if(gps_bias_prns_lengthT > gps_bias_prns_length)
        this->gps_bias_prns = (int32_t*)realloc(this->gps_bias_prns, gps_bias_prns_lengthT * sizeof(int32_t));
      offset += 3;
      gps_bias_prns_length = gps_bias_prns_lengthT;
      for( uint8_t i = 0; i < gps_bias_prns_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_gps_bias_prns;
      u_st_gps_bias_prns.base = 0;
      u_st_gps_bias_prns.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_gps_bias_prns.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_gps_bias_prns.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_gps_bias_prns.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_gps_bias_prns = u_st_gps_bias_prns.real;
      offset += sizeof(this->st_gps_bias_prns);
        memcpy( &(this->gps_bias_prns[i]), &(this->st_gps_bias_prns), sizeof(int32_t));
      }
      uint8_t gps_bias_biases_lengthT = *(inbuffer + offset++);
      if(gps_bias_biases_lengthT > gps_bias_biases_length)
        this->gps_bias_biases = (float*)realloc(this->gps_bias_biases, gps_bias_biases_lengthT * sizeof(float));
      offset += 3;
      gps_bias_biases_length = gps_bias_biases_lengthT;
      for( uint8_t i = 0; i < gps_bias_biases_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_gps_bias_biases));
        memcpy( &(this->gps_bias_biases[i]), &(this->st_gps_bias_biases), sizeof(float));
      }
      uint8_t gps_bias_stddevs_lengthT = *(inbuffer + offset++);
      if(gps_bias_stddevs_lengthT > gps_bias_stddevs_length)
        this->gps_bias_stddevs = (float*)realloc(this->gps_bias_stddevs, gps_bias_stddevs_lengthT * sizeof(float));
      offset += 3;
      gps_bias_stddevs_length = gps_bias_stddevs_lengthT;
      for( uint8_t i = 0; i < gps_bias_stddevs_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_gps_bias_stddevs));
        memcpy( &(this->gps_bias_stddevs[i]), &(this->st_gps_bias_stddevs), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "odom_estimator/Info"; };
    const char * getMD5(){ return "e33c8097079304cda20baaebf5c87a66"; };

  };

}
#endif