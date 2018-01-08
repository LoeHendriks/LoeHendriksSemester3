#include "Connection.h"

Connection::Connection()
{
    sock = 0;
}

Connection::~Connection()
{

}

int Connection::Connect (int port)
{
    struct sockaddr_in  echoServAddr; /* Echo server address */

    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        //DieWithError("socket() failed");
    }
    //info ("socket");
    sleep(1);

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(SIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(port);         /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    {
        printf("connection failed");
    }

    return (sock);
}

int Connection::Close()
{
    close (sock);
    return 1;
}

std::string Connection::Command(std::string message)
{
    // See CreateTCPClientSocket
    send(sock, message.c_str(), strlen(message.c_str()), 0);
    sleep(1);

    // See HandleTCPClient
    char echoBuffer[RCVBUFSIZE];      /* Buffer for received string */
    int recvMsgSize;                  /* Size of received message */

    recvMsgSize = recv(sock, echoBuffer, RCVBUFSIZE-1, 0);
    if (recvMsgSize < 0)
    {
        printf("recv message failed");
    }
    echoBuffer[recvMsgSize] = '\0';
    std::stringstream sstring;
    sstring.str (echoBuffer);
    std::string returnstring = sstring.str();
    return (returnstring);
}
