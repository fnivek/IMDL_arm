#ifndef _ROS_rawgps_common_Satellite_h
#define _ROS_rawgps_common_Satellite_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Vector3.h"

namespace rawgps_common
{

  class Satellite : public ros::Msg
  {
    public:
      int32_t prn;
      float cn0;
      geometry_msgs::Point position;
      geometry_msgs::Vector3 velocity;
      float time;
      float T_iono;
      float T_tropo;
      float carrier_distance;
      float doppler_velocity;
      geometry_msgs::Vector3 direction_enu;
      float velocity_plus_drift;

    Satellite():
      prn(0),
      cn0(0),
      position(),
      velocity(),
      time(0),
      T_iono(0),
      T_tropo(0),
      carrier_distance(0),
      doppler_velocity(0),
      direction_enu(),
      velocity_plus_drift(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_prn;
      u_prn.real = this->prn;
      *(outbuffer + offset + 0) = (u_prn.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_prn.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_prn.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_prn.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->prn);
      offset += serializeAvrFloat64(outbuffer + offset, this->cn0);
      offset += this->position.serialize(outbuffer + offset);
      offset += this->velocity.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->time);
      offset += serializeAvrFloat64(outbuffer + offset, this->T_iono);
      offset += serializeAvrFloat64(outbuffer + offset, this->T_tropo);
      offset += serializeAvrFloat64(outbuffer + offset, this->carrier_distance);
      offset += serializeAvrFloat64(outbuffer + offset, this->doppler_velocity);
      offset += this->direction_enu.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->velocity_plus_drift);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_prn;
      u_prn.base = 0;
      u_prn.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_prn.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_prn.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_prn.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->prn = u_prn.real;
      offset += sizeof(this->prn);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->cn0));
      offset += this->position.deserialize(inbuffer + offset);
      offset += this->velocity.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->time));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->T_iono));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->T_tropo));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->carrier_distance));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->doppler_velocity));
      offset += this->direction_enu.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->velocity_plus_drift));
     return offset;
    }

    const char * getType(){ return "rawgps_common/Satellite"; };
    const char * getMD5(){ return "c1393c83c1195cba60910bc4a01b26bb"; };

  };

}
#endif