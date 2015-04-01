#ifndef _ROS_laser_tf_py_ScanAngle_h
#define _ROS_laser_tf_py_ScanAngle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace laser_tf_py
{

  class ScanAngle : public ros::Msg
  {
    public:
      std_msgs::Header header;
      int32_t min_angle;
      int32_t max_angle;

    ScanAngle():
      header(),
      min_angle(0),
      max_angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_min_angle;
      u_min_angle.real = this->min_angle;
      *(outbuffer + offset + 0) = (u_min_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_min_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_min_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_min_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->min_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_max_angle;
      u_max_angle.real = this->max_angle;
      *(outbuffer + offset + 0) = (u_max_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->max_angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        int32_t real;
        uint32_t base;
      } u_min_angle;
      u_min_angle.base = 0;
      u_min_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_min_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_min_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_min_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->min_angle = u_min_angle.real;
      offset += sizeof(this->min_angle);
      union {
        int32_t real;
        uint32_t base;
      } u_max_angle;
      u_max_angle.base = 0;
      u_max_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->max_angle = u_max_angle.real;
      offset += sizeof(this->max_angle);
     return offset;
    }

    const char * getType(){ return "laser_tf_py/ScanAngle"; };
    const char * getMD5(){ return "acc41e229ef35c8e65f2138c5400a8dc"; };

  };

}
#endif