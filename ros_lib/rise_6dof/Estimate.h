#ifndef _ROS_rise_6dof_Estimate_h
#define _ROS_rise_6dof_Estimate_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace rise_6dof
{

  class Estimate : public ros::Msg
  {
    public:
      std_msgs::Header header;
      float theta_hat[8];
      float x_hat[6];

    Estimate():
      header(),
