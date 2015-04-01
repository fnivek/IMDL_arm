#ifndef _ROS_object_finder_TargetRes_h
#define _ROS_object_finder_TargetRes_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "object_finder/Color.h"

namespace object_finder
{

  class TargetRes : public ros::Msg
  {
    public:
      geometry_msgs::Pose pose;
      object_finder::Color color;
      double P;
      double smoothed_last_P;
      double P_within_10cm;
      double P_within_10cm_xy;

    TargetRes():
      pose(),
      color(),
      P(0),
      smoothed_last_P(0),
      P_within_10cm(0),
      P_within_10cm_xy(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      offset += this->color.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_P;
      u_P.real = this->P;
      *(outbuffer + offset + 0) = (u_P.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_P.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_P.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_P.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_P.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_P.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_P.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_P.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->P);
      union {
        double real;
        uint64_t base;
      } u_smoothed_last_P;
      u_smoothed_last_P.real = this->smoothed_last_P;
      *(outbuffer + offset + 0) = (u_smoothed_last_P.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_smoothed_last_P.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_smoothed_last_P.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_smoothed_last_P.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_smoothed_last_P.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_smoothed_last_P.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_smoothed_last_P.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_smoothed_last_P.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->smoothed_last_P);
      union {
        double real;
        uint64_t base;
      } u_P_within_10cm;
      u_P_within_10cm.real = this->P_within_10cm;
      *(outbuffer + offset + 0) = (u_P_within_10cm.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_P_within_10cm.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_P_within_10cm.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_P_within_10cm.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_P_within_10cm.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_P_within_10cm.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_P_within_10cm.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_P_within_10cm.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->P_within_10cm);
      union {
        double real;
        uint64_t base;
      } u_P_within_10cm_xy;
      u_P_within_10cm_xy.real = this->P_within_10cm_xy;
      *(outbuffer + offset + 0) = (u_P_within_10cm_xy.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_P_within_10cm_xy.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_P_within_10cm_xy.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_P_within_10cm_xy.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_P_within_10cm_xy.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_P_within_10cm_xy.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_P_within_10cm_xy.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_P_within_10cm_xy.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->P_within_10cm_xy);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->color.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_P;
      u_P.base = 0;
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_P.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->P = u_P.real;
      offset += sizeof(this->P);
      union {
        double real;
        uint64_t base;
      } u_smoothed_last_P;
      u_smoothed_last_P.base = 0;
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_smoothed_last_P.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->smoothed_last_P = u_smoothed_last_P.real;
      offset += sizeof(this->smoothed_last_P);
      union {
        double real;
        uint64_t base;
      } u_P_within_10cm;
      u_P_within_10cm.base = 0;
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_P_within_10cm.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->P_within_10cm = u_P_within_10cm.real;
      offset += sizeof(this->P_within_10cm);
      union {
        double real;
        uint64_t base;
      } u_P_within_10cm_xy;
      u_P_within_10cm_xy.base = 0;
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_P_within_10cm_xy.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->P_within_10cm_xy = u_P_within_10cm_xy.real;
      offset += sizeof(this->P_within_10cm_xy);
     return offset;
    }

    const char * getType(){ return "object_finder/TargetRes"; };
    const char * getMD5(){ return "e41cdd26c475f80435f30b9e6f313470"; };

  };

}
#endif