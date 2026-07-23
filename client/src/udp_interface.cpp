#include <iostream>
#include <string>

#include <udp_serv.hpp>

char buf;

UDPServer myUDP;
int status;

int main(int argc, char **argv)
{
    status = myUDP.init_server();
    if (status)
        return status;

    std::thread recv_thread(&UDPServer::recv_buff, &myUDP, &buf);
    while (1)
    {
        std::cout << "Recieve: " << buf << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    recv_thread.join();
    return 0;
}