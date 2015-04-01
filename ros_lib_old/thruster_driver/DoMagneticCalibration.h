#ifndef _ROS_SERVICE_DoMagneticCalibration_h
#define _ROS_SERVICE_DoMagneticCalibration_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace thruster_driver
{

static const char DOMAGNETICCALIBRATION[] = "thruster_driver/DoMagneticCalibration";

  class DoMagneticCalibrationRequest : public ros::Msg
  {
    public:

    DoMagneticCalibrationRequest()
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

    const char * getType(){ return DOMAGNETICCALIBRATION; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class DoMagneticCalibrationResponse : public ros::Msg
  {
    public:

    DoMagneticCalibrationResponse()
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

    const char * getType(){ return DOMAGNETICCALIBRATION; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class DoMagneticCalibration {
    public:
    typedef DoMagneticCalibrationRequest Request;
    typedef DoMagneticCalibrationResponse Response;
  };

}
#endif
