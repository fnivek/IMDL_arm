#ifndef _ROS_uf_smach_Plan_h
#define _ROS_uf_smach_Plan_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uf_smach/PlanEntry.h"

namespace uf_smach
{

  class Plan : public ros::Msg
  {
    public:
      const char* name;
      uint8_t entries_length;
      uf_smach::PlanEntry st_entries;
      uf_smach::PlanEntry * entries;

    Plan():
      name(""),
      entries_length(0), entries(NULL)
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
      *(outbuffer + offset++) = entries_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < entries_length; i++){
      offset += this->entries[i].serialize(outbuffer + offset);
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
      uint8_t entries_lengthT = *(inbuffer + offset++);
      if(entries_lengthT > entries_length)
        this->entries = (uf_smach::PlanEntry*)realloc(this->entries, entries_lengthT * sizeof(uf_smach::PlanEntry));
      offset += 3;
      entries_length = entries_lengthT;
      for( uint8_t i = 0; i < entries_length; i++){
      offset += this->st_entries.deserialize(inbuffer + offset);
        memcpy( &(this->entries[i]), &(this->st_entries), sizeof(uf_smach::PlanEntry));
      }
     return offset;
    }

    const char * getType(){ return "uf_smach/Plan"; };
    const char * getMD5(){ return "ae84b2a709b3095e2638cd1f42f3c531"; };

  };

}
#endif