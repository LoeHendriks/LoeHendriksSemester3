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

#define SIZE 1024


const char* SH_MEM_NAME = "xbox";
const char* MQ_NAME = "/xboxMQ";
struct xbox_t* vaddr;
int32_t file_desc;
int32_t show = 1;


//Function Called on CRTL-C
void Quit()
{
    munmap(vaddr, sizeof(struct xbox_t));
	  close(file_desc);
    shm_unlink(SH_MEM_NAME);
    printf("\nCLOSED\n");
    exit(0);
}


//Function prints the status of every pressable button
void print(struct xbox_t x)
{
		printf("<P>up %d.</P>",x.dpadUp);
		printf("<P>down %d.</P>",x.dpadDown);
		printf("<P>left %d.</P>",x.dpadLeft);
		printf("<P>right %d.</P>",x.dpadRight);	
		printf("<P>start %d.</P>",x.start);	
		printf("<P>back %d.</P>",x.back);	
		printf("<P>left stick %d.</P>",x.leftJoystick);	
		printf("<P>right stick %d.</P>",x.rightJoystick);	
		printf("<P>lb %d.</P>",x.lb);
		printf("<P>rb %d.</P>",x.rb);
		printf("<P>xbox %d.</P>",x.xbox);
		printf("<P>a %d.</P>",x.a);
		printf("<P>b %d.</P>",x.b);
		printf("<P>x %d.</P>",x.x);
		printf("<P>y %d.</P>",x.y);
}

int main()
{
		
			
	if ((file_desc = shm_open(SH_MEM_NAME, O_CREAT | O_RDWR, 0666)) == -1)
    {
      perror("cannot open shared mem");
      return -1;
	}
	
    if (ftruncate(file_desc, sizeof(struct xbox_t)) != 0)
    {
      perror("cannot set size of struct");
      return -1;
    }

    if ((vaddr = (struct xbox_t *)mmap(0, sizeof(struct xbox_t), PROT_WRITE, MAP_SHARED, file_desc, 0)) == MAP_FAILED){
      perror("cannot mmap");
      return -1;
    }

    if (mlock(vaddr, sizeof(struct xbox_t)) != 0){
      perror("cannot mlock");
      return -1;
    }
  
	signal(SIGINT, Quit);
	
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	
			mqd_t mq;
			char buffer[SIZE+1] = "-";
			//create msgqueue
			mq = mq_open("/test_queue", O_WRONLY | O_NONBLOCK);
			mq_send(mq, buffer, SIZE, 0);

		
    //while(show)
    //{     
		char* env = getenv("QUERY_STRING");

       	if(env == NULL || strlen(env) == 0 || *env == '\0'){
			sem_wait(&(vaddr->sem1));
			print(*vaddr);
			sem_post(&(vaddr->sem1));
			show = 0;
		}
		else{
			int32_t check;
			sscanf(env,"m=%d",&check);
			if(check == 1)
			{
				char buffer2[1025] = "rumble";
				//create msgqueue
				mq = mq_open("/test_queue", O_WRONLY | O_NONBLOCK);
				mq_send(mq, buffer2, 1024, 0);
			}
			if(check == 2)
			{
				char buffer2[1025] = "rotate";
				//create msgqueue
				mq = mq_open("/test_queue", O_WRONLY | O_NONBLOCK);
				mq_send(mq, buffer2, 1024, 0);
			}
			if(check == 3)
			{
				char buffer2[1025] = "stop";
				//create msgqueue
				mq = mq_open("/test_queue", O_WRONLY | O_NONBLOCK);
				mq_send(mq, buffer2, 1024, 0);
			}
			
			
		}
	//}


	return 0;
}