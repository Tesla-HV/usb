#include <stdio.h>
#include "libusb.h"

int main(int argc, char *argv[]) {

	struct libusb_device_descriptor desc;

	libusb_context *context;
	libusb_init(&context);

	ssize_t sz;
	libusb_device **list;
	sz = libusb_get_device_list(context, &list);

	for (ssize_t i = 0; i < sz; i++) {

		int status = libusb_get_device_descriptor(list[i], &desc);
		if (status >= 0) {
			printf("%04X:%04X\n", desc.idVendor, desc.idProduct);
			printf("bDeviceClass %d\n", desc.bDeviceClass);
			printf("bDeviceSubClass %d\n", desc.bDeviceSubClass);
			printf("\n");
		}

	}


	libusb_free_device_list(list, 1);

	libusb_exit(context); 	
	return 0;
}


