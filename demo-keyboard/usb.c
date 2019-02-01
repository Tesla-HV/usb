#include <stdio.h>
#include "libusb.h"
#include <unistd.h>

int work(libusb_device_handle *device) {

	int status;
	unsigned char data[8];
	int transferred;

	unsigned char data2[1] = { 0x00 };

	while (1) {

		/*status = libusb_interrupt_transfer(device, 0x81, data, sizeof(data), &transferred, 10000);
		if (status < 0) {
			fprintf(stderr, "libusb_interrupt_transfer() failed: %s\n", libusb_error_name(status));
			return -1;
		}

		for (int i = 0; i < transferred; i++) {
			printf(" %02X", data[i]);
		}
		printf("\n");*/

		status = libusb_control_transfer(device, 0x21, 0x09, 0x0200, 0x0000, data2, sizeof(data2), 10000);
		if (status < 0) {
			fprintf(stderr, "libusb_control_transfer() failed: %s\n", libusb_error_name(status));
			return -1;
		}

		data2[0] = (data2[0]+1)&7;

		usleep(20000);

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
			if (desc.idVendor == 0x045E && desc.idProduct == 0x0752) {
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

	work(device);

	libusb_release_interface(device, 0);
	libusb_close(device);

	libusb_exit(context);
	return 0;

err:
	libusb_exit(context);
	return -1;
}


