#include <iostream>
#include <thread>
#include <atomic>

#include "term_utils.hpp"
#include "udp_client_utils.hpp"

UDPClient myUDPClient;

int main(int argc, char **argv)
{
    char c;
    int msg_len = 1;
    int status;
    std::cout << "Hello World!" << std::endl;

    // Initializing client
    status = myUDPClient.init_client();
    if (status)
        return status;

    // Setting terminal to non-canonical mode
    enableRawMode();

    while (true)
    {
        // Flushing the input to ensure only the
        // latest press gets transmitted
        tcflush(STDIN_FILENO, TCIFLUSH);
        read(STDIN_FILENO, &c, 1);

        if (c == 'q')
            break;
        std::cout << "Key Pressed: " << c << std::endl;
        myUDPClient.send_msg(&c, msg_len);

        std::this_thread::sleep_for(std::chrono::milliseconds(UDP_TRANSMISSION_RATE_MS));
    }

    // Restorting default terminal settings
    disableRawMode();

    return 0;
}