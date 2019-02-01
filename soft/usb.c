#include <stdio.h>

#include <stdbool.h>
#include "libusb.h"

#define RW_INTERNAL     0xA0
#define RW_MEMORY       0xA3


int work(libusb_device_handle *device) {

	unsigned char data[128];

	int status;
	int transferred;

	while (1) {
		status = libusb_bulk_transfer(device, 0x86, data, sizeof(data), &transferred, 1000);
		if (status < 0) {
			fprintf(stderr, "libusb_bulk_transfer() failed: %s\n", libusb_error_name(status));
			return -1;
		}

		printf("%s\n", data);
	}

	return 0;
}



int main(int argc, char *argv[]) {

	struct libusb_device_descriptor desc;
	struct libusb_context *context;
	libusb_device_handle *device;
	int status;

	status = libusb_init(&context);
	if (status < 0) {
		fprintf(stderr, "libusb_init() failed: %s\n", libusb_error_name(status));
		return -1;
	}


	ssize_t sz;
	struct libusb_device **list;
	sz = libusb_get_device_list(context, &list);
	if (sz < 0) {
		fprintf(stderr, "libusb_get_device_list() failed: %s\n", libusb_error_name(sz));
		goto err;
	}


	struct libusb_device *dev = NULL;

	for (ssize_t i = 0; i < sz; i++) {

		status = libusb_get_device_descriptor(list[i], &desc);
		if (status >= 0) {
			//printf("%04X:%04X\n", desc.idVendor, desc.idProduct);
			if (desc.idVendor == 0x04B4 && desc.idProduct == 0x8613) {
				dev = list[i];
				break;
			}
		}

	}


	if (dev == NULL) {
		fprintf(stderr, "Device not found\n");
		libusb_free_device_list(list, 1);
		goto err;
	}

	status = libusb_open(dev, &device);
	libusb_free_device_list(list, 1);
	if (status < 0) {
		fprintf(stderr, "libusb_open() failed: %s\n", libusb_error_name(status));
		goto err;
	}

	libusb_set_auto_detach_kernel_driver(device, 1);
	status = libusb_claim_interface(device, 0);
	if (status != LIBUSB_SUCCESS) {
		libusb_close(device);
		fprintf(stderr, "libusb_claim_interface failed: %s\n", libusb_error_name(status));
		goto err;
	}

	status = libusb_set_interface_alt_setting(device, 0, 1);
	if (status != LIBUSB_SUCCESS) {
		libusb_close(device);
		fprintf(stderr, "libusb_set_interface_alt_setting failed: %s\n", libusb_error_name(status));
		goto err;
	}

	work(device);


	libusb_release_interface(device, 0);
	libusb_close(device);


	libusb_exit(context);
	return 0;

err:
	libusb_exit(context);
	return -1;
}


