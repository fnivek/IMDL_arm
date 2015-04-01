#ifndef _ROS_propagator_motor_driver_motor_driver_statistics_h
#define _ROS_propagator_motor_driver_motor_driver_statistics_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace propagator_motor_driver
{

  class motor_driver_statistics : public ros::Msg
  {
    public:
      std_msgs::Header header;
      const char* id;
      double current;
      double out_voltage;
      double batt_voltage;

    motor_driver_statistics():
      header(),
      id(""),
      current(0),
      out_voltage(0),
      batt_voltage(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      uint32_t length_id = strlen(this->id);
      memcpy(outbuffer + offset, &length_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      union {
        double real;
        uint64_t base;
      } u_current;
      u_current.real = this->current;
      *(outbuffer + offset + 0) = (u_current.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_current.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_current.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_current.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_current.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_current.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_current.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_current.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->current);
      union {
        double real;
        uint64_t base;
      } u_out_voltage;
      u_out_voltage.real = this->out_voltage;
      *(outbuffer + offset + 0) = (u_out_voltage.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_out_voltage.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_out_voltage.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_out_voltage.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_out_voltage.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_out_voltage.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_out_voltage.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_out_voltage.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->out_voltage);
      union {
        double real;
        uint64_t base;
      } u_batt_voltage;
      u_batt_voltage.real = this->batt_voltage;
      *(outbuffer + offset + 0) = (u_batt_voltage.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_batt_voltage.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_batt_voltage.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_batt_voltage.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_batt_voltage.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_batt_voltage.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_batt_voltage.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_batt_voltage.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->batt_voltage);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t length_id;
      memcpy(&length_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      union {
        double real;
        uint64_t base;
      } u_current;
      u_current.base = 0;
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_current.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->current = u_current.real;
      offset += sizeof(this->current);
      union {
        double real;
        uint64_t base;
      } u_out_voltage;
      u_out_voltage.base = 0;
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_out_voltage.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->out_voltage = u_out_voltage.real;
      offset += sizeof(this->out_voltage);
      union {
        double real;
        uint64_t base;
      } u_batt_voltage;
      u_batt_voltage.base = 0;
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_batt_voltage.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->batt_voltage = u_batt_voltage.real;
      offset += sizeof(this->batt_voltage);
     return offset;
    }

    const char * getType(){ return "propagator_motor_driver/motor_driver_statistics"; };
    const char * getMD5(){ return "8baf432df41c7490522afc1b01f0872d"; };

  };

}
#endif