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
#include "cijferBuffer_t.h"

#define STRINGSIZE 100

const char* SH_MEM_NAME = "cijfer";
struct cijferBuffer_t *vaddr;
int file_desc;


void Quit()
{
    munmap(vaddr, sizeof(struct cijferBuffer_t));
	close(file_desc);
    shm_unlink(SH_MEM_NAME);
    sem_close(&(vaddr->sem));
    sem_close(&(vaddr->sem2));
    printf("\nCLOSED\n");
    exit(0);
}


int main()
{
    //char quitString[STRINGSIZE + 1]; 

    //open shared mem
    if ((file_desc = shm_open(SH_MEM_NAME, O_CREAT | O_RDWR, 0666)) == -1)
    {
		perror("cannot open shared mem");
		return -1;
    }

    //set shared mem size to size of cijfer struct
    if (ftruncate(file_desc, sizeof(struct cijferBuffer_t)) != 0)
    {
		perror("cannot set size of struct");
		return -1;
    }

    //Map shared memory in address space
    if ((vaddr = (struct cijferBuffer_t *)mmap(0, sizeof(struct cijferBuffer_t), PROT_WRITE, MAP_SHARED, file_desc, 0)) == MAP_FAILED){
		perror("cannot mmap");
		return -1;
    }

    //lock shared mems
    if (mlock(vaddr, sizeof(struct cijferBuffer_t)) != 0){
		perror("cannot mlock");
		return -1;
    }

    //initialize semaphores
    if(sem_init(&(vaddr->sem), 1, 0) != 0){
        perror("cannot sem_init");
        return -1;
    }

    if(sem_init(&(vaddr->sem2), 1, 10) != 0){
        perror("Can not init semaphore emptyCount");
        return -1;
}

    

    printf("Shared Memory for struct is ready for use\n");


    //int i for waarde in struct
    int i = 0;
    struct cijfer_t cijfer;


    //while loop checks i so uitspraak can be correct
    while(1)
    {
       
        
        signal(SIGINT, Quit);
        
        cijfer.waarde = i;
        switch(i)
        {
            case 0:
                strcpy(cijfer.uitspraak, "zero");
                break;
            case 1:
                strcpy(cijfer.uitspraak, "one");
                break;
            case 2:
                strcpy(cijfer.uitspraak, "two");
                break;
            case 3:
                strcpy(cijfer.uitspraak, "three");
                break;
            case 4:
                strcpy(cijfer.uitspraak, "four");
                break;
            case 5:
                strcpy(cijfer.uitspraak, "five");
                break;
            case 6:
                strcpy(cijfer.uitspraak, "six");
                break;
            case 7:
                strcpy(cijfer.uitspraak, "seven");
                break;
            case 8:
                strcpy(cijfer.uitspraak, "eight");
                break;
            case 9:
                strcpy(cijfer.uitspraak, "nine");
                break;
        }
        sem_wait(&(vaddr->sem2));

        for (int i = 0; i < 9; i++)
        {
            vaddr->buffer[i] = vaddr->buffer[i+1];
        }
        vaddr->buffer[9] = cijfer;
        printf("%d:%s\n", cijfer.waarde, cijfer.uitspraak);
        sem_post(&(vaddr->sem));
        i++;
        if(i == 10)
        {
            i = 0;
        }
        
    }
    

}