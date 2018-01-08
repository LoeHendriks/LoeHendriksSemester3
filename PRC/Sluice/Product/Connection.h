#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <stdio.h>
#include <string.h>     // for strlen()
#include <stdlib.h>     // for exit()
#include <sys/socket.h> // for send() and recv()
#include <unistd.h>     // for sleep(), close()
#include <sstream>      // std::stringstream, std::stringbuf
#include <memory.h>     // for memset()
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define SIP "127.0.0.1" // is Localhost

class Connection
{
private:
  int sock;
public:
	Connection();
	~Connection();

	int Connect(int port);
	std::string Command(std::string message);
	int Close();
};

#endif
