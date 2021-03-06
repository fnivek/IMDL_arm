/*
 * usb.c
 *
 *  Created on: Feb 22, 2015
 *      Author: fnivek
 */


#include "usb.h"

const char* usb::usb_strings_[] = {
	"KipCDroid",
	"HardwareInterface"
};

/*
 * This notification endpoint isn't implemented. According to CDC spec its
 * optional, but its absence causes a NULL pointer dereference in Linux
 * cdc_acm driver.
 */
const struct usb_endpoint_descriptor usb::comm_endp_[] = {{
  .bLength = USB_DT_ENDPOINT_SIZE,
  .bDescriptorType = USB_DT_ENDPOINT,
  .bEndpointAddress = 0x83,
  .bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
  .wMaxPacketSize = 16,
  .bInterval = 255,
}};

const struct usb_endpoint_descriptor usb::data_endp_[] = {{
  .bLength = USB_DT_ENDPOINT_SIZE,
  .bDescriptorType = USB_DT_ENDPOINT,
  .bEndpointAddress = 0x01,
  .bmAttributes = USB_ENDPOINT_ATTR_BULK,
  .wMaxPacketSize = 64,
  .bInterval = 1,
}, {
  .bLength = USB_DT_ENDPOINT_SIZE,
  .bDescriptorType = USB_DT_ENDPOINT,
  .bEndpointAddress = 0x82,
  .bmAttributes = USB_ENDPOINT_ATTR_BULK,
  .wMaxPacketSize = 64,
  .bInterval = 1,
}};

const struct usb::cdc_acm_descriptors_ usb::cdcacm_functional_descriptors_ = {
  .header = {
	.bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
	.bDescriptorType = CS_INTERFACE,
	.bDescriptorSubtype = USB_CDC_TYPE_HEADER,
	.bcdCDC = 0x0110,
  },
  .call_mgmt = {
	.bFunctionLength =
	  sizeof(struct usb_cdc_call_management_descriptor),
	.bDescriptorType = CS_INTERFACE,
	.bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
	.bmCapabilities = 0,
	.bDataInterface = 1,
  },
  .acm = {
	.bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
	.bDescriptorType = CS_INTERFACE,
	.bDescriptorSubtype = USB_CDC_TYPE_ACM,
	.bmCapabilities = 0,
  },
  .cdc_union = {
	.bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
	.bDescriptorType = CS_INTERFACE,
	.bDescriptorSubtype = USB_CDC_TYPE_UNION,
	.bControlInterface = 0,
	.bSubordinateInterface0 = 1,
   },
};

const struct usb_interface_descriptor usb::comm_iface_[] = {{
  .bLength = USB_DT_INTERFACE_SIZE,
  .bDescriptorType = USB_DT_INTERFACE,
  .bInterfaceNumber = 0,
  .bAlternateSetting = 0,
  .bNumEndpoints = 1,
  .bInterfaceClass = USB_CLASS_CDC,
  .bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
  .bInterfaceProtocol = USB_CDC_PROTOCOL_AT,
  .iInterface = 0,

  .endpoint = comm_endp_,

  .extra = &cdcacm_functional_descriptors_,
  .extralen = sizeof(cdcacm_functional_descriptors_),
}};

const struct usb_interface_descriptor usb::data_iface_[] = {{
  .bLength = USB_DT_INTERFACE_SIZE,
  .bDescriptorType = USB_DT_INTERFACE,
  .bInterfaceNumber = 1,
  .bAlternateSetting = 0,
  .bNumEndpoints = 2,
  .bInterfaceClass = USB_CLASS_DATA,
  .bInterfaceSubClass = 0,
  .bInterfaceProtocol = 0,
  .iInterface = 0,

  .endpoint = data_endp_,

  .extra = NULL,
  .extralen = 0,
}};

const struct usb_config_descriptor::usb_interface usb::ifaces_[] = {{
//  .cur_altsetting = NULL,
  .num_altsetting = 1,
  .iface_assoc = NULL,
  .altsetting = comm_iface_,
}, {
//  .cur_altsetting = NULL,
  .num_altsetting = 1,
  .iface_assoc = NULL,
  .altsetting = data_iface_,
}};

const struct usb_config_descriptor usb::config_ = {
		  .bLength = USB_DT_CONFIGURATION_SIZE,
		  .bDescriptorType = USB_DT_CONFIGURATION,
		  .wTotalLength = 0,
		  .bNumInterfaces = 2,
		  .bConfigurationValue = 1,
		  .iConfiguration = 0,
		  .bmAttributes = 0x80,
		  .bMaxPower = 0x32,

		  .interface = ifaces_,
		};

