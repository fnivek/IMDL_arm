#ifndef _ROS_kill_handling_KillsStamped_h
#define _ROS_kill_handling_KillsStamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "kill_handling/Kill.h"

namespace kill_handling
{

  class KillsStamped : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t kills_length;
      kill_handling::Kill st_kills;
      kill_handling::Kill * kills;

    KillsStamped():
      header(),
      kills_length(0), kills(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = kills_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < kills_length; i++){
      offset += this->kills[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t kills_lengthT = *(inbuffer + offset++);
      if(kills_lengthT > kills_length)
        this->kills = (kill_handling::Kill*)realloc(this->kills, kills_lengthT * sizeof(kill_handling::Kill));
      offset += 3;
      kills_length = kills_lengthT;
      for( uint8_t i = 0; i < kills_length; i++){
      offset += this->st_kills.deserialize(inbuffer + offset);
        memcpy( &(this->kills[i]), &(this->st_kills), sizeof(kill_handling::Kill));
      }
     return offset;
    }

    const char * getType(){ return "kill_handling/KillsStamped"; };
    const char * getMD5(){ return "fcc147f7ee517b720ae1e36b36bbbe9c"; };

  };

}
#endif