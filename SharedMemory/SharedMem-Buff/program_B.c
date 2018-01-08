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
    printf("\nCLOSED\n");
    exit(0);
}

int main()
{
	
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
  
    signal(SIGINT, Quit);

    while(1)
    {
        sem_wait(&(vaddr->sem));

        struct cijfer_t printItem = vaddr->buffer[0];
       
        for (int i = 0; i < 9; i++)
        {
          vaddr->buffer[i] = vaddr->buffer[i+1];
        }

        
          printf("%i=%s\n", printItem.waarde, printItem.uitspraak);
          sem_post(&(vaddr->sem2));

    }
}