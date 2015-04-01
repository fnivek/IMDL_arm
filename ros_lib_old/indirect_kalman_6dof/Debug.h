#ifndef _ROS_indirect_kalman_6dof_Debug_h
#define _ROS_indirect_kalman_6dof_Debug_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace indirect_kalman_6dof
{

  class Debug : public ros::Msg
  {
    public:
      std_msgs::Header header;
      geometry_msgs::Vector3 a_imu;
      geometry_msgs::Vector3 a_imu_no_g;
      geometry_msgs::Vector3 w_imu;
      geometry_msgs::Vector3 b_g;
      uint32_t y_m_count;
      uint32_t y_d_count;
      uint32_t y_z_count;

    Debug():
      header(),
      a_imu(),
      a_imu_no_g(),
      w_imu(),
      b_g(),
      y_m_count(0),
      y_d_count(0),
      y_z_count(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->a_imu.serialize(outbuffer + offset);
      offset += this->a_imu_no_g.serialize(outbuffer + offset);
      offset += this->w_imu.serialize(outbuffer + offset);
      offset += this->b_g.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->y_m_count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_m_count >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_m_count >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_m_count >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_m_count);
      *(outbuffer + offset + 0) = (this->y_d_count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_d_count >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_d_count >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_d_count >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_d_count);
      *(outbuffer + offset + 0) = (this->y_z_count >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->y_z_count >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->y_z_count >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->y_z_count >> (8 * 3)) & 0xFF;
      offset += sizeof(this->y_z_count);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->a_imu.deserialize(inbuffer + offset);
      offset += this->a_imu_no_g.deserialize(inbuffer + offset);
      offset += this->w_imu.deserialize(inbuffer + offset);
      offset += this->b_g.deserialize(inbuffer + offset);
      this->y_m_count =  ((uint32_t) (*(inbuffer + offset)));
      this->y_m_count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->y_m_count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->y_m_count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->y_m_count);
      this->y_d_count =  ((uint32_t) (*(inbuffer + offset)));
      this->y_d_count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->y_d_count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->y_d_count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->y_d_count);
      this->y_z_count =  ((uint32_t) (*(inbuffer + offset)));
      this->y_z_count |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->y_z_count |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->y_z_count |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->y_z_count);
     return offset;
    }

    const char * getType(){ return "indirect_kalman_6dof/Debug"; };
    const char * getMD5(){ return "77f015eaf43c9e590d3c0eda69ec33d8"; };

  };

}
#endif