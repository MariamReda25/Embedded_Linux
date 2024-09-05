/**************  Client Algorithm Description *********************
 * the client's algorithm is as follows:
 * socket() -> connect() -> send() -> receive()
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

constexpr unsigned int SERVER_PORT = 50567;
constexpr unsigned int MAX_BUFFER = 128;

 int main (int argc, char *argv[]) {

    /* initializing socket using socket func (domain , Protocol , Type)*/
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);

   /* Chech if socket initialized or not (Success -> file descriptor . Fail -> -ve value)*/
    if (sockfd < 0)
    {
        std::cerr << "socket error" << std::endl;
        return 1;
    }
     
     /* getting the information that is related to the server */
    struct hostent* server = gethostbyname(argv[1]);

    /*return the hostent structure or a NULL pointer if an error occurs.*/
    if (server == nullptr)
    {
        std::cerr << "gethostbyname, no such host" << std::endl;
        return 2;
    } 

      /* to connect , we need correct info. about server*/
     struct sockaddr_in serv_addr;
     /* 1. Erase created struct (sev_addr)
        2. Assign server Fanily 
        3. Copy server address which get by (gethostbyname) Function.
        4. Assign Server Port
        5. establish Connetion to server
     */
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
     serv_addr.sin_port = htons(SERVER_PORT);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0)
    {
        std::cerr << "connect error" << std::endl;
        return 3;
    }


     /*server will reply with a connection ack, so we call the read method*/
    std::string readBuffer (MAX_BUFFER, 0);
    if (read(sockfd, &readBuffer[0], MAX_BUFFER-1) < 0)
    {
        std::cerr << "read from socket failed" << std::endl;
        return 5;
    }
    std::cout << readBuffer << std::endl;


    /* Send data to server using Write*/
     std::string writeBuffer (MAX_BUFFER, 0);
     std::cout << "What message for the server? : ";
     getline(std::cin, writeBuffer);
     if (write(sockfd, writeBuffer.c_str(), strlen(writeBuffer.c_str())) < 0)
    {
        std::cerr << "write to socket" << std::endl;
        return 4;
    }


     /*close the socket*/
     close(sockfd);
     
 return 0;  
   
 }
