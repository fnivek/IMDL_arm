#include "HC-SR04_Array.h"

hc_sr04_array::hc_sr04_array()
{

}

hc_sr04_array::~hc_sr04_array()
{

}

hc_sr04_array* hc_sr04_array::get_instance()
{
	if(hc_sr04_array::single_ == 0)
	{
		hc_sr04_array::single_ = new hc_sr04_array();
		//hc_sr04_array::single_->init_();
	}

	return hc_sr04_array::single_;
}

hc_sr04_array* hc_sr04_array::single_ = 0;