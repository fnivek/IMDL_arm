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
      double cn0;
      geometry_msgs::Point position;
      geometry_msgs::Vector3 velocity;
      double time;
      double T_iono;
      double T_tropo;
      double carrier_distance;
      double doppler_velocity;
      geometry_msgs::Vector3 direction_enu;
      double velocity_plus_drift;

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
      union {
        double real;
        uint64_t base;
      } u_cn0;
      u_cn0.real = this->cn0;
      *(outbuffer + offset + 0) = (u_cn0.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cn0.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cn0.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cn0.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_cn0.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_cn0.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_cn0.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_cn0.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->cn0);
      offset += this->position.serialize(outbuffer + offset);
      offset += this->velocity.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_time;
      u_time.real = this->time;
      *(outbuffer + offset + 0) = (u_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_time.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_time.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_time.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_time.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->time);
      union {
        double real;
        uint64_t base;
      } u_T_iono;
      u_T_iono.real = this->T_iono;
      *(outbuffer + offset + 0) = (u_T_iono.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_T_iono.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_T_iono.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_T_iono.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_T_iono.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_T_iono.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_T_iono.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_T_iono.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->T_iono);
      union {
        double real;
        uint64_t base;
      } u_T_tropo;
      u_T_tropo.real = this->T_tropo;
      *(outbuffer + offset + 0) = (u_T_tropo.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_T_tropo.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_T_tropo.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_T_tropo.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_T_tropo.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_T_tropo.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_T_tropo.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_T_tropo.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->T_tropo);
      union {
        double real;
        uint64_t base;
      } u_carrier_distance;
      u_carrier_distance.real = this->carrier_distance;
      *(outbuffer + offset + 0) = (u_carrier_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_carrier_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_carrier_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_carrier_distance.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_carrier_distance.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_carrier_distance.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_carrier_distance.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_carrier_distance.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->carrier_distance);
      union {
        double real;
        uint64_t base;
      } u_doppler_velocity;
      u_doppler_velocity.real = this->doppler_velocity;
      *(outbuffer + offset + 0) = (u_doppler_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_doppler_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_doppler_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_doppler_velocity.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_doppler_velocity.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_doppler_velocity.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_doppler_velocity.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_doppler_velocity.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->doppler_velocity);
      offset += this->direction_enu.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_velocity_plus_drift;
      u_velocity_plus_drift.real = this->velocity_plus_drift;
      *(outbuffer + offset + 0) = (u_velocity_plus_drift.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_velocity_plus_drift.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_velocity_plus_drift.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_velocity_plus_drift.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_velocity_plus_drift.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_velocity_plus_drift.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_velocity_plus_drift.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_velocity_plus_drift.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->velocity_plus_drift);
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
      union {
        double real;
        uint64_t base;
      } u_cn0;
      u_cn0.base = 0;
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_cn0.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->cn0 = u_cn0.real;
      offset += sizeof(this->cn0);
      offset += this->position.deserialize(inbuffer + offset);
      offset += this->velocity.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_time;
      u_time.base = 0;
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_time.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->time = u_time.real;
      offset += sizeof(this->time);
      union {
        double real;
        uint64_t base;
      } u_T_iono;
      u_T_iono.base = 0;
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_T_iono.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->T_iono = u_T_iono.real;
      offset += sizeof(this->T_iono);
      union {
        double real;
        uint64_t base;
      } u_T_tropo;
      u_T_tropo.base = 0;
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_T_tropo.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->T_tropo = u_T_tropo.real;
      offset += sizeof(this->T_tropo);
      union {
        double real;
        uint64_t base;
      } u_carrier_distance;
      u_carrier_distance.base = 0;
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_carrier_distance.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->carrier_distance = u_carrier_distance.real;
      offset += sizeof(this->carrier_distance);
      union {
        double real;
        uint64_t base;
      } u_doppler_velocity;
      u_doppler_velocity.base = 0;
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_doppler_velocity.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->doppler_velocity = u_doppler_velocity.real;
      offset += sizeof(this->doppler_velocity);
      offset += this->direction_enu.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_velocity_plus_drift;
      u_velocity_plus_drift.base = 0;
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_velocity_plus_drift.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->velocity_plus_drift = u_velocity_plus_drift.real;
      offset += sizeof(this->velocity_plus_drift);
     return offset;
    }

    const char * getType(){ return "rawgps_common/Satellite"; };
    const char * getMD5(){ return "c1393c83c1195cba60910bc4a01b26bb"; };

  };

}
#endif