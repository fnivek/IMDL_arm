#ifndef _ROS_traj_odom_diff_pose_diff_h
#define _ROS_traj_odom_diff_pose_diff_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace traj_odom_diff
{

  class pose_diff : public ros::Msg
  {
    public:
      float diff_x;
      float diff_y;
      float diff_z;
      float diff_yaw;

    pose_diff():
      diff_x(0),
      diff_y(0),
      diff_z(0),
      diff_yaw(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_diff_x;
      u_diff_x.real = this->diff_x;
      *(outbuffer + offset + 0) = (u_diff_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_diff_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_diff_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_diff_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->diff_x);
      union {
        float real;
        uint32_t base;
      } u_diff_y;
      u_diff_y.real = this->diff_y;
      *(outbuffer + offset + 0) = (u_diff_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_diff_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_diff_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_diff_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->diff_y);
      union {
        float real;
        uint32_t base;
      } u_diff_z;
      u_diff_z.real = this->diff_z;
      *(outbuffer + offset + 0) = (u_diff_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_diff_z.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_diff_z.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_diff_z.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->diff_z);
      union {
        float real;
        uint32_t base;
      } u_diff_yaw;
      u_diff_yaw.real = this->diff_yaw;
      *(outbuffer + offset + 0) = (u_diff_yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_diff_yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_diff_yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_diff_yaw.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->diff_yaw);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_diff_x;
      u_diff_x.base = 0;
      u_diff_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_diff_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_diff_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_diff_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->diff_x = u_diff_x.real;
      offset += sizeof(this->diff_x);
      union {
        float real;
        uint32_t base;
      } u_diff_y;
      u_diff_y.base = 0;
      u_diff_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_diff_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_diff_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_diff_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->diff_y = u_diff_y.real;
      offset += sizeof(this->diff_y);
      union {
        float real;
        uint32_t base;
      } u_diff_z;
      u_diff_z.base = 0;
      u_diff_z.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_diff_z.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_diff_z.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_diff_z.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->diff_z = u_diff_z.real;
      offset += sizeof(this->diff_z);
      union {
        float real;
        uint32_t base;
      } u_diff_yaw;
      u_diff_yaw.base = 0;
      u_diff_yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_diff_yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_diff_yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_diff_yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->diff_yaw = u_diff_yaw.real;
      offset += sizeof(this->diff_yaw);
     return offset;
    }

    const char * getType(){ return "traj_odom_diff/pose_diff"; };
    const char * getMD5(){ return "aeb9f60e9974293837c63120c6024465"; };

  };

}
#endif