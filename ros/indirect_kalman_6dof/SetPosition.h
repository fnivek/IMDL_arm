#ifndef _ROS_SERVICE_SetPosition_h
#define _ROS_SERVICE_SetPosition_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace indirect_kalman_6dof
{

static const char SETPOSITION[] = "indirect_kalman_6dof/SetPosition";

  class SetPositionRequest : public ros::Msg
  {
    public:
      geometry_msgs::Point position;

    SetPositionRequest():
      position()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->position.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->position.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SETPOSITION; };
    const char * getMD5(){ return "e7bb0ef028c744b081acdc57743b11d8"; };

  };

  class SetPositionResponse : public ros::Msg
  {
    public:

    SetPositionResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SETPOSITION; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SetPosition {
    public:
    typedef SetPositionRequest Request;
    typedef SetPositionResponse Response;
  };

}
#endif
