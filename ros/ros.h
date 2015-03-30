/*
 *		Header for ros stuff
 */

#ifndef ROS_H
#define ROS_H

#include "node_handle.h"
#include "../board.h"

namespace ros
{
	class NodeHandle : public ros::NodeHandle_<board>
	{
	public:
		void hardwareUpdate();
		//NodeHandle::NodeHandle();
	};
}

#endif