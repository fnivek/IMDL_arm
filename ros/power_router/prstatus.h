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
      float computercurrent;
      float motorcurrent;
      float temperature;
      float battery;

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
      offset += serializeAvrFloat64(outbuffer + offset, this->computercurrent);
      offset += serializeAvrFloat64(outbuffer + offset, this->motorcurrent);
      offset += serializeAvrFloat64(outbuffer + offset, this->temperature);
      offset += serializeAvrFloat64(outbuffer + offset, this->battery);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->computercurrent));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->motorcurrent));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->temperature));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->battery));
     return offset;
    }

    const char * getType(){ return "power_router/prstatus"; };
    const char * getMD5(){ return "45fcda3aaef6826c211ea7e3e5c320c1"; };

  };

}
#endif