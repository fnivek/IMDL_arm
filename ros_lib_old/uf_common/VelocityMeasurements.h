#ifndef _ROS_uf_common_VelocityMeasurements_h
#define _ROS_uf_common_VelocityMeasurements_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "uf_common/VelocityMeasurement.h"

namespace uf_common
{

  class VelocityMeasurements : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t velocity_measurements_length;
      uf_common::VelocityMeasurement st_velocity_measurements;
      uf_common::VelocityMeasurement * velocity_measurements;

    VelocityMeasurements():
      header(),
      velocity_measurements_length(0), velocity_measurements(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = velocity_measurements_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < velocity_measurements_length; i++){
      offset += this->velocity_measurements[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t velocity_measurements_lengthT = *(inbuffer + offset++);
      if(velocity_measurements_lengthT > velocity_measurements_length)
        this->velocity_measurements = (uf_common::VelocityMeasurement*)realloc(this->velocity_measurements, velocity_measurements_lengthT * sizeof(uf_common::VelocityMeasurement));
      offset += 3;
      velocity_measurements_length = velocity_measurements_lengthT;
      for( uint8_t i = 0; i < velocity_measurements_length; i++){
      offset += this->st_velocity_measurements.deserialize(inbuffer + offset);
        memcpy( &(this->velocity_measurements[i]), &(this->st_velocity_measurements), sizeof(uf_common::VelocityMeasurement));
      }
     return offset;
    }

    const char * getType(){ return "uf_common/VelocityMeasurements"; };
    const char * getMD5(){ return "5f86da067da8f9f18dda6b6a47259dc8"; };

  };

}
#endif