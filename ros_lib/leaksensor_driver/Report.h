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
      double temperature;
      double pressure;
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
      union {
        double real;
        uint64_t base;
      } u_temperature;
      u_temperature.real = this->temperature;
      *(outbuffer + offset + 0) = (u_temperature.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_temperature.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_temperature.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_temperature.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_temperature.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_temperature.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_temperature.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_temperature.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->temperature);
      union {
        double real;
        uint64_t base;
      } u_pressure;
      u_pressure.real = this->pressure;
      *(outbuffer + offset + 0) = (u_pressure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pressure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pressure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pressure.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_pressure.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_pressure.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_pressure.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_pressure.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->pressure);
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
      union {
        double real;
        uint64_t base;
      } u_temperature;
      u_temperature.base = 0;
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_temperature.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->temperature = u_temperature.real;
      offset += sizeof(this->temperature);
      union {
        double real;
        uint64_t base;
      } u_pressure;
      u_pressure.base = 0;
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_pressure.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->pressure = u_pressure.real;
      offset += sizeof(this->pressure);
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