#ifndef _ROS_uf_common_x_h
#define _ROS_uf_common_x_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uf_common
{

  class x : public ros::Msg
  {
    public:
      int32_t data[8];

    x():
