#ifndef _ROS_SERVICE_ModifyPlan_h
#define _ROS_SERVICE_ModifyPlan_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uf_smach/PlanEntry.h"

namespace uf_smach
{

static const char MODIFYPLAN[] = "uf_smach/ModifyPlan";

  class ModifyPlanRequest : public ros::Msg
  {
    public:
      const char* plan;
      uint8_t operation;
      int32_t pos;
      uf_smach::PlanEntry entry;
      enum { INSERT = 0 };
      enum { REMOVE = 1 };
      enum { REPLACE = 2 };

    ModifyPlanRequest():
      plan(""),
      operation(0),
      pos(0),
      entry()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_plan = strlen(this->plan);
      memcpy(outbuffer + offset, &length_plan, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->plan, length_plan);
      offset += length_plan;
      *(outbuffer + offset + 0) = (this->operation >> (8 * 0)) & 0xFF;
      offset += sizeof(this->operation);
      union {
        int32_t real;
        uint32_t base;
      } u_pos;
      u_pos.real = this->pos;
      *(outbuffer + offset + 0) = (u_pos.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pos.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pos.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pos.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pos);
      offset += this->entry.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_plan;
      memcpy(&length_plan, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_plan; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_plan-1]=0;
      this->plan = (char *)(inbuffer + offset-1);
      offset += length_plan;
      this->operation =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->operation);
      union {
        int32_t real;
        uint32_t base;
      } u_pos;
      u_pos.base = 0;
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pos.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pos = u_pos.real;
      offset += sizeof(this->pos);
      offset += this->entry.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return MODIFYPLAN; };
    const char * getMD5(){ return "5ee8765d6a4d3108d7708614ea7be66b"; };

  };

  class ModifyPlanResponse : public ros::Msg
  {
    public:

    ModifyPlanResponse()
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

    const char * getType(){ return MODIFYPLAN; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ModifyPlan {
    public:
    typedef ModifyPlanRequest Request;
    typedef ModifyPlanResponse Response;
  };

}
#endif
