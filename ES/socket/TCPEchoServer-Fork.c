#include <stdlib.h>     // for atoi() and exit()
#include <unistd.h>     // for fork()
#include <sys/wait.h>   // for waitpid()
#include <stdio.h>
#include "Auxiliary.h"
#include "AcceptTCPConnection.h"
#include "CreateTCPServerSocket.h"
#include "HandleTCPClient.h"




int main(int argc, char *argv[])
{
    int     servSock;                  /* Socket descriptor for server */
    int     clntSock;                  /* Socket descriptor for client */
    pid_t   processID;                 /* Process ID from fork() */
    bool    to_quit = false;

    parse_args (argc, argv);

    servSock = CreateTCPServerSocket (argv_port);

    while (to_quit == false)                
    {
        clntSock = AcceptTCPConnection (servSock);


        processID = fork();
        
        if(processID == 0){                     
            info("Child Process : 0");
            HandleTCPClient(clntSock);
        }
        else if (processID > 0){               
            info_d("Parent Process : ", processID);
            continue;
        }
        else {
            
            info_d(" Cant fork!", processID);
            to_quit = true;
        }
			
    }
    
	return (0);
}



