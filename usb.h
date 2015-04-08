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
private:	// Data types
	struct cdc_acm_descriptors_{
		  struct usb_cdc_header_descriptor header;
		  struct usb_cdc_call_management_descriptor call_mgmt;
		  struct usb_cdc_acm_descriptor acm;
		  struct usb_cdc_union_descriptor cdc_union;
		} __attribute__((packed));

public:		// Constants
	
	// Controls the id of the usb
	static const char * usb_strings_[];

	// Descriptors
	static const struct usb_config_descriptor config_;
	static const struct usb_device_descriptor device_;
	static const struct usb_config_descriptor::usb_interface ifaces_[];
	static const struct usb_interface_descriptor data_iface_[];
	static const struct cdc_acm_descriptors_ cdcacm_functional_descriptors_;
	static const struct usb_interface_descriptor comm_iface_[];
		/*
		 * This notification endpoint isn't implemented. According to CDC spec its
		 * optional, but its absence causes a NULL pointer dereference in Linux
		 * cdc_acm driver.
		 */
	static const struct usb_endpoint_descriptor comm_endp_[];
	static const struct usb_endpoint_descriptor data_endp_[];

public:		// Vars
	// pointer to the usb device
	usbd_device* usb_device_;

	uint8_t usb_control_buffer_[128];

private:	// Vars
	// Read callback
	static void (*read_cb_)(void*, uint16_t);

	// Singelton instance
	static usb* single_;

	// Has the usb recieved any data yet
	static bool isConnected_;


private:	// Functions
	static void cdcacm_set_config(usbd_device *usbd_dev, uint16_t wValue);

	static int cdcacm_control_request(usbd_device *usbd_dev,
		struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
		void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req));
	
	static void cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep);

	// Singelton definitions
	usb();

		// Do not implement!
	usb(usb const&){};
	void operator=(usb const&){};

	~usb();

public:
	// Get the only instance of usb
	static usb* get_instance();

	// Write the data out to the usb
	//	Returns the length of data sent out
	//	If 0 then we are still transmiting
	uint16_t write(const void* data, uint16_t length);

	// Keep The USB alive
	void poll();

	// Set or update the read callback
	//		Set to NULL for no callback
	void setReadCallback(void (*cb)(void*, uint16_t));
};

#endif
