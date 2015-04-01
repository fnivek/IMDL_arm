#ifndef _ROS_rise_6dof_Input_h
#define _ROS_rise_6dof_Input_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace rise_6dof
{

  class Input : public ros::Msg
  {
    public:
      std_msgs::Header header;
      double x[6];
      double x_dot[6];
      double u[3];

    Input():
      header(),
      x(),
      x_dot(),
      u()
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
      } u_xi;
      u_xi.real = this->x[i];
      *(outbuffer + offset + 0) = (u_xi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_xi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_xi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_xi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_xi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_xi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_xi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_xi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->x[i]);
      }
      for( uint8_t i = 0; i < 6; i++){
      union {
        double real;
        uint64_t base;
      } u_x_doti;
      u_x_doti.real = this->x_dot[i];
      *(outbuffer + offset + 0) = (u_x_doti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x_doti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_x_doti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_x_doti.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_x_doti.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_x_doti.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_x_doti.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_x_doti.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->x_dot[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_ui;
      u_ui.real = this->u[i];
      *(outbuffer + offset + 0) = (u_ui.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ui.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ui.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ui.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_ui.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_ui.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_ui.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_ui.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->u[i]);
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
      } u_xi;
      u_xi.base = 0;
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_xi.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->x[i] = u_xi.real;
      offset += sizeof(this->x[i]);
      }
      for( uint8_t i = 0; i < 6; i++){
      union {
        double real;
        uint64_t base;
      } u_x_doti;
      u_x_doti.base = 0;
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_x_doti.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->x_dot[i] = u_x_doti.real;
      offset += sizeof(this->x_dot[i]);
      }
      for( uint8_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_ui;
      u_ui.base = 0;
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_ui.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->u[i] = u_ui.real;
      offset += sizeof(this->u[i]);
      }
     return offset;
    }

    const char * getType(){ return "rise_6dof/Input"; };
    const char * getMD5(){ return "21c3f65e441ca9fa9d0a8658535cc061"; };

  };

}
#endif