#include <iostream>
#include <string>

#include <udp_serv.hpp>

#define MAX_HISTORY_MS 200
#define SLEEP_DURATION_MS 300

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
        if ((get_micros() - myUDP.get_time_stamp()) > MAX_HISTORY_MS)
            buf = '\0';
        std::cout << "Recieve: " << buf << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION_MS));
    }

    recv_thread.join();
    return 0;
}