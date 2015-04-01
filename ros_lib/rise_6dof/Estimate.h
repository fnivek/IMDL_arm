#ifndef _ROS_rise_6dof_Estimate_h
#define _ROS_rise_6dof_Estimate_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace rise_6dof
{

  class Estimate : public ros::Msg
  {
    public:
      std_msgs::Header header;
      double theta_hat[8];
      double x_hat[6];

    Estimate():
      header(),
      theta_hat(),
      x_hat()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint8_t i = 0; i < 8; i++){
      union {
        double real;
        uint64_t base;
      } u_theta_hati;
      u_theta_hati.real = this->theta_hat[i];
      *(outbuffer + offset + 0) = (u_theta_hati.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_theta_hati.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_theta_hati.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_theta_hati.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_theta_hati.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_theta_hati.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_theta_hati.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_theta_hati.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->theta_hat[i]);
      }
      for( uint8_t i = 0; i < 6; i++){
      union {
        double real;
        uint64_t base;
      } u_x_hati;
      u_x_hati.real = this->x_hat[i];
      *(outbuffer + offset + 0) = (u_x_hati.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x_hati.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x_hati.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x_hati.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_x_hati.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_x_hati.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_x_hati.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_x_hati.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->x_hat[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint8_t i = 0; i < 8; i++){
      union {
        double real;
        uint64_t base;
      } u_theta_hati;
      u_theta_hati.base = 0;
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_theta_hati.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->theta_hat[i] = u_theta_hati.real;
      offset += sizeof(this->theta_hat[i]);
      }
      for( uint8_t i = 0; i < 6; i++){
      union {
        double real;
        uint64_t base;
      } u_x_hati;
      u_x_hati.base = 0;
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_x_hati.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->x_hat[i] = u_x_hati.real;
      offset += sizeof(this->x_hat[i]);
      }
     return offset;
    }

    const char * getType(){ return "rise_6dof/Estimate"; };
    const char * getMD5(){ return "c6146309b6cf0d13662a3014992530ca"; };

  };

}
#endif