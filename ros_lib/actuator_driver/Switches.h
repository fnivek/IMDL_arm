#ifndef _ROS_actuator_driver_Switches_h
#define _ROS_actuator_driver_Switches_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace actuator_driver
{

  class Switches : public ros::Msg
  {
    public:
      std_msgs::Header header;
      bool pressed[2];

    Switches():
      header(),
      pressed()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint8_t i = 0; i < 2; i++){
      union {
        bool real;
        uint8_t base;
      } u_pressedi;
      u_pressedi.real = this->pressed[i];
      *(outbuffer + offset + 0) = (u_pressedi.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->pressed[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint8_t i = 0; i < 2; i++){
      union {
        bool real;
        uint8_t base;
      } u_pressedi;
      u_pressedi.base = 0;
      u_pressedi.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->pressed[i] = u_pressedi.real;
      offset += sizeof(this->pressed[i]);
      }
     return offset;
    }

    const char * getType(){ return "actuator_driver/Switches"; };
    const char * getMD5(){ return "6ecdc001a88b4757fa1324b2417d1b4c"; };

  };

}
#endif