#ifndef _ROS_object_finder_Component_h
#define _ROS_object_finder_Component_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "object_finder/Color.h"
#include "object_finder/Triangle.h"

namespace object_finder
{

  class Component : public ros::Msg
  {
    public:
      const char* name;
      object_finder::Color color;
      uint8_t triangles_length;
      object_finder::Triangle st_triangles;
      object_finder::Triangle * triangles;

    Component():
      name(""),
      color(),
      triangles_length(0), triangles(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      memcpy(outbuffer + offset, &length_name, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      offset += this->color.serialize(outbuffer + offset);
      *(outbuffer + offset++) = triangles_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < triangles_length; i++){
      offset += this->triangles[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      memcpy(&length_name, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      offset += this->color.deserialize(inbuffer + offset);
      uint8_t triangles_lengthT = *(inbuffer + offset++);
      if(triangles_lengthT > triangles_length)
        this->triangles = (object_finder::Triangle*)realloc(this->triangles, triangles_lengthT * sizeof(object_finder::Triangle));
      offset += 3;
      triangles_length = triangles_lengthT;
      for( uint8_t i = 0; i < triangles_length; i++){
      offset += this->st_triangles.deserialize(inbuffer + offset);
        memcpy( &(this->triangles[i]), &(this->st_triangles), sizeof(object_finder::Triangle));
      }
     return offset;
    }

    const char * getType(){ return "object_finder/Component"; };
    const char * getMD5(){ return "69a952ba9a2f478ce02ad595ce340a34"; };

  };

}
#endif