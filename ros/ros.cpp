#include "ros.h"
namespace ros
{
	void NodeHandle::hardwareUpdate()
	{
		hardware_.hardwareUpdate();
	}

	/*NodeHandle::NodeHandle() :
		ros::NodeHandle_<board>()*/
}