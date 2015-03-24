#ifndef _ROS_uf_smach_PlanEntry_h
#define _ROS_uf_smach_PlanEntry_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ros/duration.h"

namespace uf_smach
{

  class PlanEntry : public ros::Msg
  {
    public:
      const char* mission;
      ros::Duration timeout;
      const char* contigency_plan;
      const char* path;
      float dist;

    PlanEntry():
      mission(""),
      timeout(),
      contigency_plan(""),
      path(""),
      dist(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_mission = strlen(this->mission);
      memcpy(outbuffer + offset, &length_mission, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->mission, length_mission);
      offset += length_mission;
      *(outbuffer + offset + 0) = (this->timeout.sec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timeout.sec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timeout.sec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timeout.sec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeout.sec);
      *(outbuffer + offset + 0) = (this->timeout.nsec >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timeout.nsec >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timeout.nsec >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timeout.nsec >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeout.nsec);
      uint32_t length_contigency_plan = strlen(this->contigency_plan);
      memcpy(outbuffer + offset, &length_contigency_plan, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->contigency_plan, length_contigency_plan);
      offset += length_contigency_plan;
      uint32_t length_path = strlen(this->path);
      memcpy(outbuffer + offset, &length_path, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->path, length_path);
      offset += length_path;
      union {
        float real;
        uint32_t base;
      } u_dist;
      u_dist.real = this->dist;
      *(outbuffer + offset + 0) = (u_dist.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dist.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dist.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dist.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dist);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_mission;
      memcpy(&length_mission, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_mission; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_mission-1]=0;
      this->mission = (char *)(inbuffer + offset-1);
      offset += length_mission;
      this->timeout.sec =  ((uint32_t) (*(inbuffer + offset)));
      this->timeout.sec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timeout.sec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timeout.sec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timeout.sec);
      this->timeout.nsec =  ((uint32_t) (*(inbuffer + offset)));
      this->timeout.nsec |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->timeout.nsec |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->timeout.nsec |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->timeout.nsec);
      uint32_t length_contigency_plan;
      memcpy(&length_contigency_plan, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_contigency_plan; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_contigency_plan-1]=0;
      this->contigency_plan = (char *)(inbuffer + offset-1);
      offset += length_contigency_plan;
      uint32_t length_path;
      memcpy(&length_path, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_path; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_path-1]=0;
      this->path = (char *)(inbuffer + offset-1);
      offset += length_path;
      union {
        float real;
        uint32_t base;
      } u_dist;
      u_dist.base = 0;
      u_dist.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dist.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dist.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dist.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dist = u_dist.real;
      offset += sizeof(this->dist);
     return offset;
    }

    const char * getType(){ return "uf_smach/PlanEntry"; };
    const char * getMD5(){ return "df571b5d30e32b981bb77b6f6276e5d3"; };

  };

}
#endif