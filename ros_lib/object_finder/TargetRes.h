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
      float P;
      float smoothed_last_P;
      float P_within_10cm;
      float P_within_10cm_xy;

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
      offset += serializeAvrFloat64(outbuffer + offset, this->P);
      offset += serializeAvrFloat64(outbuffer + offset, this->smoothed_last_P);
      offset += serializeAvrFloat64(outbuffer + offset, this->P_within_10cm);
      offset += serializeAvrFloat64(outbuffer + offset, this->P_within_10cm_xy);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->color.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->P));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->smoothed_last_P));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->P_within_10cm));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->P_within_10cm_xy));
     return offset;
    }

    const char * getType(){ return "object_finder/TargetRes"; };
    const char * getMD5(){ return "e41cdd26c475f80435f30b9e6f313470"; };

  };

}
#endif