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

#include "xbox_t.h"

#define XBOXARRAYSIZE 20


const char* SH_MEM_NAME = "xbox";
struct xbox_t* vaddr;
int file_desc;


int main(int argc, char *argv[])
{
	libusb_device_handle *h;
	int error, transferred;


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
    if(sem_init(&(vaddr->sem1), 1, 0) != 0){
        perror("cannot sem_init");
        return -1;
    }

    if(sem_init(&(vaddr->sem2), 1, XBOXARRAYSIZE) != 0){
        perror("Can not sem_init");
        return -1;
    }

	unsigned char request[XBOXARRAYSIZE];
	while(1)
	{
		if ((error = libusb_interrupt_transfer(h, 0x81, request, sizeof(request), &transferred, 0)) == 0) {
            sem_wait(&(vaddr->sem2));
            int i;
            for(i = 0; i < XBOXARRAYSIZE;i++)
            {
                vaddr->data[i] = request[i];
            }
            sem_post(&(vaddr->sem1));
		}

	}

	return (0);
}
