#ifndef USB_H
#define USB_H

#include <stdlib.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>

/* Class for handling the USB device
 * 			//TODO: Turn into a singelton
 * 					// In the mean time use the class appropriately! only one instance!
 */
class usb
{
private:
	struct cdc_acm_descriptors{
		  struct usb_cdc_header_descriptor header;
		  struct usb_cdc_call_management_descriptor call_mgmt;
		  struct usb_cdc_acm_descriptor acm;
		  struct usb_cdc_union_descriptor cdc_union;
		} __attribute__((packed));

public:
	// pointer to the usb device
	usbd_device* usb_device_;
	static const struct usb_config_descriptor config_;
	static const char * usb_strings_[];
	uint8_t usb_control_buffer_[128];
	static const struct usb_device_descriptor device_;
	static const struct usb_config_descriptor::usb_interface ifaces_[];
	static const struct usb_interface_descriptor data_iface_[];

	/*
	 * This notification endpoint isn't implemented. According to CDC spec its
	 * optional, but its absence causes a NULL pointer dereference in Linux
	 * cdc_acm driver.
	 */
	static const struct usb_endpoint_descriptor comm_endp_[];

	static const struct usb_endpoint_descriptor data_endp_[];

	static const struct cdc_acm_descriptors cdcacm_functional_descriptors_;

	static const struct usb_interface_descriptor comm_iface_[];

	static const uint16_t IN_BUF_SIZE = 1024;
	static char in_buf_[];
	static uint16_t in_buf_index_;


private:
	static void cdcacm_set_config(usbd_device *usbd_dev, uint16_t wValue);

	static int cdcacm_control_request(usbd_device *usbd_dev,
		struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
		void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req));
	
	static void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep);

	static void (*read_cb_)(char*, uint8_t);



/* Singelton definitions don't work
	usb() :
		usb_device_(0)
	{

	}

	// Do not implement!
	usb(usb const&){};
	void operator=(usb const&){};

	~usb()
	{
		delete usb_device_;
		usb_device_ = 0;
	}*/

public:
	// Constructor
	usb();

	// Destructor
	~usb();

	/* Get the only instance of usb
	static usb* get_instance()
	{
		static usb instance;
		return &instance;
	}*/

	void init();

	void write(uint8_t* data, int length);

	void poll();

	void setReadCallback(void (*cb)(char*, uint8_t));
};

#endif
