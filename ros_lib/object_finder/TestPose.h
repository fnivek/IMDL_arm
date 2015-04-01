#ifndef _ROS_SERVICE_TestPose_h
#define _ROS_SERVICE_TestPose_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"

namespace object_finder
{

static const char TESTPOSE[] = "object_finder/TestPose";

  class TestPoseRequest : public ros::Msg
  {
    public:
      geometry_msgs::Pose pose;

    TestPoseRequest():
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return TESTPOSE; };
    const char * getMD5(){ return "f192399f711a48924df9a394d37edd67"; };

  };

  class TestPoseResponse : public ros::Msg
  {
    public:
      double correlation;

    TestPoseResponse():
      correlation(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_correlation;
      u_correlation.real = this->correlation;
      *(outbuffer + offset + 0) = (u_correlation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_correlation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_correlation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_correlation.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_correlation.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_correlation.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_correlation.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_correlation.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->correlation);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        double real;
        uint64_t base;
      } u_correlation;
      u_correlation.base = 0;
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_correlation.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->correlation = u_correlation.real;
      offset += sizeof(this->correlation);
     return offset;
    }

    const char * getType(){ return TESTPOSE; };
    const char * getMD5(){ return "ae6a8fb21b94ed31af34b587b784da25"; };

  };

  class TestPose {
    public:
    typedef TestPoseRequest Request;
    typedef TestPoseResponse Response;
  };

}
#endif
