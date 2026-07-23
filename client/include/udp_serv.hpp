#ifndef __UDP_SERV_HPP__
#define __UDP_SERV_HPP__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <atomic>
#include <thread>

#define PORT 8080
#define MAXLINE 10

class UDPServer
{
private:
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t len = sizeof(cli_addr);
    std::atomic<char> internal_buffer;

public:
    int init_server();
    void recv_buff(char *buf);
};

#endif
