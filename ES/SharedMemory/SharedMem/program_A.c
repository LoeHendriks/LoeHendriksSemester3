#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include "cijfer_t.h"

#define STRINGSIZE 100

const char* SH_MEM_NAME = "cijfer";
struct cijfer_t *vaddr;
int file_desc;


void Quit(int a){
    munmap(vaddr, sizeof(struct cijfer_t));
    close(file_desc);
    shm_unlink(SH_MEM_NAME);
    sem_close(&(vaddr->semaphore));
    printf("\nCLOSED\n");
    exit(0);
}


int main()
{

    //open shared mem
    if ((file_desc = shm_open(SH_MEM_NAME, O_CREAT | O_RDWR, 0666)) == -1)
    {
		perror("cannot open shared mem");
		return -1;
    }

    //set shared mem size to size of cijfer struct
    if (ftruncate(file_desc, sizeof(struct cijfer_t)) != 0)
    {
		perror("cannot set size of struct");
		return -1;
    }

    //Map shared memory in address space
    if ((vaddr = (struct cijfer_t *)mmap(0, sizeof(struct cijfer_t), PROT_WRITE, MAP_SHARED, file_desc, 0)) == MAP_FAILED){
		perror("cannot mmap");
		return -1;
    }

    //lock shared mems
    if (mlock(vaddr, sizeof(struct cijfer_t)) != 0){
		perror("cannot mlock");
		return -1;
    }

    //initialize semaphore
    if(sem_init(&(vaddr->semaphore), 1, 1) != 0){
        perror("cannot sem_init");
        return -1;
    }

    //start function quit on CRT C
    signal(SIGINT, Quit);
    //int i for waarde in struct
    int i = 0;
    //while loop checks i so uitspraak can be correct
    while(1)
    {
        sem_wait(&(vaddr->semaphore));
        vaddr->waarde = i;
        switch(i)
        {
            case 0:
                strcpy(vaddr->uitspraak, "zero");
                break;
            case 1:
                strcpy(vaddr->uitspraak, "one");
                break;
            case 2:
                strcpy(vaddr->uitspraak, "two");
                break;
            case 3:
                strcpy(vaddr->uitspraak, "three");
                break;
            case 4:
                strcpy(vaddr->uitspraak, "four");
                break;
            case 5:
                strcpy(vaddr->uitspraak, "five");
                break;
            case 6:
                strcpy(vaddr->uitspraak, "six");
                break;
            case 7:
                strcpy(vaddr->uitspraak, "seven");
                break;
            case 8:
                strcpy(vaddr->uitspraak, "eight");
                break;
            case 9:
                strcpy(vaddr->uitspraak, "nine");
                break;
            }
            sem_post(&(vaddr->semaphore));
        i++;
        if(i == 10)
        {
            i = 0;
        }
    }
    
    

}

