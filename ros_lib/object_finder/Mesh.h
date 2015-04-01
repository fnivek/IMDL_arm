#ifndef _ROS_object_finder_Mesh_h
#define _ROS_object_finder_Mesh_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "object_finder/Component.h"

namespace object_finder
{

  class Mesh : public ros::Msg
  {
    public:
      uint8_t components_length;
      object_finder::Component st_components;
      object_finder::Component * components;

    Mesh():
      components_length(0), components(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = components_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < components_length; i++){
      offset += this->components[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t components_lengthT = *(inbuffer + offset++);
      if(components_lengthT > components_length)
        this->components = (object_finder::Component*)realloc(this->components, components_lengthT * sizeof(object_finder::Component));
      offset += 3;
      components_length = components_lengthT;
      for( uint8_t i = 0; i < components_length; i++){
      offset += this->st_components.deserialize(inbuffer + offset);
        memcpy( &(this->components[i]), &(this->st_components), sizeof(object_finder::Component));
      }
     return offset;
    }

    const char * getType(){ return "object_finder/Mesh"; };
    const char * getMD5(){ return "b353ede27bcc5e71d3109f7b208cdd22"; };

  };

}
#endif