#ifndef _ROS_power_router_prstatus_h
#define _ROS_power_router_prstatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace power_router
{

  class prstatus : public ros::Msg
  {
    public:
      std_msgs::Header header;
      double computercurrent;
      double motorcurrent;
      double temperature;
      double battery;

    prstatus():
      header(),
      computercurrent(0),
      motorcurrent(0),
      temperature(0),
      battery(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_computercurrent;
      u_computercurrent.real = this->computercurrent;
      *(outbuffer + offset + 0) = (u_computercurrent.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_computercurrent.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_computercurrent.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_computercurrent.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_computercurrent.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_computercurrent.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_computercurrent.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_computercurrent.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->computercurrent);
      union {
        double real;
        uint64_t base;
      } u_motorcurrent;
      u_motorcurrent.real = this->motorcurrent;
      *(outbuffer + offset + 0) = (u_motorcurrent.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_motorcurrent.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_motorcurrent.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_motorcurrent.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_motorcurrent.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_motorcurrent.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_motorcurrent.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_motorcurrent.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->motorcurrent);
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
      } u_battery;
      u_battery.real = this->battery;
      *(outbuffer + offset + 0) = (u_battery.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_battery.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_battery.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_battery.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_battery.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_battery.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_battery.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_battery.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->battery);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_computercurrent;
      u_computercurrent.base = 0;
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_computercurrent.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->computercurrent = u_computercurrent.real;
      offset += sizeof(this->computercurrent);
      union {
        double real;
        uint64_t base;
      } u_motorcurrent;
      u_motorcurrent.base = 0;
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_motorcurrent.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->motorcurrent = u_motorcurrent.real;
      offset += sizeof(this->motorcurrent);
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
      } u_battery;
      u_battery.base = 0;
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_battery.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->battery = u_battery.real;
      offset += sizeof(this->battery);
     return offset;
    }

    const char * getType(){ return "power_router/prstatus"; };
    const char * getMD5(){ return "45fcda3aaef6826c211ea7e3e5c320c1"; };

  };

}
#endif