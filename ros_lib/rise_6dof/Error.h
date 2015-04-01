#ifndef _ROS_rise_6dof_Error_h
#define _ROS_rise_6dof_Error_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace rise_6dof
{

  class Error : public ros::Msg
  {
    public:
      std_msgs::Header header;
      double zeta[6];
      double tau_c[3];
      double nuC[3];

    Error():
      header(),
      zeta(),
      tau_c(),
      nuC()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint8_t i = 0; i < 6; i++){
      union {
        double real;
        uint64_t base;
      } u_zetai;
      u_zetai.real = this->zeta[i];
      *(outbuffer + offset + 0) = (u_zetai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_zetai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_zetai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_zetai.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_zetai.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_zetai.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_zetai.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_zetai.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->zeta[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_tau_ci;
      u_tau_ci.real = this->tau_c[i];
      *(outbuffer + offset + 0) = (u_tau_ci.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_tau_ci.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_tau_ci.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_tau_ci.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_tau_ci.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_tau_ci.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_tau_ci.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_tau_ci.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->tau_c[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_nuCi;
      u_nuCi.real = this->nuC[i];
      *(outbuffer + offset + 0) = (u_nuCi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_nuCi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_nuCi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_nuCi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_nuCi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_nuCi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_nuCi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_nuCi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->nuC[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint8_t i = 0; i < 6; i++){
      union {
        double real;
        uint64_t base;
      } u_zetai;
      u_zetai.base = 0;
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_zetai.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->zeta[i] = u_zetai.real;
      offset += sizeof(this->zeta[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_tau_ci;
      u_tau_ci.base = 0;
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_tau_ci.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->tau_c[i] = u_tau_ci.real;
      offset += sizeof(this->tau_c[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_nuCi;
      u_nuCi.base = 0;
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_nuCi.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->nuC[i] = u_nuCi.real;
      offset += sizeof(this->nuC[i]);
      }
     return offset;
    }

    const char * getType(){ return "rise_6dof/Error"; };
    const char * getMD5(){ return "6de9201e486bd0c50d0c0f927970a3ce"; };

  };

}
#endif