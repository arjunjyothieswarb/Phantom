#include <string>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <udp_serv.hpp>

uint64_t get_micros()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int UDPServer::init_server()
{
    /**
     * Initialize UDP server
     *
     * */

    std::cout << "Initiating server" << std::endl;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed\n");
        return ESOCKTNOSUPPORT;
    }

    // Clearing the address
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));

    // Filling server information
    serv_addr.sin_family = AF_INET;         // IPv4
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Accept incoming packets from any address
    serv_addr.sin_port = htons(PORT);       // Port

    // Bind socket with server address
    if (bind(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Socket bind failure\n");
        return ECONNREFUSED;
    }

    std::cout << "Socket Initialzed\n";

    return 0;
}

void UDPServer::recv_buff(char *buf)
{
    /**
     * Thread that recieves UDP packets and stores them in a buffer
     */
    ssize_t n;
    while (true)
    {
        // Recieve UDP datagrams
        n = recvfrom(sockfd, &internal_buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
        if (n < 0)
        {
            perror("recvfrom failed\n");
            continue;
        }
        else if (n == 0)
            continue;

        // Load the command and update timestamp
        *buf = internal_buffer.load();
        prev_time_st = get_micros();

        std::this_thread::sleep_for(std::chrono::milliseconds(UDP_TRANSMISSION_RATE_MS));
    }
}

uint64_t UDPServer::get_time_stamp()
{
    return prev_time_st.load();
}