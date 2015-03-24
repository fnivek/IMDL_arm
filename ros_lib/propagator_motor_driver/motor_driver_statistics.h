#ifndef _ROS_propagator_motor_driver_motor_driver_statistics_h
#define _ROS_propagator_motor_driver_motor_driver_statistics_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace propagator_motor_driver
{

  class motor_driver_statistics : public ros::Msg
  {
    public:
      std_msgs::Header header;
      const char* id;
      float current;
      float out_voltage;
      float batt_voltage;

    motor_driver_statistics():
      header(),
      id(""),
      current(0),
      out_voltage(0),
      batt_voltage(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_id = strlen(this->id);
      memcpy(outbuffer + offset, &length_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      offset += serializeAvrFloat64(outbuffer + offset, this->current);
      offset += serializeAvrFloat64(outbuffer + offset, this->out_voltage);
      offset += serializeAvrFloat64(outbuffer + offset, this->batt_voltage);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_id;
      memcpy(&length_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->current));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->out_voltage));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->batt_voltage));
     return offset;
    }

    const char * getType(){ return "propagator_motor_driver/motor_driver_statistics"; };
    const char * getMD5(){ return "8baf432df41c7490522afc1b01f0872d"; };

  };

}
#endif