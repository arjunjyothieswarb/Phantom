#ifndef __UDP_CLIENT_UTILS_HPP__
#define __UDP_CLIENT_UTILS_HPP__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define UDP_TRANSMISSION_RATE_MS 200

class UDPClient
{
private:
    int sockfd;
    struct sockaddr_in serv_addr;
    socklen_t len = sizeof(serv_addr);

public:
    int init_client();
    void send_msg(char *buf, int buf_len);
};

#endif