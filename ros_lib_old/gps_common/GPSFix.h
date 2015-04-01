#ifndef _ROS_gps_common_GPSFix_h
#define _ROS_gps_common_GPSFix_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "gps_common/GPSStatus.h"

namespace gps_common
{

  class GPSFix : public ros::Msg
  {
    public:
      std_msgs::Header header;
      gps_common::GPSStatus status;
      float latitude;
      float longitude;
      float altitude;
      float track;
      float speed;
      float climb;
      float pitch;
      float roll;
      float dip;
      float time;
      float gdop;
      float pdop;
      float hdop;
      float vdop;
      float tdop;
      float err;
      float err_horz;
      float err_vert;
      float err_track;
      float err_speed;
      float err_climb;
      float err_time;
      float err_pitch;
      float err_roll;
      float err_dip;
      float position_covariance[9];
      uint8_t position_covariance_type;
      enum { COVARIANCE_TYPE_UNKNOWN =  0 };
      enum { COVARIANCE_TYPE_APPROXIMATED =  1 };
      enum { COVARIANCE_TYPE_DIAGONAL_KNOWN =  2 };
      enum { COVARIANCE_TYPE_KNOWN =  3 };

    GPSFix():
      header(),
      status(),
      latitude(0),
      longitude(0),
      altitude(0),
      track(0),
      speed(0),
      climb(0),
      pitch(0),
      roll(0),
      dip(0),
      time(0),
      gdop(0),
      pdop(0),
      hdop(0),
      vdop(0),
      tdop(0),
      err(0),
      err_horz(0),
      err_vert(0),
      err_track(0),
      err_speed(0),
      err_climb(0),
      err_time(0),
      err_pitch(0),
      err_roll(0),
      err_dip(0),
