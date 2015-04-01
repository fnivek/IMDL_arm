#ifndef _ROS_rise_6dof_Weights_h
#define _ROS_rise_6dof_Weights_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace rise_6dof
{

  class Weights : public ros::Msg
  {
    public:
      std_msgs::Header header;
      double Wc_hat[21];
      double Wa1_hat[21];
      double Gamma[441];

    Weights():
      header(),
      Wc_hat(),
      Wa1_hat(),
      Gamma()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint8_t i = 0; i < 21; i++){
      union {
        double real;
        uint64_t base;
      } u_Wc_hati;
      u_Wc_hati.real = this->Wc_hat[i];
      *(outbuffer + offset + 0) = (u_Wc_hati.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Wc_hati.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Wc_hati.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Wc_hati.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_Wc_hati.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_Wc_hati.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_Wc_hati.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_Wc_hati.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->Wc_hat[i]);
      }
      for( uint8_t i = 0; i < 21; i++){
      union {
        double real;
        uint64_t base;
      } u_Wa1_hati;
      u_Wa1_hati.real = this->Wa1_hat[i];
      *(outbuffer + offset + 0) = (u_Wa1_hati.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Wa1_hati.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Wa1_hati.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Wa1_hati.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_Wa1_hati.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_Wa1_hati.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_Wa1_hati.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_Wa1_hati.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->Wa1_hat[i]);
      }
      for( uint8_t i = 0; i < 441; i++){
      union {
        double real;
        uint64_t base;
      } u_Gammai;
      u_Gammai.real = this->Gamma[i];
      *(outbuffer + offset + 0) = (u_Gammai.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Gammai.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Gammai.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Gammai.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_Gammai.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_Gammai.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_Gammai.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_Gammai.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->Gamma[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint8_t i = 0; i < 21; i++){
      union {
        double real;
        uint64_t base;
      } u_Wc_hati;
      u_Wc_hati.base = 0;
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_Wc_hati.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->Wc_hat[i] = u_Wc_hati.real;
      offset += sizeof(this->Wc_hat[i]);
      }
      for( uint8_t i = 0; i < 21; i++){
      union {
        double real;
        uint64_t base;
      } u_Wa1_hati;
      u_Wa1_hati.base = 0;
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_Wa1_hati.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->Wa1_hat[i] = u_Wa1_hati.real;
      offset += sizeof(this->Wa1_hat[i]);
      }
      for( uint8_t i = 0; i < 441; i++){
      union {
        double real;
        uint64_t base;
      } u_Gammai;
      u_Gammai.base = 0;
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_Gammai.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->Gamma[i] = u_Gammai.real;
      offset += sizeof(this->Gamma[i]);
      }
     return offset;
    }

    const char * getType(){ return "rise_6dof/Weights"; };
    const char * getMD5(){ return "c81a60b0b8eed4f29d7f65d2667a4829"; };

  };

}
#endif