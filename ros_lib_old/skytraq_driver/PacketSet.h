#ifndef _ROS_skytraq_driver_PacketSet_h
#define _ROS_skytraq_driver_PacketSet_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "skytraq_driver/Packet.h"

namespace skytraq_driver
{

  class PacketSet : public ros::Msg
  {
    public:
      uint8_t packets_length;
      skytraq_driver::Packet st_packets;
      skytraq_driver::Packet * packets;

    PacketSet():
      packets_length(0), packets(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = packets_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < packets_length; i++){
      offset += this->packets[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t packets_lengthT = *(inbuffer + offset++);
      if(packets_lengthT > packets_length)
        this->packets = (skytraq_driver::Packet*)realloc(this->packets, packets_lengthT * sizeof(skytraq_driver::Packet));
      offset += 3;
      packets_length = packets_lengthT;
      for( uint8_t i = 0; i < packets_length; i++){
      offset += this->st_packets.deserialize(inbuffer + offset);
        memcpy( &(this->packets[i]), &(this->st_packets), sizeof(skytraq_driver::Packet));
      }
     return offset;
    }

    const char * getType(){ return "skytraq_driver/PacketSet"; };
    const char * getMD5(){ return "d07230579551311e654178a7a5cd7202"; };

  };

}
#endif