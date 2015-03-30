#include "ros.h"
namespace ros
{
	void NodeHandle::hardwareUpdate()
	{
		hardware_.hardwareUpdate();
	}
}