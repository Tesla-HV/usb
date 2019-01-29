#include <stdio.h>
#include "libusb.h"

int main(int argc, char *argv[]) {

	libusb_context *context;
	libusb_init(&context);

	ssize_t sz;
	sz = libusb_get_device_list(context, list);


	libusb_free_device_list(list, 0);

	libusb_exit(context); 	
	return 0;
}


