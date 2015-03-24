#ifndef _ROS_hydrophones_Ping_h
#define _ROS_hydrophones_Ping_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace hydrophones
{

  class Ping : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int32_t channels;
      int32_t samples;
      int32_t sample_rate;
      uint8_t data_length;
      uint16_t st_data;
      uint16_t * data;

    Ping():
      header(),
      channels(0),
      samples(0),
      sample_rate(0),
      data_length(0), data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_channels;
      u_channels.real = this->channels;
      *(outbuffer + offset + 0) = (u_channels.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_channels.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_channels.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_channels.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->channels);
      union {
        int32_t real;
        uint32_t base;
      } u_samples;
      u_samples.real = this->samples;
      *(outbuffer + offset + 0) = (u_samples.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_samples.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_samples.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_samples.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->samples);
      union {
        int32_t real;
        uint32_t base;
      } u_sample_rate;
      u_sample_rate.real = this->sample_rate;
      *(outbuffer + offset + 0) = (u_sample_rate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sample_rate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sample_rate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sample_rate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sample_rate);
      *(outbuffer + offset++) = data_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < data_length; i++){
      *(outbuffer + offset + 0) = (this->data[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_channels;
      u_channels.base = 0;
      u_channels.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_channels.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_channels.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_channels.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->channels = u_channels.real;
      offset += sizeof(this->channels);
      union {
        int32_t real;
        uint32_t base;
      } u_samples;
      u_samples.base = 0;
      u_samples.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_samples.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_samples.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_samples.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->samples = u_samples.real;
      offset += sizeof(this->samples);
      union {
        int32_t real;
        uint32_t base;
      } u_sample_rate;
      u_sample_rate.base = 0;
      u_sample_rate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sample_rate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sample_rate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sample_rate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->sample_rate = u_sample_rate.real;
      offset += sizeof(this->sample_rate);
      uint8_t data_lengthT = *(inbuffer + offset++);
      if(data_lengthT > data_length)
        this->data = (uint16_t*)realloc(this->data, data_lengthT * sizeof(uint16_t));
      offset += 3;
      data_length = data_lengthT;
      for( uint8_t i = 0; i < data_length; i++){
      this->st_data =  ((uint16_t) (*(inbuffer + offset)));
      this->st_data |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_data);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(uint16_t));
      }
     return offset;
    }

    const char * getType(){ return "hydrophones/Ping"; };
    const char * getMD5(){ return "71fca9e8d7d9efe4b7e04b74b3ed2c2f"; };

  };

}
#endif