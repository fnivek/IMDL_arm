#ifndef _ROS_actuator_driver_Switches_h
#define _ROS_actuator_driver_Switches_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace actuator_driver
{

  class Switches : public ros::Msg
  {
    public:
      std_msgs::Header header;
      bool pressed[2];

    Switches():
      header(),
