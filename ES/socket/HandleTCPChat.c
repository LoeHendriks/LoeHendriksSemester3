#include <stdio.h>
#include <ctype.h>      // for isupper() etc.
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include <string.h>
#include "Auxiliary.h"
#include "HandleTCPChat.h"

//#define RCVBUFSIZE 32   /* Size of receive buffer */
#define BUFF_SIZE 100

void HandleTCPChat (int clntSocket)
{
	setbuf(stdin, NULL);
    // 'clntSocket' is obtained from AcceptTCPConnection()

    char echoBuffer[BUFF_SIZE];        /* Buffer for echo string */
    int  recvMsgSize;                   /* Size of received message */
    char tempString[BUFF_SIZE + 1];             /* String to save the cin */
    char* sendString;
    

    /* Receive message from client */
    recvMsgSize = recv (clntSocket, echoBuffer, BUFF_SIZE-1, 0);
    if (recvMsgSize < 0)
    {
        DieWithError ("recv() failed");
    }
    info_d ("Recv", recvMsgSize);

    while (recvMsgSize > 0)     
    {
		echoBuffer[recvMsgSize] = '\0';
        printf("Recieved string: %s", echoBuffer);
        
        bool check = false;
        printf("\nWhat's your message: \n");
        
        
        while(!check)
        {
            fgets(tempString, BUFF_SIZE, stdin);
            if(strcmp(tempString, "") != 0)
            {
                sendString = tempString;
                check = true;
            }
        }
        
        
        if(strcmp(sendString, "quit") == 0)
        {
            close (clntSocket);
        }
    
        delaying ();
        
        /* Echo message back to client */
        if (send (clntSocket, sendString, recvMsgSize, 0) != recvMsgSize)
        {
            DieWithError ("send() failed");
        }

        // TODO: add code to display the transmitted string in verbose mode; use info_s()
        info_s("\nTransmitted string: ", sendString);
        printf("\n");

        // receive next string
        memset(echoBuffer, 0 , BUFF_SIZE);
        recvMsgSize = recv (clntSocket, echoBuffer, BUFF_SIZE-1, 0);
        if (recvMsgSize < 0)
        {
            DieWithError ("recv() failed");
        }
        info_d ("recv", recvMsgSize);
    }

    close (clntSocket);    /* Close client socket */
    info ("close");
}
