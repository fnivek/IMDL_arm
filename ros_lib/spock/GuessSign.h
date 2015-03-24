#ifndef _ROS_SERVICE_GuessSign_h
#define _ROS_SERVICE_GuessSign_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace spock
{

static const char GUESSSIGN[] = "spock/GuessSign";

  class GuessSignRequest : public ros::Msg
  {
    public:
      const char* course;

    GuessSignRequest():
      course("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_course = strlen(this->course);
      memcpy(outbuffer + offset, &length_course, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->course, length_course);
      offset += length_course;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_course;
      memcpy(&length_course, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_course; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_course-1]=0;
      this->course = (char *)(inbuffer + offset-1);
      offset += length_course;
     return offset;
    }

    const char * getType(){ return GUESSSIGN; };
    const char * getMD5(){ return "53ea8e682aea15e338225c05428c0cb7"; };

  };

  class GuessSignResponse : public ros::Msg
  {
    public:

    GuessSignResponse()
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

    const char * getType(){ return GUESSSIGN; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GuessSign {
    public:
    typedef GuessSignRequest Request;
    typedef GuessSignResponse Response;
  };

}
#endif
