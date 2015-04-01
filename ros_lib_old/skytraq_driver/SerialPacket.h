#ifndef _ROS_skytraq_driver_SerialPacket_h
#define _ROS_skytraq_driver_SerialPacket_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace skytraq_driver
{

  class SerialPacket : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t payload_length;
      uint8_t st_payload;
      uint8_t * payload;

    SerialPacket():
      header(),
      payload_length(0), payload(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = payload_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < payload_length; i++){
      *(outbuffer + offset + 0) = (this->payload[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->payload[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t payload_lengthT = *(inbuffer + offset++);
      if(payload_lengthT > payload_length)
        this->payload = (uint8_t*)realloc(this->payload, payload_lengthT * sizeof(uint8_t));
      offset += 3;
      payload_length = payload_lengthT;
      for( uint8_t i = 0; i < payload_length; i++){
      this->st_payload =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_payload);
        memcpy( &(this->payload[i]), &(this->st_payload), sizeof(uint8_t));
      }
     return offset;
    }

    const char * getType(){ return "skytraq_driver/SerialPacket"; };
    const char * getMD5(){ return "ae368072b59df9e83153f5182b924dbc"; };

  };

}
#endif