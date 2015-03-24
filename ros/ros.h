/*
 *		Header for ros stuff
 */

#ifndef ROS_H
#define ROS_H

#include "node_handle.h"
#include "../board.h"

namespace ros
{
	typedef ros::NodeHandle_<board> NodeHandle;
}

#endif