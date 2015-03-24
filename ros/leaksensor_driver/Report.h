#ifndef _ROS_leaksensor_driver_Report_h
#define _ROS_leaksensor_driver_Report_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace leaksensor_driver
{

  class Report : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float temperature;
      float pressure;
      bool water;

    Report():
      header(),
      temperature(0),
      pressure(0),
      water(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->temperature);
      offset += serializeAvrFloat64(outbuffer + offset, this->pressure);
      union {
        bool real;
        uint8_t base;
      } u_water;
      u_water.real = this->water;
      *(outbuffer + offset + 0) = (u_water.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->water);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->temperature));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->pressure));
      union {
        bool real;
        uint8_t base;
      } u_water;
      u_water.base = 0;
      u_water.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->water = u_water.real;
      offset += sizeof(this->water);
     return offset;
    }

    const char * getType(){ return "leaksensor_driver/Report"; };
    const char * getMD5(){ return "0a31858fb1be6bba58eac03fca3f5331"; };

  };

}
#endif