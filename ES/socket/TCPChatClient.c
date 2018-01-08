#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()

#include "Auxiliary.h"
#include "CreateTCPClientSocket.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define BUFF_SIZE 100

int main (int argc, char *argv[])
{
	setbuf(stdin, NULL);
    int         sock;                   /* Socket descriptor */
    char *      echoString;             /* String to send to echo server */
    char        echoBuffer[BUFF_SIZE]; /* Buffer for received string */
    char       tempString[BUFF_SIZE + 1];             /* String to save the cin */
    int         echoStringLen;          /* Length of string to echo */
    int         bytesRcvd;              /* Bytes read in single recv() */

    parse_args (argc, argv);

    sock = CreateTCPClientSocket (argv_ip, argv_port);

    bool end = false;

    delaying();

    while (!end)
    {
        bool messageGet = false;
        //stdin
        printf("\nWhat's your message: \n");
        while(!messageGet)
        {
            fgets(tempString, BUFF_SIZE, stdin);
            if(strcmp(tempString, "") != 0)
            {
                echoString = tempString;
                messageGet = true;
            }
        }
        if(strcmp(echoString, "quit") == 0)
        {
            close(sock);
        }
        echoStringLen = strlen(echoString);
        delaying();

        send(sock, echoString, echoStringLen, 0);
        info_s("Sent string: ", echoString);
        
		memset(&echoBuffer, 0 , BUFF_SIZE);
		
		
        bytesRcvd = recv(sock, echoBuffer, BUFF_SIZE-1, 0);
        if(bytesRcvd > 0)
        {
            printf("Recieved Message: %s", echoBuffer);
            //info_s("Recieved string: ", echoBuffer);
        }
    }

    delaying ();

    close (sock);
    info ("close & exit");
    exit (0);
}
