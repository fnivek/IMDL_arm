#ifndef _ROS_object_finder_Triangle_h
#define _ROS_object_finder_Triangle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace object_finder
{

  class Triangle : public ros::Msg
  {
    public:
      geometry_msgs::Point corners[3];

    Triangle():
