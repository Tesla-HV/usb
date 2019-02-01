#include <stdio.h>
#include <stdbool.h>
#include "libusb.h"

struct datachunk {
	uint16_t addr;
	uint16_t len;
	uint8_t *data;
};

struct datachunk fw[] = {
	{ 0x0000, 3, (uint8_t[]) { 0x02, 0x00, 0x06 } },
	{ 0x005F, 3, (uint8_t[]) { 0x02, 0x00, 0x03 } },
	{ 0x0003, 3, (uint8_t[]) { 0x02, 0x00, 0x62 } },
	{ 0x0062, 77, (uint8_t[]) { 0x90, 0xE6, 0x80, 0xE0, 0xFF, 0x74, 0x08, 0x4F, 0xF0, 0x7E,
		0xFF, 0x7F, 0xFF, 0x00, 0x1E, 0xBE, 0xFF, 0x01, 0x1F, 0xEE,
		0x4F, 0x70, 0xF6, 0x90, 0xE6, 0x80, 0xE0, 0xFF, 0x74, 0xF7,
		0x5F, 0xF0, 0x90, 0xE6, 0x5C, 0xE4, 0xF0, 0x43, 0xB4, 0x01,
		0x7E, 0xFF, 0x7F, 0xFF, 0x00, 0x1E, 0xBE, 0xFF, 0x01, 0x1F,
		0xEE, 0x4F, 0x70, 0xF6, 0xAF, 0xB4, 0x74, 0xFE, 0x5F, 0xF5,
		0xB4, 0x7E, 0xFF, 0x7F, 0xFF, 0x00, 0x1E, 0xBE, 0xFF, 0x01,
		0x1F, 0xEE, 0x4F, 0x70, 0xF6, 0x80, 0xD8 } },
	{ 0x0035, 6, (uint8_t[]) { 0xE4, 0x78, 0xFF, 0xF6, 0xD8, 0xFD } },
	{ 0x0013, 34, (uint8_t[]) { 0x79, 0x00, 0xE9, 0x44, 0x00, 0x60, 0x1B, 0x7A, 0x00, 0x90,
		0x00, 0xB3, 0x78, 0x01, 0x75, 0x92, 0x00, 0xE4, 0x93, 0xF2,
		0xA3, 0x08, 0xB8, 0x00, 0x02, 0x05, 0x92, 0xD9, 0xF4, 0xDA,
		0xF2, 0x75, 0x92, 0xFF } },
	{ 0x003B, 36, (uint8_t[]) { 0x78, 0x00, 0xE8, 0x44, 0x00, 0x60, 0x0A, 0x79, 0x01, 0x75,
		0x92, 0x00, 0xE4, 0xF3, 0x09, 0xD8, 0xFC, 0x78, 0x00, 0xE8,
		0x44, 0x00, 0x60, 0x0C, 0x79, 0x00, 0x90, 0x00, 0x01, 0xE4,
		0xF0, 0xA3, 0xD8, 0xFC, 0xD9, 0xFA } },
	{ 0x0006, 13, (uint8_t[]) { 0x75, 0x81, 0x07, 0x12, 0x00, 0xAF, 0xE5, 0x82, 0x60, 0x03, 0x02, 0x00, 0x03 } },
	{ 0x00AF, 4, (uint8_t[]) { 0x75, 0x82, 0x00, 0x22 } },
	{ 0, 0, NULL }
};


#define RW_INTERNAL     0xA0
#define RW_MEMORY       0xA3


/*int work(libusb_device_handle *device) {

	struct datachunk *chunk;

	int status;

	uint32_t addr;
	uint8_t data;

	addr = 0xE600;
	data = 0x01;
	status = libusb_control_transfer(device,
		LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
		RW_INTERNAL, addr & 0xFFFF, addr >> 16,
		&data, 1, 1000);	

	if (status < 0) {
		fprintf(stderr, "libusb_control_transfer() failed: %s\n", libusb_error_name(status));
		return -1;
	}



	for (chunk = fw; chunk->data != NULL; chunk++) {

		printf("%04X %02X |", chunk->addr, chunk->len);
		for (int i = 0; i < chunk->len; i++) {
			printf(" %02X", chunk->data[i]);
		}
		printf("\n");

		addr = chunk->addr;
		status = libusb_control_transfer(device,
			LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
			RW_INTERNAL, addr & 0xFFFF, addr >> 16,
			(unsigned char*)chunk->data, (uint16_t)chunk->len, 1000);
		if (status != chunk->len) {
			fprintf(stderr, "libusb_control_transfer() failed: %s\n", libusb_error_name(status));
			return -1;
		}

	}

	addr = 0xE600;
	data = 0x00;
	status = libusb_control_transfer(device,
		LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
		RW_INTERNAL, addr & 0xFFFF, addr >> 16,
		&data, 1, 1000);	

	if (status < 0) {
		fprintf(stderr, "libusb_control_transfer() failed: %s\n", libusb_error_name(status));
		return -1;
	}



	return 0;
}*/

int work(libusb_device_handle *device) {

	struct datachunk *chunk;

	int status;

	uint32_t addr;
	uint8_t data;

	addr = 0x00B4;
	data = 0x01;
	status = libusb_control_transfer(device,
		LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
		RW_INTERNAL, addr & 0xFFFF, addr >> 16,
		&data, 1, 1000);	

	if (status < 0) {
		fprintf(stderr, "libusb_control_transfer() failed: %s\n", libusb_error_name(status));
		return -1;
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



	work(device);


	libusb_release_interface(device, 0);
	libusb_close(device);


	libusb_exit(context); 	
	return 0;

err:
	libusb_exit(context);
	return -1;
}


