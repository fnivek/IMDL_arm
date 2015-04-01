#ifndef _ROS_uf_common_VelocityMeasurement_h
#define _ROS_uf_common_VelocityMeasurement_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace uf_common
{

  class VelocityMeasurement : public ros::Msg
  {
    public:
      geometry_msgs::Vector3 direction;
      double velocity;
      double correlation;

    VelocityMeasurement():
      direction(),
      velocity(0),
      correlation(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->direction.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_velocity;
      u_velocity.real = this->velocity;
      *(outbuffer + offset + 0) = (u_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_velocity.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_velocity.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_velocity.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_velocity.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->velocity);
      union {
        double real;
        uint64_t base;
      } u_correlation;
      u_correlation.real = this->correlation;
      *(outbuffer + offset + 0) = (u_correlation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_correlation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_correlation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_correlation.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_correlation.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_correlation.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_correlation.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_correlation.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->correlation);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->direction.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_velocity;
      u_velocity.base = 0;
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_velocity.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->velocity = u_velocity.real;
      offset += sizeof(this->velocity);
      union {
        double real;
        uint64_t base;
      } u_correlation;
      u_correlation.base = 0;
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->correlation = u_correlation.real;
      offset += sizeof(this->correlation);
     return offset;
    }

    const char * getType(){ return "uf_common/VelocityMeasurement"; };
    const char * getMD5(){ return "91bd87f5dd3ca2deb6b495a94d789240"; };

  };

}
#endif