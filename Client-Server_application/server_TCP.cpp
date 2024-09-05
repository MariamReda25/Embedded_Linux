/**************  Server Algorithm Description *********************
 * The server's algorithm is as follows:
 *  socket() -> bind() -> listen() -> accept() -> receive() -> send()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>

constexpr unsigned int SERVER_PORT = 50567;
constexpr unsigned int MAX_BUFFER = 128;
constexpr unsigned int MSG_REPLY_LENGTH = 18;

int main (int argc, char *argv[]) {

   /* initializing socket using socket func (domain , Protocol , Type)*/
   int sockfd = socket(AF_INET, SOCK_STREAM, 0);

   /* Chech if socket initialized or not (Success -> file descriptor . Fail -> -ve value)*/
     if (sockfd < 0)
    {
        std::cerr << "open socket error" << std::endl;
        return 1;
    }
    /*socket descriptor that will identify our connection*/
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));


    /*bind the socket to a port and serv_addr on the local machine*/

    struct sockaddr_in serv_addr, cli_addr;
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(SERVER_PORT);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "bind error" << std::endl;
        return 2;
    }

    /* wait for and accept any incoming connection*/
    listen(sockfd, 5);
    socklen_t clilen = sizeof(cli_addr);
     
     
    /* creates a new connected socket, and returns a new file descriptor referring to that socket.*/
    int incomingSock = accept(sockfd, (struct sockaddr *) &cli_addr,&clilen);
    if (incomingSock < 0)
    {
        std::cerr << "accept error" << std::endl;
        return 3;
    }

    /* As soon as we get a connection , send a confirmation ACK*/
    std::cout << "server: got connection from = "
    << inet_ntoa(cli_addr.sin_addr)
    << " and port = " << ntohs(cli_addr.sin_port)<< std::endl;
    
     write(incomingSock, "You are connected!", MSG_REPLY_LENGTH);


    /* read any data coming from the client */
    std::string buffer (MAX_BUFFER, 0);
    if (read(incomingSock, &buffer[0], MAX_BUFFER-1) < 0)
    {
        std::cerr << "read from socket error" << std::endl;
        return 4;
    }
    std::cout << "Got the message:" << buffer << std::endl;
   

    /* close both the sockets */
    close(incomingSock);
    close(sockfd);


  return 0;
}