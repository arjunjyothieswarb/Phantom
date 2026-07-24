#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>

#include "udp_client_utils.hpp"

int UDPClient::init_client()
{
    std::cout << "Initializing client" << std::endl;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed\n");
        return ESOCKTNOSUPPORT;
    }

    // Clearing the address
    memset(&serv_addr, 0, sizeof(serv_addr));

    // Filling server information
    serv_addr.sin_family = AF_INET;                         // IPv4
    serv_addr.sin_port = htons(PORT);                       // Port
    serv_addr.sin_addr.s_addr = inet_addr("192.168.1.180"); // Server IP
}

void UDPClient::send_msg(char *buf, int buf_len)
{
    // Send message to server
    sendto(sockfd, buf, buf_len, MSG_CONFIRM, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    return;
}