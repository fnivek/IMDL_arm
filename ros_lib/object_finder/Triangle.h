#ifndef _ROS_object_finder_Triangle_h
#define _ROS_object_finder_Triangle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace object_finder
{

  class Triangle : public ros::Msg
  {
    public:
      geometry_msgs::Point corners[3];

    Triangle():
      corners()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint8_t i = 0; i < 3; i++){
      offset += this->corners[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint8_t i = 0; i < 3; i++){
      offset += this->corners[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "object_finder/Triangle"; };
    const char * getMD5(){ return "a0e200474a3819c8499cd604fce8e114"; };

  };

}
#endif