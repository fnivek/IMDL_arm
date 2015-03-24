#ifndef _ROS_legacy_vision_TargetRes_h
#define _ROS_legacy_vision_TargetRes_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace legacy_vision
{

  class TargetRes : public ros::Msg
  {
    public:
      uint8_t object_results_length;
      char* st_object_results;
      char* * object_results;

    TargetRes():
      object_results_length(0), object_results(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = object_results_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < object_results_length; i++){
      uint32_t length_object_resultsi = strlen(this->object_results[i]);
      memcpy(outbuffer + offset, &length_object_resultsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->object_results[i], length_object_resultsi);
      offset += length_object_resultsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t object_results_lengthT = *(inbuffer + offset++);
      if(object_results_lengthT > object_results_length)
        this->object_results = (char**)realloc(this->object_results, object_results_lengthT * sizeof(char*));
      offset += 3;
      object_results_length = object_results_lengthT;
      for( uint8_t i = 0; i < object_results_length; i++){
      uint32_t length_st_object_results;
      memcpy(&length_st_object_results, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_object_results; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_object_results-1]=0;
      this->st_object_results = (char *)(inbuffer + offset-1);
      offset += length_st_object_results;
        memcpy( &(this->object_results[i]), &(this->st_object_results), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "legacy_vision/TargetRes"; };
    const char * getMD5(){ return "1a468b1564ea9eab8e4ed8e10742bb0c"; };

  };

}
#endif