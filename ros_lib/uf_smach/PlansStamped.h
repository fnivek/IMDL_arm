#ifndef _ROS_uf_smach_PlansStamped_h
#define _ROS_uf_smach_PlansStamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "uf_smach/Plan.h"

namespace uf_smach
{

  class PlansStamped : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t plans_length;
      uf_smach::Plan st_plans;
      uf_smach::Plan * plans;
      uint8_t available_missions_length;
      char* st_available_missions;
      char* * available_missions;

    PlansStamped():
      header(),
      plans_length(0), plans(NULL),
      available_missions_length(0), available_missions(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = plans_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < plans_length; i++){
      offset += this->plans[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = available_missions_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < available_missions_length; i++){
      uint32_t length_available_missionsi = strlen(this->available_missions[i]);
      memcpy(outbuffer + offset, &length_available_missionsi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->available_missions[i], length_available_missionsi);
      offset += length_available_missionsi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t plans_lengthT = *(inbuffer + offset++);
      if(plans_lengthT > plans_length)
        this->plans = (uf_smach::Plan*)realloc(this->plans, plans_lengthT * sizeof(uf_smach::Plan));
      offset += 3;
      plans_length = plans_lengthT;
      for( uint8_t i = 0; i < plans_length; i++){
      offset += this->st_plans.deserialize(inbuffer + offset);
        memcpy( &(this->plans[i]), &(this->st_plans), sizeof(uf_smach::Plan));
      }
      uint8_t available_missions_lengthT = *(inbuffer + offset++);
      if(available_missions_lengthT > available_missions_length)
        this->available_missions = (char**)realloc(this->available_missions, available_missions_lengthT * sizeof(char*));
      offset += 3;
      available_missions_length = available_missions_lengthT;
      for( uint8_t i = 0; i < available_missions_length; i++){
      uint32_t length_st_available_missions;
      memcpy(&length_st_available_missions, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_available_missions; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_available_missions-1]=0;
      this->st_available_missions = (char *)(inbuffer + offset-1);
      offset += length_st_available_missions;
        memcpy( &(this->available_missions[i]), &(this->st_available_missions), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return "uf_smach/PlansStamped"; };
    const char * getMD5(){ return "f844ab18e351a2fc5fc5026ee7e523d8"; };

  };

}
#endif