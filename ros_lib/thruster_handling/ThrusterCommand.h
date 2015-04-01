#ifndef _ROS_thruster_handling_ThrusterCommand_h
#define _ROS_thruster_handling_ThrusterCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace thruster_handling
{

  class ThrusterCommand : public ros::Msg
  {
    public:
      double force;

    ThrusterCommand():
      force(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_force;
      u_force.real = this->force;
      *(outbuffer + offset + 0) = (u_force.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_force.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_force.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_force.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_force.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_force.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_force.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_force.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->force);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_force;
      u_force.base = 0;
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_force.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->force = u_force.real;
      offset += sizeof(this->force);
     return offset;
    }

    const char * getType(){ return "thruster_handling/ThrusterCommand"; };
    const char * getMD5(){ return "e18a51329659ac6263f87aaf9a01fe62"; };

  };

}
#endif