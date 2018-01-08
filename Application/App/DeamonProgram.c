#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "xbox_t.h"

#define XBOXARRAYSIZE 20
#define MQSIZE 10
#define SIZE 1024

#define FIRSTBIT 0b00000001
#define SECONDBIT 0b00000010
#define THIRDBIT 0b00000100
#define FOURTHBIT 0b00001000
#define FIFTHBIT 0b00010000
#define SIXTHBIT 0b00100000
#define SEVENTHBIT 0b01000000
#define EIGHTBIT 0b10000000


const char* SH_MEM_NAME = "xbox";
const char* MQ_NAME = "/xboxMQ";
struct xbox_t* vaddr;
int file_desc;


uint8_t vibrationOn[] = { 0x00, 0x08, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00 };
uint8_t vibrationOff[] = { 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t ledsAlternating[] = { 0x01, 0x03, 0x0D };
void PrintTerminal()
{
  fprintf(stderr, "up %d\n", vaddr->dpadUp);
  fprintf(stderr, "down %d\n", vaddr->dpadDown);
  fprintf(stderr, "left %d\n", vaddr->dpadLeft);
  fprintf(stderr, "right %d\n", vaddr->dpadRight);
  fprintf(stderr, "start %d\n", vaddr->start);
  fprintf(stderr, "back %d\n", vaddr->back);
  fprintf(stderr, "left stick %d\n", vaddr->leftJoystick);
  fprintf(stderr, "right stick %d\n", vaddr->rightJoystick);
  fprintf(stderr, "lb %d\n", vaddr->lb);
  fprintf(stderr, "rb %d\n", vaddr->rb);
  fprintf(stderr, "xbox %d\n", vaddr->xbox);
  fprintf(stderr, "a %d\n", vaddr->a);
  fprintf(stderr, "b %d\n", vaddr->b);
  fprintf(stderr, "x %d\n", vaddr->x);
  fprintf(stderr, "y %d\n", vaddr->y);
}

void ClearVaddr()
{
  vaddr->dpadUp = 0;
  vaddr->dpadDown = 0;
  vaddr->dpadRight = 0;
  vaddr->dpadLeft = 0;
  vaddr->start = 0;
  vaddr->back = 0;
  vaddr->leftJoystick = 0;
  vaddr->rightJoystick = 0;
  vaddr->lb = 0;
  vaddr->rb = 0;
  vaddr->xbox = 0;
  vaddr->a = 0;
  vaddr->b = 0;
  vaddr->x = 0;
  vaddr->y = 0;
}





int main(int argc, char *argv[])
{
    mqd_t mq;
    struct mq_attr attr;
    char buffer[SIZE+1];

    //initialize mqueue
    attr.mq_flags = O_NONBLOCK;
    attr.mq_maxmsg = MQSIZE;
    attr.mq_msgsize = SIZE;
    attr.mq_curmsgs = 0;

    //create msgqueue
    mq = mq_open("/test_queue", O_CREAT | O_RDONLY, 0644, &attr);

    ssize_t bytes_read;
    

  //fprintf(stderr, "TEST\n");
	libusb_device_handle *h;
	int32_t error, transferred;


	libusb_init(NULL);
	h = libusb_open_device_with_vid_pid(NULL, 0x045e, 0x028e);
	if (h == NULL) {
		fprintf(stderr, "Failed to open device\n");
		return (1);
	}

    //open shared mem
    if ((file_desc = shm_open(SH_MEM_NAME, O_CREAT | O_RDWR, 0666)) == -1)
    {
		perror("cannot open shared mem");
		return -1;
    }

    //set shared mem size to size of cijfer struct
    if (ftruncate(file_desc, sizeof(struct xbox_t)) != 0)
    {
		perror("cannot set size of struct");
		return -1;
    }

    //Map shared memory in address space
    if ((vaddr = (struct xbox_t *)mmap(0, sizeof(struct xbox_t), PROT_WRITE, MAP_SHARED, file_desc, 0)) == MAP_FAILED){
		perror("cannot mmap");
		return -1;
    }

    //lock shared mems
    if (mlock(vaddr, sizeof(struct xbox_t)) != 0){
		perror("cannot mlock");
		return -1;
    }

    //initialize semaphores
    if(sem_init(&(vaddr->sem1), 1, 1) != 0){
        perror("cannot sem_init");
        return -1;
    }

     
      
    


	unsigned char request[XBOXARRAYSIZE];
	while(1)
	{
    bytes_read = mq_receive(mq, buffer, SIZE, NULL);
            buffer[bytes_read] = '\0';
            printf("Received message: %s\n", buffer);

            if(strcmp(buffer, "rumble") == 0)
            {
                libusb_interrupt_transfer(h, 0x01, vibrationOn, sizeof vibrationOn, &transferred, 0);
            }
              
            if(strcmp(buffer, "rotate") == 0)
            {
                libusb_interrupt_transfer(h, 0x01, ledsAlternating, sizeof ledsAlternating, &transferred, 0);
              }
              if(strcmp(buffer, "stop") == 0)
            {
                libusb_interrupt_transfer(h, 0x01, vibrationOff, sizeof vibrationOff, &transferred, 0);
            }
              



    

		if ((error = libusb_interrupt_transfer(h, 0x81, request, sizeof(request), &transferred, 0)) == 0) {


            
            sem_wait(&(vaddr->sem1));
            switch(request[2])
            {
              case FIRSTBIT:
              ClearVaddr();
              vaddr->dpadUp = 1;
              break;

              case SECONDBIT:
              ClearVaddr();
              vaddr->dpadDown = 1;
              break;

              case THIRDBIT:
              ClearVaddr();
              vaddr->dpadLeft = 1;
              break;

              case FOURTHBIT:
              ClearVaddr();
              vaddr->dpadRight = 1;
              break;

              case FIFTHBIT:
              ClearVaddr();
              vaddr->start = 1;
              break;

              case SIXTHBIT:
              ClearVaddr();
              vaddr->back = 1;
              break;
              case SEVENTHBIT:
              ClearVaddr();
              vaddr->leftJoystick = 1;
              break;
              case EIGHTBIT:
              ClearVaddr();
              vaddr->rightJoystick = 1;
              break;
              default:
              break;
            }

            switch(request[3])
            {
              case FIRSTBIT:
              ClearVaddr();
              vaddr->lb = 1;
              break;
              case SECONDBIT:
              ClearVaddr();
              vaddr->rb = 1;
              break;
              case THIRDBIT:
              ClearVaddr();
              vaddr->xbox = 1;
              break;
              case FIFTHBIT:
              ClearVaddr();
              vaddr->a = 1;
              break;
              case SIXTHBIT:
              ClearVaddr();
              vaddr->b = 1;
              break;
              case SEVENTHBIT:
              ClearVaddr();
              vaddr->x = 1;
              break;
              case EIGHTBIT:
              ClearVaddr();
              vaddr->y = 1;
              break;
              default:
              break;
          
            }
            PrintTerminal();
            sem_post(&(vaddr->sem1));  
          }
          else{
            fprintf(stderr, "Failed to open USB\n");
          }
    
    
    


	}

	return (0);
}
