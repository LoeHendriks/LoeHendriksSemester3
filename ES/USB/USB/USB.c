
#include <libusb-1.0/libusb.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	libusb_device_handle *h;

	unsigned char FullVibrate[] = { 0x00, 0x08, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00 };
	unsigned char TurnOffVibrate[] = { 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char led1[] = { 0x01, 0x03, 0x06 };
  	unsigned char led2[] = { 0x01, 0x03, 0x07 };
  	unsigned char led3[] = { 0x01, 0x03, 0x08 };
	unsigned char led4[] = { 0x01, 0x03, 0x09 };
	unsigned char ledsBlinking[] = { 0x01, 0x03, 0x01 };
	unsigned char ledsAlternating[] = { 0x01, 0x03, 0x0D };
	int error, transferred;

	int LTpressed = 0;
	int RTpressed = 0;
	int CheckjoyStick = 0;

	libusb_init(NULL);
	h = libusb_open_device_with_vid_pid(NULL, 0x045e, 0x028e);
	if (h == NULL) {
		fprintf(stderr, "Failed to open device\n");
		return (1);
	}

	unsigned char request[20];
	while(1)
	{
		if ((error = libusb_interrupt_transfer(h, 0x81, request, sizeof(request), &transferred, 0)) == 0) {

			switch(request[2])
			{
				case 0b00000001:
				fprintf(stderr, "Dpad: UP\n");
				CheckjoyStick = 1;
				break;

				case 0b00000010:
				fprintf(stderr, "Dpad: DOWN\n");
				CheckjoyStick = 0;
				break;

				case 0b00000100:
				fprintf(stderr, "Dpad: LEFT\n");
				break;

				case 0b00001000:
				fprintf(stderr, "Dpad: RIGHT\n");
				break;

				case 0b00010000:
				fprintf(stderr, "START\n");
				libusb_interrupt_transfer(h, 0x01, FullVibrate, sizeof FullVibrate, &transferred, 0);
				break;

				case 0b00100000:
				fprintf(stderr, "BACK\n");
				libusb_interrupt_transfer(h, 0x01, TurnOffVibrate, sizeof TurnOffVibrate, &transferred, 0);
				break;
				case 0b01000000:
				fprintf(stderr, "LEFTBUMBER\n");
				libusb_interrupt_transfer(h, 0x01, ledsBlinking, sizeof ledsBlinking, &transferred, 0);
				break;
				case 0b10000000:
				fprintf(stderr, "RIGHTBUMBER\n");
				libusb_interrupt_transfer(h, 0x01, ledsAlternating, sizeof ledsAlternating, &transferred, 0);
				break;
			}

			switch(request[3])
			{
				case 0b00000001:
				fprintf(stderr, "Button: LEFTBACK\n");
				break;
				case 0b00000010:
				fprintf(stderr, "Button: RIGHTBACK\n");
				break;
				case 0b00000100:
				fprintf(stderr, "Button: XBOXLOGO\n");
				break;
				case 0b00010000:
				fprintf(stderr, "Button: A\n");
				libusb_interrupt_transfer(h, 0x01, led3, sizeof led1, &transferred, 0);
				break;
				case 0b00100000:
				fprintf(stderr, "Button: B\n");
				libusb_interrupt_transfer(h, 0x01, led4, sizeof led1, &transferred, 0);
				break;
				case 0b01000000:
				fprintf(stderr, "Button: X\n");
				libusb_interrupt_transfer(h, 0x01, led1, sizeof led1, &transferred, 0);
				break;
				case 0b10000000:
				fprintf(stderr, "Button: Y\n");
				libusb_interrupt_transfer(h, 0x01, led2, sizeof led1, &transferred, 0);
				break;
			}


			if(!LTpressed && request[4] >= 250)
			{
				LTpressed = 1;
				fprintf(stderr, "Button: LEFTTRIGGER\n");

			}
			else if (request[4] < 240){
				LTpressed = 0;
			}
		
			if(!RTpressed && request[5] >= 250)
			{
				RTpressed = 1;
				fprintf(stderr, "Button: RIGHTTRIGGER\n");

			}
			else if (request[5] < 240){
				RTpressed = 0;
			}

			if(CheckjoyStick == 1)
			{
				if(request[6] || request [8])
				{
					int x = request[6];
					int y = request[8];
					printf("X-as Waarde: %d\n",x);
					printf("Y-as Waarde: %d\n",y);
		
				}
			}
			


		}

	}

	return (0);
}