const struct usb_device_descriptor usb::device_ = {
		  .bLength = USB_DT_DEVICE_SIZE,
		  .bDescriptorType = USB_DT_DEVICE,
		  .bcdUSB = 0x0200,
		  .bDeviceClass = USB_CLASS_CDC,
		  .bDeviceSubClass = 0,
		  .bDeviceProtocol = 0,
		  .bMaxPacketSize0 = 64,
		  .idVendor = 0x0483,
		  .idProduct = 0x5740,
		  .bcdDevice = 0x0200,
		  .iManufacturer = 1,
		  .iProduct = 2,
		  .iSerialNumber = 3,
		  .bNumConfigurations = 1,
		};

void usb::cdcacm_data_rx_cb(usbd_device *usbd_dev, uint8_t ep)
{
	(void)ep;

	char buf[64];
	uint8_t len = usbd_ep_read_packet(usbd_dev, 0x01, buf, 64);

	isConnected_ = true;

	if(usb::read_cb_ != NULL)
	{
		read_cb_(buf, len);
	}


	// Echo function
	//if (len) {
	//	while (usbd_ep_write_packet(usbd_dev, 0x82, buf, len) == 0);
	//}
}

int usb::cdcacm_control_request(usbd_device *usbd_dev,
	struct usb_setup_data *req, uint8_t **buf, uint16_t *len,
	void (**complete)(usbd_device *usbd_dev, struct usb_setup_data *req))
{
	(void)complete;
	(void)buf;
	(void)usbd_dev;

	switch (req->bRequest) {
	case USB_CDC_REQ_SET_CONTROL_LINE_STATE: {
		/*
		 * This Linux cdc_acm driver requires this to be implemented
		 * even though it's optional in the CDC spec, and we don't
		 * advertise it in the ACM functional descriptor.
		 */
		return 1;
		}
	case USB_CDC_REQ_SET_LINE_CODING:
		if (*len < sizeof(struct usb_cdc_line_coding)) {
			return 0;
		}

		return 1;
	}
	return 0;
}

void usb::cdcacm_set_config(usbd_device *usbd_dev, uint16_t wValue)
{
	(void)wValue;

	usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64,
			cdcacm_data_rx_cb);
	usbd_ep_setup(usbd_dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, NULL);
	usbd_ep_setup(usbd_dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);

	usbd_register_control_callback(
				usbd_dev,
				USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
				USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
				cdcacm_control_request);
}



// Constructor
usb::usb() :
	usb_device_(0)
{
	// Initilize the GPIO and clocks
	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_OTGFS);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE,			// Set USB GPIO in Alternate function mode (AF)
	  GPIO9 | GPIO11 | GPIO12);
	gpio_set_af(GPIOA, GPIO_AF10, GPIO9 | GPIO11 | GPIO12);			// Set alternate function to USB mode



	// Initilze the device with the
	usb_device_ = usbd_init(&otgfs_usb_driver, 	// on the go fs mode
							&usb::device_,			// defined above
							&usb::config_,			// defined above
							usb::usb_strings_, 2,	// USB ID (size 2)
							usb_control_buffer_, sizeof(usb_control_buffer_));	// Control buffer and size

	// Set the reconfiguration callback function
	usbd_register_set_config_callback(usb_device_, usb::cdcacm_set_config);
}

// Destructor
usb::~usb()
{
	delete usb_device_;
	usb_device_ = 0;
}

// Get the only instance of usb
usb* usb::get_instance()
{
	if(usb::single_ == NULL)
	{
		usb::single_ = new usb();
	}
	return usb::single_;
}

void usb::poll()
{
	usbd_poll(usb_device_);
}

uint16_t usb::write(const void* data, uint16_t length)
{
	if(isConnected_)
	{
		return usbd_ep_write_packet(usb_device_, 0x82, data, length);
	}
	else
	{
		return 0;
	}
}

void usb::setReadCallback(void (*cb)(char*, uint16_t))
{
	if(cb == NULL)
	{
		return;
	}
	else
	{
		usb::read_cb_ = cb;
	}
}

bool usb::isConnected_ = false;
void (*usb::read_cb_)(char*, uint16_t) = NULL;
usb* usb::single_ = NULL;